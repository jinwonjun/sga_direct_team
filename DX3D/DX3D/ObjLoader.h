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
	//��ũ�� OUT�� ����? ���۷����� ���ڴ�! OUT�̶� �ǹ̴� ���̷�Ʈ �������� ���� �ָ� ���ڷ� �Ѱ��شٴ� �ǹ�
	void Load(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<DrawingGroup * > & vecGroup);

	//�Ž��� �ε��غ���
	LPD3DXMESH LoadMesh(const char * filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<MTLTEX* > & vecMtlTex);
	//���� mtl���ϸ� �δ��ϴ� �Լ� �߰��ϱ�
	void LoadMtlLib(string fullPath);
	bool CompareStr(char * str1, const char * str2);
};

