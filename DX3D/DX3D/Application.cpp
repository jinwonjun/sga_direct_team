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
	Shaders::Get()->Init();
	g_pSoundManager->Init();
	g_pSceneManager->Init();
	//g_pItem->ItemTable();
	g_pUIManager->Init();
	g_pInventory->Init();
	g_pItem->init();
	g_pUIOperator->Init();
	g_pShop->Init();

	//g_pStatus->Init();

	
}

void Application::Destroy()
{
	Shaders::Get()->Delete();
	g_pSceneManager->Destroy();

	//디바이스 매니져와 텍스쳐 매니져에서 지우는 텍스쳐를 
	//g_pObjMgr->Destroy();
	
	g_pMouse->Delete();
	g_pKeyboard->Delete();
	g_pTextureManager->Destroy();
	g_pFontMgr->Destroy();
	Debug->Destroy();
	g_pDeviceManager->Destroy();
	g_pInventory->Delete();
	g_pUIOperator->Delete();
	g_pShop->Delete();

	//g_pStatus->Delete();
	g_pUIManager->Delete();

	g_pSoundManager->Destroy();
}

void Application::Update()
{
	Debug->InitText();
	g_pTimeManager->Update();
	g_pKeyboardManager->Update();
	g_pMouse->Update();
	g_pKeyboard->Update();
	g_pSceneManager->Update();
	g_pSoundManager->Update();
	g_pShop->Update();

	//카메라 업데이트를 여기서 돌림
	g_pCamera->Update();
	g_pInventory->Update();
	g_pUIManager->Update();
	g_pUIOperator->Update();
//	g_pStatus->Update();

}

void Application::Render()
{
	g_pDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(50, 50, 50), 1.0f, 0);

	g_pDevice->BeginScene();

	g_pSceneManager->Render();
	Debug->Print();

	g_pInventory->Render();
	g_pUIOperator->Render();
	g_pUIManager->Render();
	g_pShop->Render();

//	g_pStatus->Render();

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
