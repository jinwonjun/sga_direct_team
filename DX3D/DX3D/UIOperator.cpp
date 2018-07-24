#include "stdafx.h"
#include "UIOperator.h"
#include "IUIObject.h"
#include "UIImage.h"
#include <cstring>

UIOperator* UIOperator::instance = NULL;



UIOperator * UIOperator::Get()
{
	if (instance == NULL)
		instance = new UIOperator();

	return instance;
}

void UIOperator::Delete()
{
	SAFE_DELETE(instance);

}



void UIOperator::Init()
{
	GetClientRect(g_hWnd, &clientRect);
	D3DXCreateSprite(g_pDevice, &pSprite);
	D3DXCreateSprite(g_pDevice, &Text_Bar_BackGround.m_pSprite);

	InitValkire();

	InitZealot();

	InitMutant();
	
	
	Init_TextBar_Frame();
	Init_TextBar_Background();

	CrossHeadMoving = false;
	ScaleHeadMoving = false;
	ShutCrossHeadMoving = true;
	ShutScaleHeadMoving = true;
	TextBar_Rendering = false;

	Mutant.ScreenOn = false;
	
}

void UIOperator::Update()
{
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	if (g_pKeyboard->KeyDown('C'))
	{
		TextBar_Rendering = true;
		CrossHeadMoving = true;
		Text_Bar_Frame.Str_ = L"이동을 위해서 \n W A S D 를 눌러보세요";
	}
	if (CrossHeadMoving)
	{
		CrossHeadMovingFunction(Zealot);
	}

	if (g_pKeyboard->KeyDown('V'))
	{
		TextBar_Rendering = true;
		ScaleHeadMoving = true;
		Text_Bar_Frame.Str_ = L"적을 소멸시켜라!";
	}

	if (g_pKeyboard->KeyDown('B'))
	{
		Mutant.ScreenOn = !Mutant.ScreenOn;
	}
	if (ScaleHeadMoving)
	{
		SacleHeadMovingFunction(Valkire);
	}
	//if (HeadMoving && Valkire.ScaleY < 1.0f)
			
	if (Valkire.ScreenOn)
	{
		ShutDownSacleHeadMovingFunction(Valkire);
	}
	
	if (Zealot.ScreenOn)
	{

		ShutDownCrossHeadMovingFunction(Zealot);
	}
	
	SAFE_UPDATE(Text_Bar_Frame.m_pRootUI);

}

void UIOperator::Render()
{
	g_pDevice->SetTexture(0, NULL);
	//pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	//g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	//g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	//g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	
	//pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	DrawValkire();
	DrawZealot();

	if (Mutant.ScreenOn)
	{
		DrawMutant();
	}

	if (TextBar_Rendering || Mutant.ScreenOn)
	{

		Text_Bar_Frame.m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		Text_Bar_Frame.m_pSprite->SetTransform(&Text_Bar_Frame.matWorld);
		Text_Bar_Frame.m_pButton->GetFinalRect(&Text_Bar_Frame.rect);
		SAFE_RENDER(Text_Bar_Frame.m_pRootUI);
		Text_Bar_Frame.m_pSprite->End();
		Draw_TextBar_Background();
	}


	//g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	

	//pSprite->End();

}

//void UIOperator::OnClick(UIButton * pSender)
//{
//
//}

void UIOperator::CrossHeadMovingFunction(Draw_UI_ &Chara)
{
	if (Chara.PointX + 10.f > clientRect.right * 0.02)
	{
		Chara.PointX = clientRect.right * 0.02;
	}

	if (Chara.PointX >= clientRect.right * 0.02)
	{
		Chara.PointX = clientRect.right * 0.02;
		CrossHeadMoving = false;
		Chara.ScreenOn = true;
		return;
	}


	Chara.PointX += 10.f;
	
}

void UIOperator::SacleHeadMovingFunction(Draw_UI_ & Chara)
{
	

	if (Chara.ScaleY >= 1.0f)
	{
		ScaleHeadMoving = false;
		Chara.ScreenOn = true;
		return;
	}

	Chara.ScaleY += 0.05f;
}

void UIOperator::ShutDownCrossHeadMovingFunction(Draw_UI_ & Chara)
{
	if (Chara.timer > 10)
	{
		Chara.PointX -= 10.f;

		if (Chara.PointX < -SizeofImage_Width)
		{

			Chara.ScreenOn = false;
			Chara.timer = 0;
			TextBar_Rendering = false;
			return;
		}
	}

	else
	{
		Chara.timer++;
	}

}

