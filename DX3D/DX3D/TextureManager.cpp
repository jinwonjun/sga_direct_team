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

	return GetTexture(string (fullPath));
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string fullPath)
{
	if (fullPath == "") return NULL;



	if (m_mapTexture.find(fullPath) == m_mapTexture.end())
	{
			D3DXCreateTextureFromFileA(g_pDevice, fullPath.c_str(),
				&m_mapTexture[fullPath]);	
	}	

	return m_mapTexture[fullPath];
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(CString fullPath)
{
	CT2CA pszConvertedAnsiString(fullPath);
	std::string _str(pszConvertedAnsiString);
	return GetTexture(_str);
}

LPDIRECT3DTEXTURE9 TextureManager::GetTexture(string fullPath, D3DXIMAGE_INFO info)
{
	
	if (fullPath == "") return NULL;

	if (m_mapTexture.find(fullPath) == m_mapTexture.end())
	{	

		CString cstr2 = CA2CT(fullPath.c_str());
		D3DXCreateTextureFromFileEx(
			g_pDevice,            //LPDIRECT3DDEVICE9 pDevice,
			cstr2,   //LPCTSTR pSrcFile,
			D3DX_DEFAULT_NONPOW2,   //UINT Width, 자동으로 스케일링을 해준다 2에n승이 아닐시
			D3DX_DEFAULT_NONPOW2,   //UINT Height, 자동으로 스케일링을 해준다 2에n승이 아닐시
			D3DX_DEFAULT,      //UINT MipLevels,
			0,               //DWORD Usage,
			D3DFMT_UNKNOWN,      //D3DFORMAT Format,
			D3DPOOL_MANAGED,   //D3DPOOL Pool
			D3DX_FILTER_NONE,   //DWORD Filter
			D3DX_DEFAULT,      //DWORD MipFilter
			D3DCOLOR_XRGB(255, 255, 255),   //D3DCOLOR ColorKey
			&info,   //D3DXIMAGE_INFO *pSrcInfo
			NULL,         //PALETTEENTRY *pPalette
			&m_mapTexture[fullPath]);   //LPDIRECT3DTEXTURE9 *ppTexture

	}

	return m_mapTexture[fullPath];



}

void TextureManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}
