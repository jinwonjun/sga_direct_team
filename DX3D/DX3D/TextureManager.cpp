#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(char * fullPath)
{
	if (fullPath == NULL) return NULL;

	return GetTexture(string(fullPath));
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string fullPath)
{
	if (fullPath == "") return NULL;

	if (m_mapTexture.find(fullPath) == m_mapTexture.end())
	{
		//없으면 생성해서 이름 그대로 넣어주기
		D3DXCreateTextureFromFileA(g_pDevice, fullPath.c_str(),&m_mapTexture[fullPath]);
	}
	return m_mapTexture[fullPath];
}

void TextureManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		//세컨이 텍스쳐 , 퍼스트가 스트링
		SAFE_RELEASE(it.second);
	}
	
	m_mapTexture.clear();
}
