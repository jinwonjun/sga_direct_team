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

	//보스 총 인덱스가 0~31 32개의 파츠 값 가져오기
	for (int i = 0; i < 32; i++)
	{
		D3DXMATRIXA16 temp;
		m_Boss_FrameMatrix.push_back(temp);
	}
	//쫄몹 총 인덱스가 0~32 33개의 파츠 값 가져오기
	for (int k = 0; k < 33; k++)
	{
		D3DXMATRIXA16 temp;
		m_Sub_FrameMatrix.push_back(temp);
	}
	//플레이어 인덱스가 0~51 52개의 파츠값 가져오기
	for (int j = 0; j < 52; j++)
	{
		D3DXMATRIXA16 temp;
		m_Player_FrameMatrix.push_back(temp);
	}

	SetFrameNameInit();
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
	
	//UpdateFrameMatrices(m_pRootFrame, NULL);
	//행렬 계산 함수 돌리기
	//보스 , 쫄 ,플레이어에다가 구별 변수 주고 따로따로 돌리기, 오른손 행렬 값도 이 함수에 넣음
	MonsterCalFrameMat(m_pRootFrame, NULL);
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
	//{
	//	Debug->EndLine();
	//	Debug->AddText(_T("NULL"));
	//}
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
}

//보스 && 쫄 행렬 계산 담기
void SkinnedMesh::MonsterCalFrameMat(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
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
		MonsterCalFrameMat(pFrameEx->pFrameSibling, pParent);
	}

	if (pFrameEx->pFrameFirstChild != NULL)
	{
		MonsterCalFrameMat(pFrameEx->pFrameFirstChild, pFrameEx);
	}
	//플레이어 오른손 행렬 좌표 구하기
	if (pFrame->Name != NULL && strcmp(pFrame->Name, "mixamorig_RightHand") == 0)
	{
		FRAME_EX * pFrameEx = (FRAME_EX *)pFrame;
		m_RightHandFrame = ((pFrameEx->CombinedTM)* m_matWorld);
	}
	//플레이어 시작부분
	for (int i = 0; i < 52; i++)
	{
		if (pFrame->Name != NULL && strcmp(pFrame->Name, PlayerFrameName[i].c_str()) == 0)
		{
			FRAME_EX * pFrameEx = (FRAME_EX *)pFrame;
			m_Player_FrameMatrix[i] = ((pFrameEx->CombinedTM)* m_matWorld);
		}
	}

	//보스 시작부분
	for (int i = 0; i < 32; i++)
	{
		if (pFrame->Name != NULL && strcmp(pFrame->Name, BossFrameName[i].c_str()) == 0)
		{
			FRAME_EX * pFrameEx = (FRAME_EX *)pFrame;
			m_Boss_FrameMatrix[i] = ((pFrameEx->CombinedTM)* m_matWorld);
		}
	}

	//질럿 찾기
	for (int i = 0; i < 33; i++)
	{
		if (pFrame->Name != NULL && strcmp(pFrame->Name, SubMobFrameName[i].c_str()) == 0)
		{
			FRAME_EX * pFrameEx = (FRAME_EX *)pFrame;
			m_Sub_FrameMatrix[i] = ((pFrameEx->CombinedTM)* m_matWorld);
		}
	}
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

