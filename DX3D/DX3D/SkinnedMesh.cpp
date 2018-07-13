#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"

#include"Ironman.h"

SkinnedMesh::SkinnedMesh()
{
	//m_Brot.y = ;
	//m_baseRotY = D3DX_PI;

	m_pRootFrame = NULL;
	m_pAnimController = NULL;
	m_fBlendTime = 0.3f;
	m_fPassedBlendTime = 0.0f;
	m_animIndex = 0;
	m_bWireFrame = false;
	m_bDrawFrame = true;
	m_bDrawSkeleton = false;

	//만약에 셰이더 안쓸라고 RenderMode 따로 셋팅 안해주면 그냥 Render 해주기
	m_renderMode = IDisplayObject::RenderMode::RenderMode_Default;
}

SkinnedMesh::~SkinnedMesh()
{
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void SkinnedMesh::Init()
{
	D3DXCreateSphere(g_pDevice, m_radius, 10, 10, &m_pSphereMesh, NULL);

	D3DXMatrixIdentity(&m_matWorld);
}

void SkinnedMesh::Load(LPCTSTR path, LPCTSTR filename)
{
	AllocateHierarchy alloc(path);

	CString fullPath(path);
	fullPath.Append(filename);

	D3DXLoadMeshHierarchyFromX(fullPath, D3DXMESH_MANAGED, g_pDevice,&alloc, NULL, &m_pRootFrame, &m_pAnimController);

	SetupBoneMatrixPointers(m_pRootFrame);
}

// 각 프레임의 매시 컨테이너에 있는 pSkinInfo를 이용하여 
// 현재 매쉬에 영향을 주는 프레임들의 월드행렬 포인터를 연결 
//Called to setup the pointers for a given bone to its transformation matrix
void SkinnedMesh::SetupBoneMatrixPointers(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer != NULL)
	{
		SetupBoneMatrixPointersOnMesh(pFrame->pMeshContainer);
	}

	if (pFrame->pFrameSibling != NULL)
	{
		SetupBoneMatrixPointers(pFrame->pFrameSibling);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		SetupBoneMatrixPointers(pFrame->pFrameFirstChild);
	}
}

void SkinnedMesh::SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase)
{
	DWORD numBones;
	FRAME_EX* pFrameExInfluence;
	MESHCONTAINER_EX* pMeshContainerEx = (MESHCONTAINER_EX*)pMeshContainerBase;

	if (pMeshContainerEx->pSkinInfo != NULL)
	{
		numBones = pMeshContainerEx->pSkinInfo->GetNumBones();

		for (DWORD i = 0; i < numBones; ++i)
		{
			pFrameExInfluence = (FRAME_EX*)D3DXFrameFind(m_pRootFrame,
				pMeshContainerEx->pSkinInfo->GetBoneName(i));

			pMeshContainerEx->ppBoneMatrixPtrs[i] = &pFrameExInfluence->CombinedTM;
		}
	}
}


void SkinnedMesh::Update()
{
	//Debug->AddText(_T("Anim Index = "));
	//Debug->AddText((int)m_animIndex + 1);
	//Debug->AddText(_T(" / "));
	//if(m_pAnimController != NULL)
	//Debug->AddText((int)m_pAnimController->GetMaxNumAnimationSets());
	//Debug->EndLine();
	
	if (Keyboard::Get()->KeyDown(VK_F1))
	{
		m_bDrawFrame = !m_bDrawFrame;
	}

	SetAnimationIndex(status, true);

	UpdateAnim();
	UpdateFrameMatrices(m_pRootFrame, NULL);


	//m_pBounidngSphere->center = D3DXVECTOR3(m_pos.x, m_pos.y + m_SphereHeight, m_pos.z);
	//D3DXMatrixTranslation(&m_SphereMat, m_pBounidngSphere->center.x, m_pBounidngSphere->center.y, m_pBounidngSphere->center.z);
}


