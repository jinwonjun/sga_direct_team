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

	//자유시점 후 초기화할 회전값
	float			tempRotX;
	float			tempRotY;

	//마우스 카메라 회전
	POINT			mCenter;
	RECT			mRc;
	float			mSensX;			//X 민감도, 클수록 느려짐
	float			mSensY;
	float			mSensStepX;		//민감도 조절 단위
	float			mSensStepY;
	float			mLimitX;		//마우스 제한 렉트 X
	float			mLimitY;
	float			mLimitDistance;
	bool			mRCCollCheck;	//마우스 충돌 체크 확인 변수
	int				sensLevel;		//민감도 레벨
	float			deltaRotY;

	//초기 카메라 조작
	bool			isStart;
	bool			isColl;

	//마우스 커서
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
	POINT GetMCenter() { return mCenter; }//중앙좌표 가져오기

	const D3DXVECTOR3& GetPosition() { return m_eye; }
	D3DXMATRIXA16* GetViewMatrix() { return &m_matView; }
	D3DXMATRIXA16* GetProjMatrix() { return &m_matProj; }
	D3DXMATRIXA16* GetViewProjMatrix() { return &(D3DXMATRIXA16)(m_matView * m_matProj); }
};