void UIOperator::ShutDownSacleHeadMovingFunction(Draw_UI_ & Chara)
{

	if (Chara.timer > 10)
	{
		Chara.ScaleY -= 0.05f;

		if (Chara.ScaleY <= 0.0f)
		{
			Chara.ScreenOn = false;
			Chara.timer = 0;
			TextBar_Rendering = false;
			return;
		}
	}

	else
	{
		Chara.timer++;
	}
}

void UIOperator::InitValkire()
{
	D3DXCreateSprite(g_pDevice, &Valkire.m_pSprite);

		//UIImage * pImage = new UIImage(Valkire.m_pSprite);
		//Valkire.m_pRootUI = pImage;

		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			_T("resources/images/Operator/Valkire_Head2.png"),   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width,
			D3DX_DEFAULT_NONPOW2,   //UINT Height,
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&Valkire.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&Valkire.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

		SizeofImage_Width = Valkire.m_imageInfo.Width;
		SizeofImage_Height = Valkire.m_imageInfo.Height;

		Valkire.PointX = clientRect.right * 0.02 + Valkire.m_imageInfo.Width / 2;
		Valkire.PointY = (OriginY / 2) + Valkire.m_imageInfo.Height / 2;
		Valkire.ScaleX = 1.0f;
		Valkire.ScaleY = 0.0f;
}

void UIOperator::InitZealot()
{

	D3DXCreateSprite(g_pDevice, &Zealot.m_pSprite);
	
		//UIImage * pImage = new UIImage(Zealot.m_pSprite);
		//Zealot.m_pRootUI = pImage;
	
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Operator/Zealot_Head2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Zealot.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Zealot.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	Zealot.PointX = -SizeofImage_Width;
	Zealot.PointY = OriginY / 2;
	Zealot.ScaleX = 1.0f;
	Zealot.ScaleY = 1.0f;
}

void UIOperator::InitMutant()
{
	D3DXCreateSprite(g_pDevice, &Mutant.m_pSprite);
	/*
		UIImage * pImage = new UIImage(Mutant.m_pSprite);
		Mutant.m_pRootUI = pImage;*/
	
	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Operator/Mutant_Head2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Mutant.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Mutant.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	Mutant.PointX = clientRect.right * 0.02 + (SizeofImage_Width/2);
	Mutant.PointY = OriginY / 2 + SizeofImage_Height / 2;
	Mutant.ScaleX = 1.0f;
	Mutant.ScaleY = 1.0f;

}

void UIOperator::DrawValkire()
{

	SetRect(&Valkire.m_Image_rc, 0, 0, Valkire.m_imageInfo.Width, Valkire.m_imageInfo.Height);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Valkire.PointX, Valkire.PointY, 0);
	D3DXMatrixScaling(&matS, Valkire.ScaleX, Valkire.ScaleY, 1);
	Valkire.matWorld = matS * matT;
	
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&Valkire.matWorld);
	pSprite->Draw(
		Valkire.m_pTex,
		&Valkire.m_Image_rc,
		&D3DXVECTOR3(Valkire.m_imageInfo.Width / 2, Valkire.m_imageInfo.Height / 2, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	pSprite->End();
}

void UIOperator::DrawZealot()
{

	SetRect(&Zealot.m_Image_rc, 0, 0, Zealot.m_imageInfo.Width, Zealot.m_imageInfo.Height);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Zealot.PointX, Zealot.PointY, 0);
	D3DXMatrixScaling(&matS, Zealot.ScaleX, Zealot.ScaleY, 1);
	Zealot.matWorld = matS * matT;


	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&Zealot.matWorld);
	pSprite->Draw(
		Zealot.m_pTex,
		&Zealot.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	pSprite->End();
}

void UIOperator::DrawMutant()
{

	SetRect(&Mutant.m_Image_rc, 0, 0, Mutant.m_imageInfo.Width, Mutant.m_imageInfo.Height);

	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, Mutant.PointX, Mutant.PointY, 0);
	D3DXMatrixScaling(&matS, Mutant.ScaleX, Mutant.ScaleY, 1);
	Mutant.matWorld = matS * matT;


	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&Mutant.matWorld);
	pSprite->Draw(
		Mutant.m_pTex,
		&Mutant.m_Image_rc,
		&D3DXVECTOR3(Mutant.m_imageInfo.Width / 2, Mutant.m_imageInfo.Height / 2, 0),
		&D3DXVECTOR3(0, 0, 0),
		WHITE);
	pSprite->End();

}

