#pragma once

class SkinnedMesh
{
protected:
	LPD3DXFRAME					m_pRootFrame;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	
	int							m_animIndex;
	float						m_fBlendTime;
	float						m_fPassedBlendTime;

	LPD3DXMESH					m_pSphereMesh;
	bool						m_bWireFrame;
	bool						m_bDrawFrame;
	bool						m_bDrawSkeleton;
	int							m_numFrame;
	int							m_numMesh;

	float						m_radius;//히트 구체 그려줄 라디우스값

	D3DXMATRIXA16				m_matWorld;
	D3DXMATRIXA16				m_RightHandFrame;//플레이어 오른손 행렬가져오기

	vector <D3DXMATRIXA16>		m_Boss_FrameMatrix;//보스 계산 행렬(32개)
	vector <D3DXMATRIXA16>		m_Sub_FrameMatrix;//쫄몹 계산 행렬(33개)
	vector <D3DXMATRIXA16>		m_Player_FrameMatrix;//플레이어 행렬 계산 행렬

	string*						BossFrameName;//보스 프레임 이름값 저장용도
	string*						SubMobFrameName;//쫄몹 프레임 이름값 저장용도
	string*						PlayerFrameName;//플레이어 프레임 이름값 저장용도


	IDisplayObject::RenderMode m_renderMode;
public:
	SkinnedMesh();
	virtual ~SkinnedMesh();

	void Init();
	void Update();
	void Render();

	void Load(LPCTSTR path, LPCTSTR filename);
private:
	void SetupBoneMatrixPointers(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPointersOnMesh(LPD3DXMESHCONTAINER pMeshContainerBase);

	void UpdateAnim();
	void UpdateFrameMatrices(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);

	void DrawFrame(LPD3DXFRAME pFrame);
	void DrawMeshContainer(LPD3DXFRAME pFrame);
	void DrawSkeleton(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
public:
	void SetAnimationIndex(int nIndex, bool isBlend);
	LPD3DXANIMATIONCONTROLLER GetAnimationController() {return m_pAnimController;}
	
	int status;
	//m_matWorld값을 이 함수를 통해서 바꿔주자.
	void SetWorldMatrix(D3DXMATRIXA16* matW) { m_matWorld = *matW; }

	D3DXMATRIXA16& GetHandMatrix() { return m_RightHandFrame; }

	void RenderUseShader_0();
	void RenderUseShader_1();
	void SetRenderMode(IDisplayObject::RenderMode renderMode) { m_renderMode = renderMode; }
	//구체 그리기 & 그리기만 했음
	void DrawSphereMatrix(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	LPD3DXFRAME GetRootFrame() { return m_pRootFrame; }
	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius() { return m_radius; }
	
	//이름 찾는 행렬 함수화
	void SetFrameNameInit();
	void MonsterCalFrameMat(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	vector<D3DXMATRIXA16> GetBossMatrix() { return m_Boss_FrameMatrix; }
	vector<D3DXMATRIXA16> GetSubMobMatrix() { return m_Sub_FrameMatrix; }
	vector<D3DXMATRIXA16> GetPlayerMatrix() { return m_Player_FrameMatrix; }
};

// OnInit
// pMeshContainerEx->ppBoneMatrixPtrs[i] = &pFrameExInfluence->CombinedTM;

// OnUpdate
// pFrameEx->CombinedTM = pFrameEx->TransformationMatrix * ((FRAME_EX*)pParent)->CombinedTM;
// pMeshContainerEx->pFinalBoneMatrices[i] =
// pMeshContainerEx->pBoneOffsetMatrices[i] * *(pMeshContainerEx->ppBoneMatrixPtrs[i]);