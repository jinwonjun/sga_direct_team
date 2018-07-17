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
	//버전 정보를 통해서 IDirect3D9 Interface의 포인터를 획득.
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL) return E_FAIL;
	//D3DCAPS9는 GetDeviceCaps로 현재 하드웨어의 정보를 얻을 수 있는 구조체다.
	D3DCAPS9 caps;
	int vp;

	//주 그래픽 카드의 정보를 D3DCAPS9에 받아오기.
	if (FAILED(m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps)))
	{
		return E_FAIL;
	}
	//하드웨어가 정점처리를 지원하는지 확인한다.
	//caps의 정보를 받아와서 어떤걸 지원하는지, 어떤걸 지원하는지를 체크해서 써준다.
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//가능하다면 하드웨어를 이용한 버텍스 프로세싱
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		//불가능 하다면 소프트웨어를 이용한 버텍스 프로세싱
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	//D3D 정보 설정하기

	//D3D의 정보를 담고 있는 구조체
	//디바이스의 속성을 받아올 자료형 선언하기
	D3DPRESENT_PARAMETERS d3dpp;
	//혹은 memset을 이용한 초기화 설정하기
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));//값 비워주기
	//이런 특성을 갖는 디바이스를 만들거다
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//출력모드 설정하기. 윈도우 모드라면 true값 쓰고, 전체 화면이라면 false.
	d3dpp.Windowed = true;

	//백버퍼의 포멧 형식을 지정. 보통 RGB + 8bit 예약 형식의 D3DFMT_X8R8G8B8를 사용한다.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	//깊이버퍼를 관리하는 주체를 설정
	//true로 지정 시 Direct3D에서 자동으로 관리한다.
	d3dpp.EnableAutoDepthStencil = TRUE;

	//32비트를 할당하고 24비트는 깊이버퍼, 8비트는 스텐실 버퍼에 할당한다.
	//스텐실 버퍼란, 특수한 효과를 위한 화면에 비치지 않는 버퍼로, 깊이 버퍼와 동일한 해상도를 가진다.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//이것이 의미하는 것은?! -> 이것을 넣으면 프레임 관리를 못한다!
	//디폴트로 써야 관리를 해준다!
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//설정 정보를 토대로 디바이스 생성하기
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
		//ULONG은 생성이 되어있는 객체 수를 검사하는 용도.
		ULONG ul = m_pD3DDevice->Release();//delete 쓰지 않고 release씀.

 //실제 배포 상에서는 assert를 어지간해서는 안쓴다고 한다. 다른 방법으로 구현하는 코딩이 필요함.

 //일단 모르겠으니 주석처리

 //assert(ul == 0 && "디바이스를 이용해서 생성한 객체 중 소멸되지 않은 객체가 존재합니다.");


 /*
 개념적인 두개의 차이 -> delete는 해제 해달라고 요청을 해야지 할수 있음!
 참조 카운트를 쓰기 위해서. 무언가 하나의 객체를 만들고, 그 객체를 이곳 저곳에서 쓸 수 있는데, 객체 X 한 개가 A와 B 클래스 둘 다에서 쓰는데,
 소멸할 적에, A에서 X객체를 소멸하려고 할라하면, B에서 쓰다가 에러가 날거기 때문에, 이런 것을 막기 위해서, A클래스에서 X를 소멸할라고 할 때,
 참조카운트를 증가시켜서 둘다 소멸 시킬때 참조카운트를 감소, 즉 참조카운트가 0이 되면 다 소멸 콜 했다는 소리니까 그 때 지우면 된다.
 다이렉트X 상에서 이미 그렇게 구현이 되어있기 때문에, 우리가 구현할 필요는 없다.
 */
	}
	if (m_pD3D) m_pD3D->Release();
}

/*
버퍼의 기본개념 백버퍼와 프론트 버퍼 2개를 쓰는데, 화면에 표시할때는 프론트 버퍼에 표시하는 거를 백버퍼에서 정보를 담아서
프론트 버퍼에 넘겨줌

스왑 체인 = 하나는 프론트, 하나는 백버퍼, 포인터를 계속 바꿔서 (고정적인 역할이 아닌 가변적으로 사용함으로써, 버퍼에 담긴 정보를 계속 바꿔줌)
포인터만 교체하니깐, 메모리 카피가 없다. swapeffectdiscard를 썼을 때 보통 flipping 개념이라한다. (API 상에서 더블 버퍼링과 비슷한 개념)

*/