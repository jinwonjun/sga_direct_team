#pragma once

class DrawingGroup;

class ObjLoader
{
public:

	string m_filePath;
	map<string, MTLTEX * > m_mapMtlTex;
	vector<VERTEX_PNT>		vecPNT;


	ObjLoader();
	~ObjLoader();
	//기존 원본 로드기능
	void		Load(const char * filePath, const char * fileName, D3DXMATRIXA16* pMat, OUT vector<DrawingGroup*> &vecGroup);
	//서페이스 만들기 기능
	void		CreateSurface(OUT vector<D3DXVECTOR3> &vecVertex);
	
	void LoadSurface(const char * fullPath, D3DXMATRIXA16 * pMat, OUT vector <D3DXVECTOR3> & vecVertex);
	//매크로 OUT은 뭘까? 레퍼런스로 쓰겠다! OUT이란 의미는 다이렉트 기준으로 받은 애를 인자로 넘겨준다는 의미
	void LoadNoneMtl(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<DrawingGroup * > & vecGroup);
	//(f가 3개인 매쉬)
	LPD3DXMESH LoadF_Tri_Mesh(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<MTLTEX* > & vecMtlTex);
	//매쉬를 로드해보자(f가 4개인 매쉬)
	LPD3DXMESH LoadMesh(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<MTLTEX* > & vecMtlTex);
	//따로 mtl파일만 로더하는 함수 추가하기
	void LoadMtlLib(string fullPath);
	bool CompareStr(char * str1, const char * str2);
};

