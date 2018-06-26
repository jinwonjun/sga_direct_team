#include "stdafx.h"
#include "SceneManager.h"
#include "IScene.h"
#include "SceneGrid.h"
#include "SceneObjMap.h"
#include "SceneHeightmap.h"

#include "Scene_UI.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	m_vecScene.push_back(new SceneGrid());
	m_vecScene.push_back(new SceneObjMap());
	m_vecScene.push_back(new SceneHeightmap());
	m_vecScene.push_back(new Scene_UI());

	//주석을 풀면 캐릭터는 돌아가긴하는데, 렌더만 안되는 상태기 때문에 키가 안먹히는 상황이 생김
	//SetCurrentScene(SCENE_GRID);
	//SetCurrentScene(SCENE_OBJMAP);
	//SetCurrentScene(SCENE_HEIGHTMAP);
	SetCurrentScene(SCENE_UI);
}

void SceneManager::Destroy()
{
	for (auto p : m_vecScene)
	{
		SAFE_RELEASE(p);
	}
}

void SceneManager::Update()
{
	SAFE_UPDATE(m_pCurrScene);
}

void SceneManager::Render()
{
	SAFE_RENDER(m_pCurrScene);
}

void SceneManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCurrScene)
		m_pCurrScene->WndProc(hWnd, message, wParam, lParam);
}

void SceneManager::SetCurrentScene(size_t index)
{
	if (index >= m_vecScene.size()) return;

	IScene* pScene = m_vecScene[index];
	if (pScene)
	{
		pScene->Init();
		m_pCurrScene = pScene;
	}
}
