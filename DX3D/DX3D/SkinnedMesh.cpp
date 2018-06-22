#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"
#include "BoundingBox.h"
#include "Ray.h"
#include "EnemyManager.h"
#include "Enemy.h"

//원준이가 끄적거린!
#include "Cubeman.h"


#define SCALE 0.05f

SkinnedMesh::SkinnedMesh()
{
	//m_Brot.y = ;
	m_baseRotY = D3DX_PI;

	m_pRootFrame = NULL;
	m_pAnimController = NULL;
	m_fBlendTime = 0.3f;
	m_fPassedBlendTime = 0.0f;
	m_animIndex = 0;
	m_bWireFrame = false;
	m_bDrawFrame = true;
	m_bDrawSkeleton = false;
}

SkinnedMesh::~SkinnedMesh()
{
	SAFE_RELEASE(m_pBox);
	SAFE_RELEASE(m_pSphereMesh);
	AllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRootFrame, &alloc);

	SAFE_RELEASE(m_pAnimController);
}

void SkinnedMesh::Init()
{
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	D3DXCreateSphere(g_pDevice, 0.01f, 10, 10, &m_pSphereMesh, NULL);

	//Load(ASSET_PATH + _T("zealot/"), _T("zealot.X"));
	//CString path = "resources/xFile/";
	//CString path = "resources/zealot/";
	//CString filename = "ironman.X";
	//Load(path, filename);
	D3DXMatrixIdentity(&m_matWorld);

	m_pBox = new BoundingBox(D3DXVECTOR3(2.0f, 1.0f, 2.0f)); m_pBox->Init();

	//위치 초기화
	BloodCalPos = D3DXVECTOR3(0, 0, 0);
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
	m_pBox->Update();
	m_pBox->SetPosition(&m_pos);

	Debug->AddText(_T("Anim Index = "));
	Debug->AddText((int)m_animIndex + 1);
	Debug->AddText(_T(" / "));
	if(m_pAnimController != NULL)
	Debug->AddText((int)m_pAnimController->GetMaxNumAnimationSets());
	Debug->EndLine();
	D3DXMATRIXA16 matR;

	IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePosition();

	//인덱스4 = 기본상태 , 3 = 점프, 2 = 뒷무빙, 1 = 앞 뛰기 0 = 레이저 쏘기

	//if (Keyboard::Get()->KeyDown('1'))//1
	//{
	//	if (m_animIndex < m_pAnimController->GetMaxNumAnimationSets() - 1)
	//		m_animIndex++;

	//	SetAnimationIndex(m_animIndex, true);
	//}


	//방향키 가라치기, 휴면상태, idle 만들기

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
	}

	//모션 돌리기
	if (!(g_pKeyboard->KeyPress(VK_LSHIFT)))
	{
		m_rot.x = g_pCamera->m_rotX;
		m_rot.y = g_pCamera->m_rotY;
	}
	else
		m_rot += m_deltaRot * m_rotationSpeed;


	D3DXMATRIXA16 matRotY, matRotX, matRot;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	D3DXMatrixRotationX(&matRotX, m_rot.x);
	matRot = matRotY * matRotX;

	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixScaling(&matS, SCALE, SCALE, SCALE);
	m_matWorld = matS * matRotY* matR * matT;
	
	UpdateAnim();
	UpdateFrameMatrices(m_pRootFrame, NULL);

	
	D3DXTRACK_DESC track;
	m_pAnimController->GetTrackDesc(0, &track);
	LPD3DXANIMATIONSET pCurrAnimSet = NULL;
	m_pAnimController->GetAnimationSet(0, &pCurrAnimSet);
	pCurrAnimSet->GetPeriod(); //전체 시간
	Debug->EndLine();
	Debug->EndLine();
	Debug->AddText("전체 시간 : ");
	Debug->AddText(pCurrAnimSet->GetPeriod());
	Debug->EndLine();
	Debug->AddText("현재 시간 : ");
	pCurrAnimSet->GetPeriodicPosition(track.Position); //현재 시간
	Debug->AddText(pCurrAnimSet->GetPeriodicPosition(track.Position));
	Debug->EndLine();
	Debug->EndLine();
	pCurrAnimSet->Release();

	Shoot();
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
}


