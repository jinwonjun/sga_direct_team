#include "stdafx.h"
#include "Cubeman.h"
#include "CubemanParts.h"
#include "Enemyman.h"

#include "Ray.h"
#include "Cube.h"
Cubeman::Cubeman()
{
	m_pRootParts = NULL;

	m_isMoving = false;
	//기본 이속
	//m_moveSpeed = 0.2f;

	m_moveSpeed = 0.5f;

	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;
	m_maxStepHeight = 0.5f;
}


Cubeman::~Cubeman()
{
	//요놈도 idisplayobject 상속받을예정
	m_pRootParts->ReleaseAll();
}

void Cubeman::Init()
{	
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	//printf("%f %f %f\n", &m_pos.x, &m_pos.y, &m_pos.z);
	//g_pCamera->SetTarget(& D3DXVECTOR3(0, m_pos.y, 0));

	//g_pKeyboardManager->SetMovingTarget(&m_deltaPos, &m_deltaRot , &m_isJumping);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);


	CreateAllParts();

	//버텍스 벡터에 정면 벡터값이랑 값 넣어주기
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	//시점
	m_vecVertex.push_back(VERTEX_PC(m_pos, red));//0
	//종점
	m_vecVertex.push_back(VERTEX_PC(m_pos + m_forward * 100, red));//1
}

void Cubeman::Update()
{
	//UpdatePosition();
	//디버그 코드 예제
	//Debug->AddText(m_pos);
	//Debug->EndLine();//찍고 나서 줄바꿈
	//printf("%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
	
	IUnitObject::UpdatePosition();
	IUnitObject::UpdateKeyboardState();
	//static_cast <IUnitObject * >(g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetPosition()

	//마우스로 충돌 됬을 때!
	if ((CalcPickedPosition(m_pos, (WORD)(g_pMouse->GetPosition().x) , (WORD)(g_pMouse->GetPosition().y)) == true) && g_pMouse->ButtonDown(Mouse::LBUTTON))
	{
		static_cast <Cube *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY1))->m_vPosition.z += 1.5f;
		//구체를 넣고 렌더를 하지말자
	}

	//조명 예제
	if (GetAsyncKeyState('1') & 0x0001)
	{
		m_isTurnedOnLight = !m_isTurnedOnLight;
	}
	if (m_isTurnedOnLight)
	{
		D3DXVECTOR3 pos = m_pos;
		pos.y += 3.0f;
		D3DXVECTOR3 dir = m_forward;
		D3DXCOLOR c = BLUE;
		D3DLIGHT9 light = DXUtil::InitSpot(&dir, &pos, &c);
		
		//손전등의 시야각 변경하기
		light.Phi = D3DX_PI / 2;
		//D3DLIGHT9 light = DXUtil::InitPoint(&dir, &c);

		//광원을 만들었으면 세팅을 해주자.
		//0번 라이트
		g_pDevice->SetLight(10, &light);
	}
	//bool 값에 따라서 0번으로 지시한 광원을 껐다 켰다 컨트롤 해보기
	g_pDevice->LightEnable(10, m_isTurnedOnLight);
	//각각의 파츠들이 움직이는지 아닌지 상태를 판단해서 인자값 넘겨줄거야
	m_pRootParts->SetMovingState(IUnitObject::m_isMoving);
	m_pRootParts->Update();
	if (GetAsyncKeyState('Q') & 0x8000)
	{
		IUnitObject::m_isMoving = true;
		m_pos.x -= 0.5f;

	}
	else if (GetKeyState('E') & 0x8000)
	{
		IUnitObject::m_isMoving = true;
		m_pos.x += 0.5f;
	}

	//버텍스 벡터에 정면 벡터값이랑 값 넣어주기
	D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
	D3DXVECTOR3 temp1;
	D3DXVECTOR3 temp2;
	temp2= m_forward * 100;
	
	temp1 = m_pos;
	temp1.y = 5.0f;

	m_vecVertex[0].c = red;
	m_vecVertex[0].p = temp1;
	
	m_vecVertex[1].c = red;
	m_vecVertex[1].p = temp1 + temp2;

	Debug->AddText((int)m_vecVertex.size());
	Debug->EndLine();
}

