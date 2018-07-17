#pragma once

#define g_pDeviceManager DeviceManager::GetInstance()
#define g_pDevice DeviceManager::GetInstance()->GetDevice()

class DeviceManager
{
private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

	DeviceManager();
	~DeviceManager();

public:
	static DeviceManager* GetInstance()
	{
		static DeviceManager instance;
		return &instance;
	}

	HRESULT				Init();
	LPDIRECT3DDEVICE9	GetDevice();
	void				Destroy();
};

/*
Direct3D는 가속 하드웨어를 이용하여 3D 세계 표현을 도와주는 그래픽 API이다.
Application - Direct3D - HAL(Hardware Abstraction Layer) - Graphics Hardware
Device에서 지원하지 않지만, D3D에서 제공하는 기능을 REF 장치를 통해서 이용할 수 있다.
D3DDECTYPE_HAL or D3DDEVTYPE_REF
REF장치는 순수 개발 목적으로 제공된다. DirectX SDK 에만 포함되어있으며, 상당히 느리다.

COM(Component Object Model) <- 마이크로소프트에서 발표한 규격같은 개념임. 여러 특징중에서 다이렉트 특징 중 하나 -> IUknown기능
IUnknown Interface를 상속받음. 세부적인 부분들은 내부적으로 작동하며 자신의 메모리 관리를 스스로 수행한다.
특수 함수를 통해서 객체의 포인터를 얻고 Release Method를 통해서 해제한다.(new, delete 키워드 사용안함.)


*/