void SkinnedMesh::Render()
{
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
	if (m_numFrame % 10 == 0)
	{
		Debug->EndLine();
	}
	if (pFrame->Name == NULL)
		Debug->AddText(_T("NULL"));
	else
		Debug->AddText(pFrame->Name);


	LPD3DXMESHCONTAINER pMeshContainer = pFrame->pMeshContainer;
	while (pMeshContainer != NULL)
	{
		m_numMesh++;
		Debug->AddText(_T("(MESH)"));
		DrawMeshContainer(pFrame);
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}
	Debug->AddText(_T(" / "));
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

	if (m_bWireFrame)
		g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//D3DXMatrixIdentity(&m_matWorld);
	//D3DXMatrixScaling(&m_matWorld, 5.0f, 5.0f, 5.0f);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (size_t i = 0; i < pMeshContainerEx->vecMtlTex.size(); ++i)
	{
		g_pDevice->SetMaterial(&pMeshContainerEx->vecMtlTex[i]->GetMaterial());
		g_pDevice->SetTexture(0, pMeshContainerEx->vecMtlTex[i]->GetTexture());
		pMeshContainerEx->pWorkMesh->DrawSubset(i);
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

void SkinnedMesh::Shoot()
{
	//Debug->AddText("캐릭터 위치 : ");
	//Debug->AddText(static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition());
	//Debug->EndLine();
	//Debug->EndLine();
	//g_pMouse->ButtonDown(Mouse::LBUTTON)
	if (g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		Ray r = Ray::RayAtWorldSpace(g_pCamera->GetMCenter().x, g_pCamera->GetMCenter().y);

		Debug->AddText("캐릭터 위치 : ");
		Debug->AddText(static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition());
		Debug->EndLine();
		Debug->EndLine();

		Debug->AddText("캐릭터 방향 : ");
		Debug->AddText(static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward());
		Debug->EndLine();
		Debug->EndLine();

		Debug->AddText("레이 위치 : ");
		Debug->AddText(r.m_pos);
		Debug->EndLine();
		Debug->EndLine();

		Debug->AddText("레이 방향 : ");
		Debug->AddText(r.m_dir);
		Debug->EndLine();
		Debug->EndLine();

		BoundingSphere* sphere = NULL;
		float minDistance = FLT_MAX;
		float intersectionDistance;
		EnemyManager* em = static_cast <EnemyManager *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY));
		BoundingSphere* temp = NULL;
		for (auto p : em->GetVecEnemy())
		{
			temp = p->GetSphere();
			if (r.CalcIntersectSphere(temp) == true)
			{
				intersectionDistance = D3DXVec3Length(&(temp->center - r.m_pos));
				//printf("거리 : %f\n", intersectionDistance);
				//최소거리
				if (intersectionDistance < minDistance)
				{
					minDistance = intersectionDistance;
					sphere = temp;
				}
				//파티클 거리 구하기
				D3DXVECTOR3 TempPos = static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition();
				D3DXVECTOR3 TempDir = static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward();
				//거리 보정 위치값 찾기
				BloodCalPos = TempDir * (intersectionDistance) * 3 / 5 + TempPos;
				//BloodCalPos = TempDir * minDistance + TempPos;

			}
			if (sphere != NULL)
			{
				p->MinusHP();
				static_cast<BloodManager*>(g_pObjMgr->FindObjectByTag(TAG_PARTICLE))->Fire();
				break;
			}
		}
	}
	Debug->AddText("힛트계산 위치 : ");
	Debug->AddText(BloodCalPos);
	Debug->EndLine();
	Debug->EndLine();
}


void SkinnedMesh::SetAnimationIndex(int nIndex, bool isBlend)
{
	LPD3DXANIMATIONSET pNextAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);

	//트랙 자체의 속도를 빠르게하는 기능
	//m_pAnimController->SetTrackSpeed(0, 5.f);
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