void SkinnedMesh::UpdateAnim()
{
	float fDeltaTime = g_pTimeManager->GetDeltaTime();
	// AdvanceTime 함수가 호출된 간격으로 Anim 키프레임 계산
	m_pAnimController->AdvanceTime(fDeltaTime, NULL);

	if (m_fPassedBlendTime <= m_fBlendTime)
	{
		m_fPassedBlendTime += fDeltaTime;

		if (m_fPassedBlendTime < m_fBlendTime)
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;

			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
		else
		{
			m_pAnimController->SetTrackWeight(0, 1);
			m_pAnimController->SetTrackWeight(1, 0);
			m_pAnimController->SetTrackEnable(1, false);
		}
	}
}

void SkinnedMesh::UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;

	if (pParent != NULL)
	{
		pFrameEx->CombinedTM = pFrameEx->TransformationMatrix * ((FRAME_EX*)pParent)->CombinedTM;
	}
	else
	{
		pFrameEx->CombinedTM = pFrameEx->TransformationMatrix;
	}

	if (pFrameEx->pFrameSibling != NULL)
	{
		UpdateFrameMatrices(pFrameEx->pFrameSibling, pParent);
	}

	if (pFrameEx->pFrameFirstChild != NULL)
	{
		UpdateFrameMatrices(pFrameEx->pFrameFirstChild, pFrameEx);
	}

	/*
	mixamorig:RightHand
	mixamorig:RightHandIndex1
	mixamorig:RightHandIndex2
	mixamorig_RightHand
	mixamorig_LeftHand
	*/
	//오른손행렬값 찾아서 따로 담기
	//LPSTR hand = "mixamorig_RightHand";
	//하드코딩 가즈아!!!!!!!!!!!!!!!32개 아무것도 아냐!
	if (pFrame->Name != NULL && strcmp(pFrame->Name, "mixamorig_RightHand")==0)
	{
		FRAME_EX * pFrameEx = (FRAME_EX *)pFrame;//* m_matWorld
		m_RightHandFrame = ((pFrameEx->CombinedTM)* m_matWorld);
	}
}


void SkinnedMesh::Render()
{
	if (m_renderMode != IDisplayObject::RenderMode::RenderMode_Default) return;

	m_numFrame = 0;
	m_numMesh = 0;
	
	Debug->AddText(_T("=====DrawFrame====="));
	Debug->EndLine();
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);
	Debug->EndLine();
	Debug->AddText(_T("numFrame = "));
	Debug->AddText(m_numFrame);
	Debug->EndLine();
	Debug->AddText(_T("numMesh = "));
	Debug->AddText(m_numMesh);
	Debug->EndLine();
	if (m_bDrawSkeleton)DrawSkeleton(m_pRootFrame, NULL);
}

