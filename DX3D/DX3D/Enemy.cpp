#include "stdafx.h"
#include "Enemy.h"
#include "AStar.h"
#include "AStarNode.h"
#include "BoundingBox.h"

//obj파일 불러오기
#include "DrawingGroup.h"
#include "ObjLoader.h"
#include "SkinnedMesh.h"
#include "Ironman.h"
#include "Ray.h"


Enemy::Enemy(D3DXVECTOR3& pos, CString path, CString fileName, int enemyNum)
{
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Render()
{
}

void Enemy::UpdatePosition()
{
}

void Enemy::AnimationModify()
{
}

void Enemy::WorldToVP()
{
}

void Enemy::UpdateFrameMatrix()
{
}

bool Enemy::SphereCollideCheck()
{
	return false;
}

void Enemy::DrawRenderSphere()
{
}

void Enemy::DrawRenderMobHp()
{
}

void Enemy::MonsterCollideCheckRender()
{
}

void Enemy::RenderUseShader_0()
{
}

void Enemy::RenderUseShader_1()
{
}

void Enemy::MinusHP()
{
}

int Enemy::GetHP()
{
	return 0;
}

int Enemy::GetMonsterX()
{
	return 0;
}

int Enemy::GetMonsterY()
{
	return 0;
}

BoundingBox * Enemy::GetBoundingBox()
{
	return nullptr;
}

BoundingSphere * Enemy::GetSphere()
{
	return nullptr;
}

vector<BoundingSphere*> Enemy::GetSphereVector()
{
	return vector<BoundingSphere*>();
}

int Enemy::GetEnemyNum()
{
	return 0;
}

