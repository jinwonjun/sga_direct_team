#pragma once
#include "IDisplayObject.h"

//�����̴��� �����

class Enemyman :
	public IDisplayObject
{
private:
	//���� ���ؽ� ����
	//vector<VERTEX_PC> m_vecPCVertex;

	vector <VERTEX_PT> m_vecPTVertex;

	//�ȴٸ��ϱ� X�ุ �����ϸ� �ǰ���?
	bool m_isMoving;
	float m_rotXAngle;
	float m_rotXSpeed;

	LPDIRECT3DTEXTURE9 tex;//�ؽ��� �ѹ� ��������

public:
	Enemyman(float rotXSpeed = 0.0f);
	~Enemyman();

	// IDisplayObject��(��) ���� ��ӵ�
	//������ �ϰ� �Ⱦ�����. �ٵ� �� �����Լ� �߳ĸ� ������ ���س����� �Ʒ� ������ ����� ���� ���!
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	D3DXVECTOR3 m_CharPos;//���� ĳ������ ��ġ�� �޾ƿ���

	void Init(D3DXMATRIXA16* pMat, vector<vector<int>> &vecUV);
	void SetPTVertex(vector<VERTEX_PT> &vecOut, vector<D3DXVECTOR3> &vecVertex, vector<vector<int>> &uv);
	void SetMovingState(bool isMoving);
	void MakeUVList(vector<D3DXVECTOR2> &out, vector<vector<int>> &uv);
};