// Desc: Called to render a frame in the hierarchy
void SkinnedMesh::DrawFrame(LPD3DXFRAME pFrame)
{
	m_numFrame++;
	//if (m_numFrame % 10 == 0)
	//{
	//	Debug->EndLine();
	//}
	//if (pFrame->Name == NULL)
	//	Debug->AddText(_T("NULL"));
	//else
	//	Debug->AddText(pFrame->Name);

	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		m_numMesh++;
		Debug->AddText(_T("(MESH)"));
		DrawMeshContainer(pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	//Debug->AddText(_T(" / "));
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}

void SkinnedMesh::DrawMeshContainer(LPD3DXFRAME pFrame)
{
	if (pFrame->pMeshContainer->pSkinInfo == NULL)
		return;

	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;
	MESHCONTAINER_EX* pMeshContainerEx = (MESHCONTAINER_EX*)pFrameEx->pMeshContainer;
	DWORD numBones = pMeshContainerEx->pSkinInfo->GetNumBones();

	for (DWORD i = 0; i < numBones; ++i)
	{
		pMeshContainerEx->pFinalBoneMatrices[i] =
			pMeshContainerEx->pBoneOffsetMatrices[i] * *(pMeshContainerEx->ppBoneMatrixPtrs[i]);
	}

	PBYTE pVerticesSrc = NULL;
	PBYTE pVerticesDest = NULL;

	pMeshContainerEx->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (LPVOID*)&pVerticesSrc);
	pMeshContainerEx->pWorkMesh->LockVertexBuffer(0, (LPVOID*)&pVerticesDest);

	// generate skinned mesh
	pMeshContainerEx->pSkinInfo->UpdateSkinnedMesh(
		pMeshContainerEx->pFinalBoneMatrices, NULL, pVerticesSrc, pVerticesDest);

	pMeshContainerEx->pWorkMesh->UnlockVertexBuffer();
	pMeshContainerEx->pOrigMesh->UnlockVertexBuffer();

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	//왜곡 줄이기, 맵이 밝아지는 효과가 생기네?!
	//g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	if (m_bWireFrame)
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//D3DXMatrixIdentity(&m_matWorld);
	//D3DXMatrixScaling(&m_matWorld, 5.0f, 5.0f, 5.0f);
	/*
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
	{
		g_pDevice->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->GetMaterial());
		g_pDevice->SetTexture(0, pMeshContainerEx->vecMtlTex[i]->GetTexture());
		pMeshContainerEx->pWorkMesh->DrawSubset(i);
	}
	*/

	if (m_renderMode == IDisplayObject::RenderMode::RenderMode_Default)
	{
		g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

		for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
		{
			g_pDevice->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->material);
			g_pDevice->SetTexture(0, pMeshContainerEx->vecMtlTex[i]->pTexture);
			pMeshContainerEx->pWorkMesh->DrawSubset(i);
		}
	}

	else if (m_renderMode == IDisplayObject::RenderMode::RenderMode_Lighting)
	{
		for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
		{
			Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
			Shaders::Get()->GetCurrentShader()->SetTexture(pMeshContainerEx->vecMtlTex[i]->pTexture);
			Shaders::Get()->GetCurrentShader()->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->material);
			Shaders::Get()->GetCurrentShader()->Commit();
			pMeshContainerEx->pWorkMesh->DrawSubset(i);
		}
	}
	else if (m_renderMode == IDisplayObject::RenderMode::RenderMode_ShadowMapping)
	{
		for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
		{
			Shaders::Get()->GetCurrentShader()->SetWorldMatrix(&m_matWorld);
			Shaders::Get()->GetCurrentShader()->SetTexture(pMeshContainerEx->vecMtlTex[i]->pTexture);
			Shaders::Get()->GetCurrentShader()->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->material);
			Shaders::Get()->GetCurrentShader()->Commit();
			pMeshContainerEx->pWorkMesh->DrawSubset(i);
		}
	}
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void SkinnedMesh::DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;
	FRAME_EX* pParentFrameEx = (FRAME_EX*)pParent;

	g_pDevice->SetTransform(D3DTS_WORLD, &(pFrameEx->CombinedTM));
	//g_pDevice->SetTransform(D3DTS_WORLD, &(pFrameEx->CombinedTM * m_matWorld));

	g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pDevice->SetTexture(0, NULL);
	m_pSphereMesh->DrawSubset(0);

	if (pParent != NULL && pFrame->Name != NULL && pParent->Name != NULL)
	{
		D3DXMATRIXA16 matThis = pFrameEx->CombinedTM;
		D3DXMATRIXA16 matParent = pParentFrameEx->CombinedTM;

		D3DXVECTOR3 posThis(matThis(3, 0), matThis(3, 1), matThis(3, 2));
		D3DXVECTOR3 posParent(matParent(3, 0), matParent(3, 1), matParent(3, 2));

		vector<VERTEX_PC> line{ VERTEX_PC(posThis, BLUE), VERTEX_PC(posParent, YELLOW) };
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pDevice->SetFVF(VERTEX_PC::FVF);
		D3DXMATRIXA16 mat;
		D3DXMatrixIdentity(&mat);

		g_pDevice->SetTransform(D3DTS_WORLD, &mat);
		g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 1, &line[0], sizeof(VERTEX_PC));
		g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	}

	if (pFrame->pFrameSibling != NULL)
	{
		DrawSkeleton(pFrame->pFrameSibling, pParent);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawSkeleton(pFrame->pFrameFirstChild, pFrame);
	}
}

void SkinnedMesh::RenderUseShader_0()
{
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);
}

void SkinnedMesh::RenderUseShader_1()
{
	if (m_bDrawFrame)DrawFrame(m_pRootFrame);
	// if (m_pSubRootFrame) if (m_bDrawFrame)DrawFrame(m_pSubRootFrame);
}

