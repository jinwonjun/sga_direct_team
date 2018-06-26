#include "stdafx.h"
#include "ObjLoader.h"
#include "DrawingGroup.h"

const int TOKEN_SIZE = 128;

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::Load(const char * filePath, const char * fileName, D3DXMATRIXA16 * pMat, OUT vector<DrawingGroup*>& vecGroup)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR3> vecN;
	vector<D3DXVECTOR2> vecT;
	vector<VERTEX_PNT> vecPNT;
	//string mtlName;
	//char szToken[TOKEN_SIZE];

	//m_filePath = filePath;

	//std::ifstream fin;
	//fin.open(m_filePath + fileName);

	string mtlName;

	char szToken[128];
	ifstream fin;//이 변수로 파일을 읽을거야

	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;

	fin.open(fullPath);

	if (fin.is_open() == false)
		assert(false && "fin.is_open() == false");

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "mtllib"))
		{
			fin >> szToken;
			LoadMtlLib(m_filePath + szToken);
		}
		else if (CompareStr(szToken, "g"))
		{
			if (vecPNT.empty()) continue;

			DrawingGroup* pGroup = new DrawingGroup;
			pGroup->SetVertexBuffer(vecPNT);
			pGroup->SetMtlTex(m_mapMtlTex[mtlName]);
			vecGroup.push_back(pGroup);

			vecPNT.clear();
		}
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, TOKEN_SIZE);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y;
			fin.getline(szToken, TOKEN_SIZE);
			sscanf_s(szToken, "%f %f *%f", &x, &y);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, TOKEN_SIZE);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3][3];
			fin.getline(szToken, TOKEN_SIZE);

			sscanf_s(szToken, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; ++i)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}
		}
	}

	m_mapMtlTex.clear();
	fin.close();
}

void ObjLoader::CreateSurface(OUT vector<D3DXVECTOR3>& vecVertex)
{
	vecVertex.reserve(vecPNT.size() / 3);
	for (size_t i = 0; i < vecPNT.size(); i += 3)
	{
		D3DXVECTOR3 normal;
		DXUtil::ComputeNormal(&normal, &vecPNT[i].p, &vecPNT[i + 1].p, &vecPNT[i + 2].p);
		if (D3DXVec3Dot(&normal, &D3DXVECTOR3(0, 1, 0)) > 0.4f)
		{
			vecVertex.push_back(vecPNT[i].p);
			vecVertex.push_back(vecPNT[i + 1].p);
			vecVertex.push_back(vecPNT[i + 2].p);
		}
	}
}

void ObjLoader::LoadSurface(const char * fullPath, D3DXMATRIXA16 * pMat, OUT vector<D3DXVECTOR3>& vecVertex)
{
	vector<D3DXVECTOR3> vecP;
	

	char szToken[128];
	ifstream fin;//이 변수로 파일을 읽을거야

	fin.open(fullPath);

	if (fin.is_open() == false) return;
	//파일의 끝 까지
	while (fin.eof() == false)
	{
		//단어 단위로 읽어서 문자 비교
		fin >> szToken;

		if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &aIndex[0], &aIndex[1], &aIndex[2]);
			for (int i = 0; i < 3; i++)
			{
				D3DXVECTOR3 v = vecP[aIndex[i] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&v, &v, pMat);
				}
				vecVertex.push_back(v);
			}
		}
	}//end of Fileread

	fin.close();
}

void ObjLoader::LoadNoneMtl(const char * filePath,const char * fileName, D3DXMATRIXA16 * pMat, OUT vector<DrawingGroup * >& vecGroup)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR3> vecN;
	vector<D3DXVECTOR2> vecT;
	vector<VERTEX_PNT> vecPNT;
	//머테리얼이름
	string mtlName;

	char szToken[128];
	ifstream fin;//이 변수로 파일을 읽을거야
	 
	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;
	
	fin.open(fullPath);

	if (fin.is_open() == false) return;
	//파일의 끝 까지
	while (fin.eof() == false)
	{
		//단어 단위로 읽어서 문자 비교
		fin >> szToken;


		if (CompareStr(szToken, "mtllib"))
		{
			string fileName;
			fin >> fileName;
			fileName = m_filePath + "/" + fileName;

			LoadMtlLib(fileName.c_str());
		}
		else if (CompareStr(szToken, "g"))
		{
			//그룹 생성시에 버텍스가 비어있으면 건너뛰기
			if (vecPNT.empty())continue;

			DrawingGroup * pGroup = new DrawingGroup;
			pGroup->SetVertexBuffer(vecPNT);
			//참조를 두 군데에서 하기 때문에 레퍼런스 추가 함수 호출하기
			//mtl파일 없으면 밑에 두 줄 주석처리하기
			//pGroup->SetMtlTex(m_mapMtlTex[mtlName]);
			//m_mapMtlTex[mtlName]->AddRef();
			vecGroup.push_back(pGroup);
			//그룹을 만들었으면 지워주기
			vecPNT.clear();
		}
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			//sscanf_s(szToken, "%f %f *%f", &x, &y);//형식 지정자 앞에 * 붙이면, 값을 받지 않겠다 라는 의미!
			sscanf_s(szToken, "%f %f", &x, &y);//형식 지정자 앞에 * 붙이면, 값을 받지 않겠다 라는 의미!
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			//현재 그룹에 사용할 머테리얼 네임 지정하기
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3][3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%d/%d %d/%d/%d %d/%d/%d", &aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
															&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
															&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);
			for (int i = 0; i < 3; i++)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}
		}
	}//end of Fileread

	for (auto p : m_mapMtlTex)
	{
		SAFE_RELEASE(p.second);
	}
	//이렇게 되면 그룹을 갖고 있는 참조카운트가 1개만 된다!
	m_mapMtlTex.clear();
	fin.close();
	//크기 : 139
	//printf("vecgroup size : %d\n", vecGroup.size());
}

