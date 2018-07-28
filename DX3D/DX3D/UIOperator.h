#pragma once
#include "IDisplayObject.h"
#include "UIButton.h"
#include "UIText.h"

#define g_pUIOperator UIOperator::Get()

class IUIObject;

struct Draw_UI_
{

	RECT m_Image_rc;
	RECT m_Sacle_rc;

	LPDIRECT3DTEXTURE9 m_pTex;
	D3DXIMAGE_INFO m_imageInfo;

	D3DXMATRIXA16 matWorld;
	LPD3DXSPRITE m_pSprite;
	IUIObject * m_pRootUI;

	float ScaleX; // �̹��� X ������
	float ScaleY; // �̹��� Y ������
	float PointX; // �̹��� ���� X ��ǥ
	float PointY; // �̹��� ���� Y ��ǥ

	int timer = 0;
	bool ScreenOn = false;
};

struct Button_UI_
{
	RECT rect;

	IUIObject * m_pRootUI;
	UIButton * m_pButton;
	LPD3DXSPRITE m_pSprite;
	D3DXMATRIXA16 matWorld;
	wstring Str_; // �̹��� ���� �޾��� str

	float ScaleX; // �̹��� X ������
	float ScaleY; // �̹��� Y ������
	float PointX; // �̹��� ���� X ��ǥ
	float PointY; // �̹��� ���� Y ��ǥ

	int timer = 0;
	bool ScreenOn = false;
};



class UIOperator 
{
private:

	static UIOperator* instance;

	RECT clientRect;
	POINT mousePoint;
	D3DXMATRIXA16 matR, matT,matS;

	LPD3DXSPRITE pSprite;

	bool CrossHeadMoving; // �Ӹ� �̹��� �̵��ϱ� ���� Ʈ����
	bool ShutCrossHeadMoving;
	
	bool ScaleHeadMoving;
	bool ShutScaleHeadMoving;

	float SizeofImage_Width;
	float SizeofImage_Height;


	void InitValkire();
	void InitZealot();
	void InitMutant();
	void DrawValkire();
	void DrawZealot();
	void DrawMutant();
	void Init_TextBar_Frame();
	void Init_TextBar_Background();
	void Draw_TextBar_Background();
	bool TextBar_Rendering;

public:

	static UIOperator* Get();
	static void Delete();


	Draw_UI_ Valkire;
	Draw_UI_ Zealot;
	Draw_UI_ Mutant;
	Draw_UI_ RedScreen;
	Draw_UI_ RedScreen2;

	Draw_UI_ ShotEffetc; 

	int RedScreen_Alpha1;
	int RedScreen_Alpha2;
	int RedScreen_Alpha3;

	bool ScreenEffectOn;


	Button_UI_ Text_Bar_Frame;
	IUIButtonDelegate * Text_Bar_Frame_Dele;

	Draw_UI_ Text_Bar_BackGround;

	int OperatorTimer_Tutorial;
	int OperatorTimer_Tutorial_Text2;
	int OperatorTimer_Tutorial_Text2_1;

	bool OperatorTrigger_Tutorial_Move_valkire;
	bool OperatorTrigger_Tutorial_Move_zealot;
	bool OperatorTrigger_Tutorial_Move_Mutant;

	bool BattleOn_Zealot;
	bool BattleOn_Mutant;

	
	bool TimerOnValikre;
	int ValkireTimer;
	int ZealotTimer;
	int MutantTimer;

	void CrossHeadMovingFunction(Draw_UI_ &Chara);
	void SacleHeadMovingFunction(Draw_UI_ &Chara);
	

	void ShutDownCrossHeadMovingFunction(Draw_UI_ &Chara);
	void ShutDownSacleHeadMovingFunction(Draw_UI_ &Chara);





	// IDisplayObject��(��) ���� ��ӵ�
	void Init();
	void Update();
	void Render();

	// IUIButtonDelegate��(��) ���� ��ӵ�
	//virtual void OnClick(UIButton * pSender) override;
};