void SkinnedMesh::DrawSphereMatrix(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	FRAME_EX* pFrameEx = (FRAME_EX*)pFrame;
	FRAME_EX* pParentFrameEx = (FRAME_EX*)pParent;

	//원본 크기의 본 위치
	//g_pDevice->SetTransform(D3DTS_WORLD, &(pFrameEx->CombinedTM));
	//스킨매시 적용한 월드의 위치
	g_pDevice->SetTransform(D3DTS_WORLD, &(pFrameEx->CombinedTM * m_matWorld));
	g_pDevice->SetMaterial(&DXUtil::WHITE_MTRL);
	g_pDevice->SetTexture(0, NULL);
	m_pSphereMesh->DrawSubset(0);
	

	if (pFrame->pFrameSibling != NULL)
	{
		DrawSphereMatrix(pFrame->pFrameSibling, pParent);
	}

	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawSphereMatrix(pFrame->pFrameFirstChild, pFrame);
	}
	//D3DXVECTOR3 temp;
	//D3DXVec3TransformCoord(&temp, &temp, &(pFrameEx->CombinedTM * m_matWorld));
	//m_pBounidngSphere = new BoundingSphere(D3DXVECTOR3(temp.x, temp.y, temp.z), 2.0f);
	//Debug->AddText(temp);
	//Debug->EndLine();
	//Debug->EndLine();
}

void SkinnedMesh::SetAnimationIndex(int nIndex, bool isBlend)
{
	LPD3DXANIMATIONSET pNextAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);

	//트랙 자체의 속도를 빠르게하는 기능
	//m_pAnimController->SetTrackSpeed(0, 0.05f);
	//isBlend = false;
	if (isBlend)
	{
		m_fPassedBlendTime = 0.0f;

		LPD3DXANIMATIONSET pPrevAnimSet = NULL;

		m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
		m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);

		D3DXTRACK_DESC trackDesc;
		m_pAnimController->GetTrackDesc(0, &trackDesc);
		m_pAnimController->SetTrackDesc(1, &trackDesc);

		m_pAnimController->SetTrackWeight(0, 0.0f);
		m_pAnimController->SetTrackWeight(1, 1.0f);

		SAFE_RELEASE(pPrevAnimSet);

		m_fPassedBlendTime = 0.0f;
	}

	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->ResetTime();

	SAFE_RELEASE(pNextAnimSet);
}



/*업데이트 부분 setAnimation 개량부분
인덱스4 = 기본상태 , 3 = 점프, 2 = 뒷무빙, 1 = 앞 뛰기 0 = 레이저 쏘기
if (Keyboard::Get()->KeyDown('1'))//1
{
	if (m_animIndex < m_pAnimController->GetMaxNumAnimationSets() - 1)
		m_animIndex++;
	SetAnimationIndex(m_animIndex, true);
}
방향키 가라치기, 휴면상태, idle 만들기
if (Keyboard::Get()->KeyPress('W'))
{
	//m_pAnimController->KeyTrackSpeed(0,5.0f,10,20, D3DXTRANSITION_LINEAR);
	SetAnimationIndex(1, true);
}
else if (Keyboard::Get()->KeyPress('S'))
{
	SetAnimationIndex(2, true);
}
else if (Keyboard::Get()->KeyPress(VK_SPACE))
{
	SetAnimationIndex(3, true);
}
//Keyboard::Get()->KeyDown('2') ||
else if ( Mouse::Get()->ButtonDown(Mouse::Get()->LBUTTON))
{
	//if (m_animIndex > 0)//0
		//m_animIndex--;
	SetAnimationIndex(0, true);
}
else if (Keyboard::Get()->KeyDown(VK_F1))
{
	m_bDrawFrame = !m_bDrawFrame;
}
else if (Keyboard::Get()->KeyDown(VK_F2))
{
	m_bDrawSkeleton = !m_bDrawSkeleton;
}
else if (Keyboard::Get()->KeyDown(VK_F3))
{
	m_bWireFrame = !m_bWireFrame;
}
else//idle상태 만들기
{
	SetAnimationIndex(4, true);
}*/