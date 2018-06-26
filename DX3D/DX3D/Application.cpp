#include "stdafx.h"
#include "Application.h"


Application::Application()
{
}


Application::~Application()
{
}

void Application::Init()
{
	g_pDeviceManager->Init();
	g_pMouse->SetHandle(g_hWnd);
	g_pCamera->Init();
	g_pSceneManager->Init();
	
}

void Application::Destroy()
{
	g_pSceneManager->Destroy();

	//디바이스 매니져와 텍스쳐 매니져에서 지우는 텍스쳐를 
	//g_pObjMgr->Destroy();
	
	g_pMouse->Delete();
	g_pKeyboard->Delete();
	g_pTextureManager->Destroy();
	g_pFontMgr->Destroy();
	Debug->Destroy();
	g_pDeviceManager->Destroy();
}

void Application::Update()
{
	Debug->InitText();
	g_pTimeManager->Update();
	g_pKeyboardManager->Update();
	g_pMouse->Update();
	g_pKeyboard->Update();
	g_pSceneManager->Update();

	//카메라 업데이트를 여기서 돌림
	g_pCamera->Update();
}

void Application::Render()
{
	g_pDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

	g_pDevice->BeginScene();

	g_pSceneManager->Render();
	Debug->Print();

	if (GetAsyncKeyState('M') & 0x0001)
	{
		Debug->ShowMessageBox();
	}

	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

void Application::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	g_pSceneManager->WndProc(hWnd, message, wParam, lParam);
	g_pCamera->WndProc(hWnd, message, wParam, lParam);
	g_pMouse->InputProc(message, wParam, lParam);
}
