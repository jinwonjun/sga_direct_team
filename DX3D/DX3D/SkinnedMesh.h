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

	float						m_radius;//��Ʈ ��ü �׷��� ���콺��

	D3DXMATRIXA16				m_matWorld;
	D3DXMATRIXA16				m_RightHandFrame;//�÷��̾� ������ ��İ�������

	vector <D3DXMATRIXA16>		m_Boss_FrameMatrix;//���� ��� ���(32��)
	vector <D3DXMATRIXA16>		m_Sub_FrameMatrix;//�̸� ��� ���(33��)
	vector <D3DXMATRIXA16>		m_Player_FrameMatrix;//�÷��̾� ��� ��� ���

	string*						BossFrameName;//���� ������ �̸��� ����뵵
	string*						SubMobFrameName;//�̸� ������ �̸��� ����뵵
	string*						PlayerFrameName;//�÷��̾� ������ �̸��� ����뵵


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
	//m_matWorld���� �� �Լ��� ���ؼ� �ٲ�����.
	void SetWorldMatrix(D3DXMATRIXA16* matW) { m_matWorld = *matW; }

	D3DXMATRIXA16& GetHandMatrix() { return m_RightHandFrame; }

	void RenderUseShader_0();
	void RenderUseShader_1();
	void SetRenderMode(IDisplayObject::RenderMode renderMode) { m_renderMode = renderMode; }
	//��ü �׸��� & �׸��⸸ ����
	void DrawSphereMatrix(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	LPD3DXFRAME GetRootFrame() { return m_pRootFrame; }
	void SetRadius(float radius) { m_radius = radius; }
	float GetRadius() { return m_radius; }
	
	//�̸� ã�� ��� �Լ�ȭ
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