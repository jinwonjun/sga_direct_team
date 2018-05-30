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
Direct3D�� ���� �ϵ��� �̿��Ͽ� 3D ���� ǥ���� �����ִ� �׷��� API�̴�.
Application - Direct3D - HAL(Hardware Abstraction Layer) - Graphics Hardware
Device���� �������� ������, D3D���� �����ϴ� ����� REF ��ġ�� ���ؼ� �̿��� �� �ִ�.
D3DDECTYPE_HAL or D3DDEVTYPE_REF
REF��ġ�� ���� ���� �������� �����ȴ�. DirectX SDK ���� ���ԵǾ�������, ����� ������.

COM(Component Object Model) <- ����ũ�μ���Ʈ���� ��ǥ�� �԰ݰ��� ������. ���� Ư¡�߿��� ���̷�Ʈ Ư¡ �� �ϳ� -> IUknown���
IUnknown Interface�� ��ӹ���. �������� �κе��� ���������� �۵��ϸ� �ڽ��� �޸� ������ ������ �����Ѵ�.
Ư�� �Լ��� ���ؼ� ��ü�� �����͸� ��� Release Method�� ���ؼ� �����Ѵ�.(new, delete Ű���� ������.)


*/