#pragma once

#define g_pCamera Camera::GetInstance()

class Camera
{
	SINGLETON(Camera)
private:


	//D3DXVECTOR3		m_eye;
	//D3DXVECTOR3		m_lookAt;
	//D3DXVECTOR3		m_up;
	D3DXMATRIXA16	m_matView;
	D3DXMATRIXA16	m_matProj;
	float			m_basePosX;
	float			m_basePosY;
	float			m_distance;
	//float			m_rotX;
	//float			m_rotY;
	bool			m_isLbuttonDown;
	POINT			m_ptPrevMouse;
	D3DXVECTOR3 *	m_pTarget;

	//�������� �� �ʱ�ȭ�� ȸ����
	float			tempRotX;
	float			tempRotY;

	//���콺 ī�޶� ȸ��
	POINT			mCenter;
	RECT			mRc;
	float			mSensX;			//X �ΰ���, Ŭ���� ������
	float			mSensY;
	float			mSensStepX;		//�ΰ��� ���� ����
	float			mSensStepY;
	float			mLimitX;		//���콺 ���� ��Ʈ X
	float			mLimitY;
	float			mLimitDistance;
	bool			mRCCollCheck;	//���콺 �浹 üũ Ȯ�� ����
	int				sensLevel;		//�ΰ��� ����
	float			deltaRotY;

	//�ʱ� ī�޶� ����
	bool			isStart;
	bool			isColl;

	//���콺 Ŀ��
	bool			UIopen;
public:

	float			m_rotX;
	float			m_rotY;
	D3DXVECTOR3		m_eye;
	D3DXVECTOR3		m_lookAt;
	D3DXVECTOR3		m_up;

	D3DXVECTOR3		m_lookatTemp;
	D3DXVECTOR3		m_eyeTemp;

	void Init();
	void Update();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(D3DXVECTOR3* pTarget) { m_pTarget = pTarget; }
	POINT GetMCenter() { return mCenter; }//�߾���ǥ ��������

	const D3DXVECTOR3& GetPosition() { return m_eye; }
	D3DXMATRIXA16* GetViewMatrix() { return &m_matView; }
	D3DXMATRIXA16* GetProjMatrix() { return &m_matProj; }
	D3DXMATRIXA16* GetViewProjMatrix() { return &(D3DXMATRIXA16)(m_matView * m_matProj); }
};