//보스 및 쫄몹 프레임 이름 값 일일이 저장해서 찾는 용도
void SkinnedMesh::SetFrameNameInit()
{
	BossFrameName = new string[32]{
		"Mutant_Hips" ,
		"Mutant_Spine",
		"Mutant_Spine2",
		"Mutant_Neck",
		"Mutant_Head",
		"Mutant_LeftShoulder",
		"Mutant_LeftArm",
		"Mutant_LeftForeArm",
		"Mutant_LeftHand",
		"Mutant_LeftUpLeg",
		"Mutant_LeftLeg",
		"Mutant_LeftFoot",
		"Mutant_LeftToeBase",
		"Mutant_RightShoulder",
		"Mutant_RightArm",
		"Mutant_RightForeArm",
		"Mutant_RightHand",
		"Mutant_RightHandThumb1",
		"Mutant_RightHandThumb2",
		"Mutant_RightHandThumb3",
		"Mutant_RightHandThumb4",
		"Mutant_RightHandIndex1",
		"Mutant_RightHandIndex2",
		"Mutant_RightHandIndex3",
		"Mutant_RightHandPinky1",
		"Mutant_RightHandPinky2",
		"Mutant_RightHandPinky3",
		"Mutant_RightUpLeg",
		"Mutant_RightLeg",
		"Mutant_RightFoot",
		"Mutant_RightToeBase"
	};
	SubMobFrameName = new string[33]{
		"Main",
		"Root",
		"Pelvis",
		"Bone13",
		"Bone20",
		"Bone21",
		"Unit_Protoss_Zealot_Leg_Lower_04",
		"Bone13_mirrored_",
		"Bone20_mirrored_",
		"Bone21_mirrored_",
		"Lower_Chest",
		"UpperChest",
		"Bone01",
		"Bone02",
		"Bone03",
		"Bone04",
		"Star2Ribbon03",
		"BoneHead",
		"Star2Ribbon01",
		"Bone01_mirrored_",
		"Bone02_mirrored_",
		"Bone03_mirrored_",
		"Bone04_mirrored_",
		"Star2Ribbon04",
		"HitTestFuzzy",
		"Star2Force01",
		"HitTestTight",
		"Foot_Left",
		"Bone10",
		"Foot_Right",
		"Bone10_mirrored_",
		"Star2RibbonCharge",
		"Zealot_0"
	};
	PlayerFrameName = new string[52]{
		"mixamorig_Hips",
		"mixamorig_Spine",
		"mixamorig_Spine1",
		"mixamorig_Spine2",
		"mixamorig_Neck",
		"mixamorig_Head",
		"mixamorig_LeftShoulder",
		"mixamorig_LeftArm",
		"mixamorig_LeftForeArm",
		"mixamorig_LeftHand",
		"mixamorig_LeftHandThumb1",
		"mixamorig_LeftHandThumb2",
		"mixamorig_LeftHandThumb3",
		"mixamorig_LeftHandIndex1",
		"mixamorig_LeftHandIndex2",
		"mixamorig_LeftHandIndex3",
		"mixamorig_LeftHandMiddle1",
		"mixamorig_LeftHandMiddle2",
		"mixamorig_LeftHandMiddle3",
		"mixamorig_LeftHandRing1",
		"mixamorig_LeftHandRing2",
		"mixamorig_LeftHandRing3",
		"mixamorig_LeftHandPinky1",
		"mixamorig_LeftHandPinky2",
		"mixamorig_LeftHandPinky3",
		"mixamorig_RightShoulder",
		"mixamorig_RightArm",
		"mixamorig_RightForeArm",
		"mixamorig_RightHand",
		"mixamorig_RightHandThumb1",
		"mixamorig_RightHandThumb2",
		"mixamorig_RightHandThumb3",
		"mixamorig_RightHandIndex1",
		"mixamorig_RightHandIndex2",
		"mixamorig_RightHandIndex3",
		"mixamorig_RightHandMiddle1",
		"mixamorig_RightHandMiddle2",
		"mixamorig_RightHandMiddle3",
		"mixamorig_RightHandRing1",
		"mixamorig_RightHandRing2",
		"mixamorig_RightHandRing3",
		"mixamorig_RightHandPinky1",
		"mixamorig_RightHandPinky2",
		"mixamorig_RightHandPinky3",
		"mixamorig_LeftUpLeg",
		"mixamorig_LeftLeg",
		"mixamorig_LeftFoot",
		"mixamorig_LeftToeBase",
		"mixamorig_RightUpLeg",
		"mixamorig_RightLeg",
		"mixamorig_RightFoot",
		"mixamorig_RightToeBase"
	};
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