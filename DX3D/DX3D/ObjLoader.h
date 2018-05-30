#pragma once

class DrawingGroup;

class ObjLoader
{
public:

	string m_filePath;
	map<string, MTLTEX * > m_mapMtlTex;



	ObjLoader();
	~ObjLoader();
	void LoadSurface(const char * fullPath, D3DXMATRIXA16 * pMat, OUT vector <D3DXVECTOR3> & vecVertex);
	//매크로 OUT은 뭘까? 레퍼런스로 쓰겠다! OUT이란 의미는 다이렉트 기준으로 받은 애를 인자로 넘겨준다는 의미
	void Load(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<DrawingGroup * > & vecGroup);

	//매쉬를 로드해보자
	LPD3DXMESH LoadMesh(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<MTLTEX* > & vecMtlTex);
	//따로 mtl파일만 로더하는 함수 추가하기
	void LoadMtlLib(string fullPath);
	bool CompareStr(char * str1, const char * str2);
};