void Cubeman::Render()
{
	m_pRootParts->Render();

	D3DXMatrixIdentity(&m_matWorld);
	//정면 방향 벡터 그림 그려보기
	////월드 매트릭스 설정해주기
	g_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pDevice->SetFVF(VERTEX_PC::FVF);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	//그릴 도형의 타입, 도형의 갯수, 정점 정보의 시작 주소, 정점의 크기
	//그라데이션 형식으로 그려짐.
	g_pDevice->SetTexture(0, NULL);
	g_pDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecVertex.size() / 2, &m_vecVertex[0], sizeof(VERTEX_PC));
}

bool Cubeman::CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY)
{
	//Ray ray = Ray::RayAtWorldSpace(screenX, screenY);
	//float minDist = FLT_MAX;
	//float intersectionDist;
	bool bIntersect = false;

	//D3DXVECTOR3 enemyPos = static_cast <IUnitObject * >(g_pObjMgr->FindObjectByTag(TAG_ENEMY1))->GetPosition();
	////printf("적 위치 : %f,%f,%f\n", enemyPos.x, enemyPos.y, enemyPos.z);

	//Debug->AddText("X 값" +to_string(m_forward.x)+ "Y 값" + to_string(m_forward.y) + "Z 값" + to_string(m_forward.z));
	//Debug->EndLine();

	//for (int i = 0; i < g_pObjMgr->FindObjectByTag(TAG_ENEMY1)->GetCubeVertex().size(); i += 3)
	//{
	//	if (ray.CalcIntersectTri_dir(&g_pObjMgr->FindObjectByTag(TAG_ENEMY1)->GetCubeVertex()[i].p, &intersectionDist, &m_forward,&m_pos))
	//	{
	//		if (intersectionDist < minDist)
	//		{
	//			bIntersect = true;
	//			minDist = intersectionDist;
	//			vOut = ray.m_pos + ray.m_dir * intersectionDist;
	//		}
	//	}
	//}

	//여기부터 구체 충돌 체크부분!!
	Ray r = Ray::RayAtWorldSpace(screenX, screenY);

	//for (auto p : m_vecBoundary)
	//{
	//	//p->isPicked = r.CalcIntersectSphere(p);
	//}
	BoundingSphere* sphere = NULL;
	float minDistance = FLT_MAX;
	float intersectionDistance;

	//몹 객체의 스피어 정보
	BoundingSphere* temp = static_cast <Cube *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY1))->GetSphere();

	temp->isPicked = false;
	if (r.CalcIntersectSphere(temp) == true)
	{
		intersectionDistance = D3DXVec3Length(&(temp->center - r.m_pos));
		//제일 앞 부분의 거리만 충돌 체크 표시
		if (intersectionDistance < minDistance)
		{
			minDistance = intersectionDistance;
			sphere = temp;
		}
	}
	
	if (sphere != NULL)
	{
		sphere->isPicked = true;
		bIntersect = true;
	}


	return bIntersect;
}

