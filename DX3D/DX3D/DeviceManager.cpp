#include "stdafx.h"
#include "DeviceManager.h"


DeviceManager::DeviceManager()
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
}


DeviceManager::~DeviceManager()
{
}

HRESULT DeviceManager::Init()
{
	//���� ������ ���ؼ� IDirect3D9 Interface�� �����͸� ȹ��.
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL) return E_FAIL;
	//D3DCAPS9�� GetDeviceCaps�� ���� �ϵ������ ������ ���� �� �ִ� ����ü��.
	D3DCAPS9 caps;
	int vp;

	//�� �׷��� ī���� ������ D3DCAPS9�� �޾ƿ���.
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	//�ϵ��� ����ó���� �����ϴ��� Ȯ���Ѵ�.
	//caps�� ������ �޾ƿͼ� ��� �����ϴ���, ��� �����ϴ����� üũ�ؼ� ���ش�.
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//�����ϴٸ� �ϵ��� �̿��� ���ؽ� ���μ���
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//�Ұ��� �ϴٸ� ����Ʈ��� �̿��� ���ؽ� ���μ���
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//D3D ���� �����ϱ�

	//D3D�� ������ ��� �ִ� ����ü
	//����̽��� �Ӽ��� �޾ƿ� �ڷ��� �����ϱ�
	D3DPRESENT_PARAMETERS d3dpp;
	//Ȥ�� memset�� �̿��� �ʱ�ȭ �����ϱ�
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));//�� ����ֱ�
	//�̷� Ư���� ���� ����̽��� ����Ŵ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//��¸�� �����ϱ�. ������ ����� true�� ����, ��ü ȭ���̶�� false.
	d3dpp.Windowed = true;

	//������� ���� ������ ����. ���� RGB + 8bit ���� ������ D3DFMT_X8R8G8B8�� ����Ѵ�.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//���̹��۸� �����ϴ� ��ü�� ����
	//true�� ���� �� Direct3D���� �ڵ����� �����Ѵ�.
	d3dpp.EnableAutoDepthStencil = TRUE;

	//32��Ʈ�� �Ҵ��ϰ� 24��Ʈ�� ���̹���, 8��Ʈ�� ���ٽ� ���ۿ� �Ҵ��Ѵ�.
	//���ٽ� ���۶�, Ư���� ȿ���� ���� ȭ�鿡 ��ġ�� �ʴ� ���۷�, ���� ���ۿ� ������ �ػ󵵸� ������.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//�̰��� �ǹ��ϴ� ����?! -> �̰��� ������ ������ ������ ���Ѵ�!
	//����Ʈ�� ��� ������ ���ش�!
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//���� ������ ���� ����̽� �����ϱ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, vp, &d3dpp, &m_pD3DDevice)))
	{
		return E_FAIL;
	}
}

LPDIRECT3DDEVICE9 DeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void DeviceManager::Destroy()
{
	if (m_pD3DDevice)
	{
		//ULONG�� ������ �Ǿ��ִ� ��ü ���� �˻��ϴ� �뵵.
		ULONG ul = m_pD3DDevice->Release();//delete ���� �ʰ� release��.

 //���� ���� �󿡼��� assert�� �������ؼ��� �Ⱦ��ٰ� �Ѵ�. �ٸ� ������� �����ϴ� �ڵ��� �ʿ���.

 //�ϴ� �𸣰����� �ּ�ó��

 //assert(ul == 0 && "����̽��� �̿��ؼ� ������ ��ü �� �Ҹ���� ���� ��ü�� �����մϴ�.");


 /*
 �������� �ΰ��� ���� -> delete�� ���� �ش޶�� ��û�� �ؾ��� �Ҽ� ����!
 ���� ī��Ʈ�� ���� ���ؼ�. ���� �ϳ��� ��ü�� �����, �� ��ü�� �̰� �������� �� �� �ִµ�, ��ü X �� ���� A�� B Ŭ���� �� �ٿ��� ���µ�,
 �Ҹ��� ����, A���� X��ü�� �Ҹ��Ϸ��� �Ҷ��ϸ�, B���� ���ٰ� ������ ���ű� ������, �̷� ���� ���� ���ؼ�, AŬ�������� X�� �Ҹ��Ҷ�� �� ��,
 ����ī��Ʈ�� �������Ѽ� �Ѵ� �Ҹ� ��ų�� ����ī��Ʈ�� ����, �� ����ī��Ʈ�� 0�� �Ǹ� �� �Ҹ� �� �ߴٴ� �Ҹ��ϱ� �� �� ����� �ȴ�.
 ���̷�ƮX �󿡼� �̹� �׷��� ������ �Ǿ��ֱ� ������, �츮�� ������ �ʿ�� ����.
 */
	}
	if (m_pD3D) m_pD3D->Release();
}

/*
������ �⺻���� ����ۿ� ����Ʈ ���� 2���� ���µ�, ȭ�鿡 ǥ���Ҷ��� ����Ʈ ���ۿ� ǥ���ϴ� �Ÿ� ����ۿ��� ������ ��Ƽ�
����Ʈ ���ۿ� �Ѱ���

���� ü�� = �ϳ��� ����Ʈ, �ϳ��� �����, �����͸� ��� �ٲ㼭 (�������� ������ �ƴ� ���������� ��������ν�, ���ۿ� ��� ������ ��� �ٲ���)
�����͸� ��ü�ϴϱ�, �޸� ī�ǰ� ����. swapeffectdiscard�� ���� �� ���� flipping �����̶��Ѵ�. (API �󿡼� ���� ���۸��� ����� ����)

*/