LPD3DXMESH ObjLoader::LoadMesh(const char * filePath, const char * fileName, D3DXMATRIXA16 * pMat, OUT vector<MTLTEX*>& vecMtlTex)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR3> vecN;
	vector<D3DXVECTOR2> vecT;
	vector<VERTEX_PNT> vecPNT;
	vector<DWORD> vecAttBuf;//어트리뷰트 정보를 담아줄거임
	//머테리얼이름
	string mtlName;

	char szToken[128];
	ifstream fin;//이 변수로 파일을 읽을거야

	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;
	fin.open(fullPath);

	if (fin.is_open() == false) return NULL;
	//파일의 끝 까지
	while (fin.eof() == false)
	{
		//단어 단위로 읽어서 문자 비교
		fin >> szToken;


		if (CompareStr(szToken, "mtllib"))
		{
			string fileName;
			fin >> fileName;
			fileName = m_filePath + "/" + fileName;

			LoadMtlLib(fileName.c_str());

			vecMtlTex.resize(m_mapMtlTex.size());
			for (auto p : m_mapMtlTex)
			{
				vecMtlTex[p.second->id] = p.second;
			}

		}
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f *%f", &x, &y);//형식 지정자 앞에 * 붙이면, 값을 받지 않겠다 라는 의미!
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			//현재 그룹에 사용할 머테리얼 네임 지정하기
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[4][3];
			memset(&aIndex, 0, sizeof(int) * 4 * 3);
			fin.getline(szToken, TOKEN_SIZE);

			sscanf_s(szToken, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2],
				&aIndex[3][0], &aIndex[3][1], &aIndex[3][2]);

			for (int i = 0; i < 3; ++i)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}
			vecAttBuf.push_back(m_mapMtlTex[mtlName]->id);	//추가

			if (aIndex[3][0] > 0)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (i == 1) continue;
					VERTEX_PNT pnt;
					pnt.p = vecP[aIndex[i][0] - 1];
					pnt.t = vecT[aIndex[i][1] - 1];
					pnt.n = vecN[aIndex[i][2] - 1];

					if (pMat)
					{
						D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
						D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
					}
					vecPNT.push_back(pnt);
				}
				vecAttBuf.push_back(m_mapMtlTex[mtlName]->id);	//추가
			}

		}
	}//end of Fileread

	m_mapMtlTex.clear();
	fin.close();

	//매쉬를 생성 및 정보 채우기, 최적화해보기
	LPD3DXMESH pMesh = NULL;
	//(비어있는)매쉬 생성하기
	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(), D3DXMESH_MANAGED, VERTEX_PNT::FVF, g_pDevice, &pMesh);

	VERTEX_PNT * pV = NULL;
	DWORD flags = 0;
	pMesh->LockVertexBuffer(flags, (LPVOID*)& pV);
	memcpy(pV, &vecPNT[0], vecPNT.size() * sizeof(VERTEX_PNT));
	pMesh->UnlockVertexBuffer();

	WORD * pI = NULL;
	pMesh->LockIndexBuffer(flags, (LPVOID*)& pI);
	for (size_t i = 0; i < vecPNT.size(); i++)
	{
		pI[i] = i;
	}
	pMesh->UnlockIndexBuffer();

	DWORD * pA = NULL;
	pMesh->LockAttributeBuffer(flags, &pA);
	memcpy(pA, &vecAttBuf[0], vecAttBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();
	//인접정보 생성하기
	vector<DWORD> vecAdjacency(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjacency[0]);
	//최적화 시키기
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &vecAdjacency[0], 0, 0, 0);

	return pMesh;
}

void ObjLoader::LoadMtlLib(string fullPath)
{
	char szToken[128];
	ifstream fin;//이 변수로 파일을 읽을거야
	string mtlName;
	//하나 로드할 때마다 ID를 추가함
	DWORD mtltexID = 0;

	fin.open(fullPath);

	if (fin.is_open() == false) return;
	//파일의 끝 까지
	while (fin.eof() == false)
	{
		//단어 단위로 읽어서 문자 비교
		fin >> szToken;

		if (CompareStr(szToken, "newmtl"))
		{
			fin >> mtlName;

			SAFE_RELEASE(m_mapMtlTex[mtlName]);
			m_mapMtlTex[mtlName] = new MTLTEX;
			m_mapMtlTex[mtlName]->id = mtltexID++;

		}
		else if (CompareStr(szToken, "Ka"))
		{
			D3DCOLORVALUE c;
			//ambient
			fin.getline(szToken,128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Ambient = c;
		}
		else if (CompareStr(szToken, "Kd"))
		{
			D3DCOLORVALUE c;
			//ambient
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Diffuse = c;
		}
		else if (CompareStr(szToken, "Ks"))
		{
			D3DCOLORVALUE c;
			//ambient
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Specular = c;
		}
		else if (CompareStr(szToken, "map_Kd"))
		{

			string filename;
			fin >> filename;
			filename = m_filePath + "/" + filename;

			m_mapMtlTex[mtlName]->SetTexture(g_pTextureManager->GetTexture(filename));
		}
	}
	fin.close();
	//크기 : 6
	//printf("m_mapMtlTex size : %d\n", m_mapMtlTex.size());
}
//단순 문자열 비교하기
bool ObjLoader::CompareStr(char * str1, const char * str2)
{
	return strcmp(str1, str2) == 0;
}