void Cubeman::UpdatePosition()
{
	m_rot += m_deltaRot * m_rotationSpeed;

	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_rot.y);
	//정면 방향 벡터 가져오자
	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);

	D3DXVECTOR3 targetPos;
	float basePosY = 0;

	bool isIntersected = true;
	float height = 0;

	if (m_isJumping)
	{
		m_currMoveSpeedRate = 0.7f;
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;//델타포스 z는 키보드로 w가 눌렸냐 안눌렸냐 값이 들어가있음!
		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		//이게 그냥 낙하 부분
		/*if (targetPos.y <= basePosY)
		{
			targetPos.y = basePosY;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}*/
		//그냥 내가 추가한거(낙하)
		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}
		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				//현재의 위치에서 높이 체크를 해준다.
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			//바닥위에 있으면 그대로 값 받아오기
			m_pos = targetPos;
		}
		// m_jumpPower < m_currGravity <- 이게 하강 중일때를 의미함!
		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//if (targetPos.y <= basePosY && ob->GetHeight(targetPos.y, targetPos) == false)
		//{
		//	targetPos.y = basePosY;
		//	m_isJumping = false;
		//	m_currGravity = 0;
		//	m_currMoveSpeedRate = 1.0f;
		//}
		////점프 상태에서 충돌 했을때
		//if (targetPos.y <= basePosY && ob->GetHeight(targetPos.y, targetPos) == true)
		//{
		//	targetPos.y *= 2.0f;
		//}
		//m_pos = targetPos;
	}
	else //m_isJumping == false;
	{
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate;
		
		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			//현재 높이랑 타겟y 의 차이가 커버리면 막아버리기
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}
		//그냥 내가 추가한거
		/*if (ob->GetHeight(m_pos.y, m_pos) == false)
		{
			m_pos.y = basePosY;
		}*/
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);


	//높낮이 컨트롤해보기
	//이게 그냥 평지고~
	//ob->GetHeight(m_pos.y, m_pos);

	m_matWorld = matRotY * matT;

	//Sq를 붙인 이유가 뭐냐면 단순히 엡실론보다 큰지 작은지 비교할라고 하는거임. Sq빠진건 말그대로 루트연산때문에 연산량이 든다.
	if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON || D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
	{
		m_isMoving = true;
	}
	else
		m_isMoving = false;
}
/*
큐브맨 파츠 부분 설명
팔을 원점기준으로 그릴게 아니라, 일단 기본값이 0,0,0 중심으로 그려져있을 테니까, 처음부터(로컬스페이스)내려서 그려주자
월드 스페이스로 갔을 때 몸통기준으로 양쪽에 붙어야 되니까, 월드 스페이스 기준으로(몸통의 월드스페이스) 움직이도록 하자
*/
void Cubeman::CreateAllParts()
{
	//기본 캐릭터 셋팅
	CubemanParts* pParts;
	//몸통
	m_pRootParts = new CubemanParts(몸);
	CreateParts(m_pRootParts, this, D3DXVECTOR3(0.0f, 3.0f, 0.0f),D3DXVECTOR3(1.0f, 1.0f, 0.5f), D3DXVECTOR3(0, 0, 0), uvBody);
	//머리
	pParts = new CubemanParts(머리);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.0f, 1.6f, 0.0f),D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0, 0, 0), uvHead);
	//왼팔
	pParts = new CubemanParts(왼팔, 0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-1.5f, 1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLArm);
	//오른팔
	pParts = new CubemanParts(오른팔, -0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRArm);
	//왼다리
	pParts = new CubemanParts(왼다리, -0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(-0.5f, -1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvLLeg);
	//오른다리
	pParts = new CubemanParts(오른다리, 0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(0.5f, -1.0f, 0.0f),D3DXVECTOR3(0.5f, 1.0f, 0.5f), D3DXVECTOR3(0, -1.0f, 0), uvRLeg);
	//총손잡이
	pParts = new CubemanParts(무기, -0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f), D3DXVECTOR3(0.2f, 0.2f, 0.1f), D3DXVECTOR3(0, -1.8f, .6f), uvBody);
	//총구
	pParts = new CubemanParts(무기, -0.1f);
	CreateParts(pParts, m_pRootParts, D3DXVECTOR3(1.5f, 1.0f, 0.0f), D3DXVECTOR3(0.2f, 0.5f, 0.2f), D3DXVECTOR3(0, -2.1f, .8f), uvBody);

}

void Cubeman::CreateParts(CubemanParts* &pParts, IDisplayObject* pParent, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 trans, vector<vector<int>> &vecUV)
{
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, scale.x, scale.y, scale.z);
	D3DXMatrixTranslation(&matT, trans.x, trans.y, trans.z);
	mat = matS * matT;
	pParts->Init(&mat, vecUV);
	pParts->SetPosition(&pos);
	pParent->AddChild(pParts);
}

