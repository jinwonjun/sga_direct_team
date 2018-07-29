#include "stdafx.h"
#include "Frustum.h"
#include "EnemyManager.h"
#include "Enemy.h"

Frustum::Frustum()
{

	m_pMesh = NULL;
}


Frustum::~Frustum()
{
	SAFE_RELEASE(m_pMesh);
}

void Frustum::Init()
{
	/*
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 1));//좌상후
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 1));//우상후
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 0));//좌상전
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 0));//우상전

	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 1));//좌하후
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 1));//우하후
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 0));//좌하전
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 0));//우하전

	m_vecWorldVtx.resize(8);
	m_vecPlane.resize(6);

	//구체 그려주기 

	int dim = 6;
	float offset = 4;
	float half = (dim - 1) * offset / 2.0f;

	float radius = 0.6f;

	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pMesh, NULL);

	m_vecBoundary.reserve(dim * dim * dim);

	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			for (int k = 0; k < dim; k++)
			{
				BoundingSphere* s = new BoundingSphere(
					D3DXVECTOR3(i * offset - half,
						j * offset - half, k * offset - half), radius);
				m_vecBoundary.push_back(s);
			}
		}
	}
	
	UpdateFrustum();
	*/

	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 1));//좌상후
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 1));//우상후
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, 1, 0));//좌상전
	m_vecProjVtx.push_back(D3DXVECTOR3(1, 1, 0));//우상전

	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 1));//좌하후
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 1));//우하후
	m_vecProjVtx.push_back(D3DXVECTOR3(-1, -1, 0));//좌하전
	m_vecProjVtx.push_back(D3DXVECTOR3(1, -1, 0));//우하전

	m_vecWorldVtx.resize(8);
	m_vecPlane.resize(6);
}

void Frustum::Update()
{
	//if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	//{
	//	UpdateFrustum();
	//}
	/*
	if (GetKeyState(VK_SPACE) & 0x0001)
	{
		UpdateFrustum();
	}
	*/

	UpdateFrustum();

	EnemyManager* em = static_cast <EnemyManager *> (g_pObjMgr->FindObjectByTag(TAG_ENEMY));
	for (auto p : em->GetVecEnemy())
	{
		BoundingSphere* enemySphere = p->GetSphere();
		if (IsSphereInsideFrustum(enemySphere))
		{
			//FrustumCulling 안에 들어있으면...
			p->SetFrustumRender(true);
		}
		else
		{
			p->SetFrustumRender(false);
		}
	}
}

void Frustum::Render()
{
	/*
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetMaterial(&DXUtil::BLUE_MTRL);

	for (auto p : m_vecBoundary)
	{
		if (IsSphereInsideFrustum(p))
		{
			D3DXMATRIXA16 mat;
			D3DXMatrixTranslation(&mat, p->center.x,
				p->center.y, p->center.z);
			g_pDevice->SetTransform(D3DTS_WORLD, &mat);
			g_pDevice->SetTexture(0, NULL);

			m_pMesh->DrawSubset(0);
		}
	}*/

	//위에와 같은거임
	//for (int i = 0; i < m_vecpBoundary.size(); i++)
	//{
	//   if (IsSphereInsideFrustum(m_vecpBoundary[i]))
	//   {
	//      D3DXMATRIXA16 mat;
	//      D3DXMatrixTranslation(&mat, m_vecpBoundary[i]->center.x,
	//         m_vecpBoundary[i]->center.y, m_vecpBoundary[i]->center.z);
	//      g_pDevice->SetTransform(D3DTS_WORLD, &mat);
	//      g_pDevice->SetTexture(0, NULL);
	//      m_pMesh->DrawSubset(0);
	//      
	//   }
	//}
}

void Frustum::UpdateFrustum()
{
	D3DXMATRIXA16 matProj, matView;
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pDevice->GetTransform(D3DTS_VIEW, &matView);

	for (size_t i = 0; i < m_vecWorldVtx.size(); i++)
	{
		D3DXVec3Unproject(&m_vecWorldVtx[i], &m_vecProjVtx[i],
			NULL, &matProj, &matView, NULL);

		//전평면//좌상전//우상전//좌하전
		D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVtx[2],
			&m_vecWorldVtx[3], &m_vecWorldVtx[6]);

		//후평면//우상후//좌상후//우하후
		D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVtx[1],
			&m_vecWorldVtx[0], &m_vecWorldVtx[5]);

		//좌평면
		D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVtx[0],
			&m_vecWorldVtx[2], &m_vecWorldVtx[4]);

		//우평면
		D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVtx[3],
			&m_vecWorldVtx[1], &m_vecWorldVtx[7]);

		//상평면
		D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVtx[0],
			&m_vecWorldVtx[1], &m_vecWorldVtx[2]);

		//하평면
		D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVtx[6],
			&m_vecWorldVtx[7], &m_vecWorldVtx[4]);

	}
}

bool Frustum::IsSphereInsideFrustum(BoundingSphere * pSphere)
{
	for (auto p : m_vecPlane)
	{
		//앞쪽 보다 클떄?
		//센터에서 p 면까지의 거리
		if (D3DXPlaneDotCoord(&p, &pSphere->center) > pSphere->radius)
		{
			//면의 앞쪽에 위치하고 center와 면의 거리가 radius 보다 크다..
			//center가 면의 앞쪽에 위치하고
			//center 와 면의 거리가 radius보다 크다
			return false;
		}
	}
	return true;
}