#pragma once
#include "IScene.h"

class ObjMap;
class Cubeman;
class AseCharacter;


class SceneObjMap :
	public IScene
{
private :
	ObjMap * m_pObjMAp;

	Cubeman * m_pCubeman;

	AseCharacter * m_pAseCharacter;

public:
	SceneObjMap();
	~SceneObjMap();

	// IScene을(를) 통해 상속됨
	//맵 정보를 갖고 있을 obj컨테이너를 만들어야함! -> ObjMap 클래스를 생성
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

