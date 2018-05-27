#include "stdafx.h"
#include "Ray.h"


Ray::Ray() : m_pos(0,0,0), m_dir(0,0,1)
{
}

Ray::~Ray()
{
}

Ray Ray::RayAtViewSpace(int x, int y)
{
	D3DVIEWPORT9 vp;
	g_pDevice->GetViewport(&vp);

	D3DXMATRIXA16 matProj;
	g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

	Ray ray;
	ray.m_dir.x = ((x * 2.0f) / vp.Width - 1.0f) / matProj._11;
	ray.m_dir.y = ((-y * 2.0f) / vp.Height + 1.0f) / matProj._22;

	return ray;
}

Ray Ray::RayAtWorldSpace(int x, int y)
{
	//��ũ�� x, y ��ǥ�� View �� �ִ� Ray ����
	Ray ray = Ray::RayAtViewSpace(x, y);

	//View �� �ִ� ray �� World �� ��ȯ
	D3DXMATRIXA16 matView, matInvView;
	g_pDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matInvView, NULL, &matView);

	D3DXVec3TransformCoord(&ray.m_pos, &ray.m_pos, &matInvView);
	D3DXVec3TransformNormal(&ray.m_dir, &ray.m_dir, &matInvView);
	D3DXVec3Normalize(&ray.m_dir, &ray.m_dir);

	return ray;
}

bool Ray::CalcIntersectSphere(BoundingSphere * pSphere)
{
	//��� ������ �־�ھ�!
	//����ϱ� ���� ���� ��ġ�� �������� �����ϱ�
	//D3DXVECTOR3 posTemp = m_pos - pSphere->center;

	//float qvDotTemp=0;
	//qvDotTemp = D3DXVec3Dot(&posTemp, &m_dir);
	//float squreTemp=0;
	//squreTemp = D3DXVec3LengthSq(&posTemp);
	//if ((qvDotTemp *qvDotTemp - squreTemp + (pSphere->radius) *(pSphere->radius)) >= 0)
	//{
	//	return true;
	//}
	//else
	//	return false;

	D3DXVECTOR3 localPos = m_pos - pSphere->center;
	float vv = D3DXVec3Dot(&m_dir, &m_dir);//�ڱ��ڽ��� ������ 1�ϼ�
	float qv = D3DXVec3Dot(&localPos, &m_dir);
	float qq = D3DXVec3Dot(&localPos, &localPos);
	float rr = pSphere->radius * pSphere->radius;

	//printf("%f\n", qv* qv - (qq - rr));
	//float caltemp = qv* qv - (qq - rr);

	//calculate.push_back(caltemp);
	//printf("%d\n", calculate.size());

	return qv* qv - (qq - rr) >= 0;
}

bool Ray::CalcIntersectTri(D3DXVECTOR3 * pStart, float * distance)
{
	return D3DXIntersectTri(pStart, pStart+1, pStart+2, &m_pos, & m_dir,NULL,NULL,distance);
}

bool Ray::CalcIntersectTri_dir(D3DXVECTOR3 * pStart, float * distance, D3DXVECTOR3 m_dir, D3DXVECTOR3 m_pos)
{
	return D3DXIntersectTri(pStart, pStart + 1, pStart + 2, &m_pos, &m_dir, NULL, NULL, distance);
}

/*
//����Ʈ -> �������� �����̽� -> �佺���̽�  �̵����� �⺻ �ڵ�
D3DVIEWPORT9 vp;
g_pDevice->GetViewport(&vp);

D3DXMATRIXA16 matProj;
g_pDevice->GetTransform(D3DTS_PROJECTION, &matProj);

m_dir.x = ((x* 2.0f) / vp.Width - 1.0f) / matProj._11;
m_dir.y = ((-y * 2.0f) / vp.Height + 1.0f) / matProj._22;
m_dir.z = 1;

D3DXMATRIXA16 matView, matInvView;
g_pDevice->GetTransform(D3DTS_VIEW, &matView);
D3DXMatrixInverse(&matInvView, NULL, &matView);
m_pos = D3DXVECTOR3(0,0,0);

D3DXVec3TransformCoord(&ray.m_pos, &ray.m_pos, &matInvView);
D3DXVec3TransformNormal(&ray.m_dir, &ray.m_dir, &matInvView);

D3DXVec3Normalize(&ray.m_dir, &ray.m_dir);

//�Ǻ����� ���ؼ� 0�̻��̸� �����ɷ� üũ���ֱ�
//(Q dot V)^2 - (V dot V) *(Q^2 - r^2) >= 0 �̸� true
//Q�� ������, V�� �𷺼�!
*/