void UIOperator::Init_TextBar_Frame()
{
	D3DXCreateSprite(g_pDevice, &Text_Bar_Frame.m_pSprite);

	UIImage * pImage = new UIImage(Text_Bar_Frame.m_pSprite);
	Text_Bar_Frame.m_pRootUI = pImage;
	
	Text_Bar_Frame.m_pButton = new UIButton(Text_Bar_Frame_Dele, Text_Bar_Frame.m_pSprite, 1);
	Text_Bar_Frame.m_pButton->SetPosition(&D3DXVECTOR3(0, 0, 0));


	Text_Bar_Frame.m_pButton->SetTexture("resources/images/Operator/Text_Bar1.png",
		"resources/images/Operator/Text_Bar1.png",
		"resources/images/Operator/Text_Bar1.png");

	Text_Bar_Frame.Str_ = L"초기화를 위한 \n 입력입니다. 0000000000000000";
	//Text_Bar_Frame.Str_ = std::to_wstring(g_pUIManager->IronMan_Def);

	Text_Bar_Frame.m_pButton->SetText(g_pFontMgr->GetFont(FONT::NORMAL), Text_Bar_Frame.Str_.c_str(), WHITE);

	Text_Bar_Frame.m_pRootUI->AddChild(Text_Bar_Frame.m_pButton);


	Text_Bar_Frame.ScaleX = 1.f;
	Text_Bar_Frame.ScaleY = 1.f;
	Text_Bar_Frame.PointX = clientRect.right * 0.02 + (SizeofImage_Width);
	Text_Bar_Frame.PointY = (OriginY / 2);
	D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixScaling(&matS, Text_Bar_Frame.ScaleX, Text_Bar_Frame.ScaleY, 1);
	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, Text_Bar_Frame.PointX, Text_Bar_Frame.PointY, 0);
	Text_Bar_Frame.matWorld = matS * matT;


}

void UIOperator::Init_TextBar_Background()
{

	D3DXCreateTextureFromFileEx(
		g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
		_T("resources/images/Operator/Text_Bar2.png"),   //LPCTSTR pSrcFile,
		D3DX_DEFAULT_NONPOW2,   //UINT Width,
		D3DX_DEFAULT_NONPOW2,   //UINT Height,
		D3DX_DEFAULT,      //UINT MipLevels,
		0,               //DWORD Usage,
		D3DFMT_UNKNOWN,      //D3DFORMAT Format,
		D3DPOOL_MANAGED,   //D3DPOOL Pool
		D3DX_FILTER_NONE,   //DWORD Filter
		D3DX_DEFAULT,      //DWORD MipFilter
		D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
		&Text_Bar_BackGround.m_imageInfo,   //D3DXIMAGE_INFO *pSrcInfo
		NULL,         //PALETTEENTRY *pPalette
		&Text_Bar_BackGround.m_pTex);   //LPDIRECT3DTEXTURE9 *ppTexture

	Text_Bar_BackGround.ScaleX = 1.f;
	Text_Bar_BackGround.ScaleY = 1.f;
	Text_Bar_BackGround.PointX = clientRect.right * 0.02 + (SizeofImage_Width);
	Text_Bar_BackGround.PointY = (OriginY / 2);
	//D3DXMATRIXA16 matS;
	D3DXMatrixIdentity(&matS);

	D3DXMatrixScaling(&matS, Text_Bar_BackGround.ScaleX, Text_Bar_BackGround.ScaleY, 1);

	//D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);

	D3DXMatrixTranslation(&matT, Text_Bar_BackGround.PointX, Text_Bar_BackGround.PointY, 0);
	Text_Bar_BackGround.matWorld = matS * matT;
		
}

void UIOperator::Draw_TextBar_Background()
{

	
	SetRect(&Text_Bar_BackGround.m_Image_rc, 0, 0, Text_Bar_BackGround.m_imageInfo.Width, Text_Bar_BackGround.m_imageInfo.Height);

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	pSprite->SetTransform(&Text_Bar_BackGround.matWorld);
	pSprite->Draw(
		Text_Bar_BackGround.m_pTex,
		&Text_Bar_BackGround.m_Image_rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(105, 255, 255, 255));

	pSprite->End();


	//SetRect(&Text_Bar_BackGround.m_Image_rc, 0, 0, Text_Bar_BackGround.m_imageInfo.Width, Text_Bar_BackGround.m_imageInfo.Height);

	//pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//pSprite->SetTransform(&Text_Bar_BackGround.matWorld);
	//pSprite->Draw(
	//	Text_Bar_BackGround.m_pTex,
	//	&Text_Bar_BackGround.m_Image_rc,
	//	&D3DXVECTOR3(0, 0, 0),
	//	&D3DXVECTOR3(0, 0, 0),
	//	D3DCOLOR_ARGB(205, 255, 255, 255));
	//pSprite->End();

}
