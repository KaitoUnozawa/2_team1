#include "Enemy.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	safe_delete(enemy);
}

void Enemy::Init(DirectXCommon* dxCommon)
{
	assert(dxCommon);
	this->dxCommon = dxCommon;
	enemy = EnemyModel::Create();
	enemy->SetPosition({ 0,0,0 });
	enemy->Update();
	srand(time(NULL));
	angle = rand() % 360 + 1;
	moveVector.x = (cosf(angle)) * enemyMoveSpeed;
	moveVector.y = (sinf(angle)) * enemyMoveSpeed;
	enemyAlive = true;
	position = { 0,0,0 };
}

void Enemy::Update()
{
#pragma region エネミー移動

	position = { 
		position.x + moveVector.x,
		position.y + moveVector.y,
		position.z + moveVector.z
	};
#pragma endregion
	if (position.x >= 50 || position.x <= -50 ||
		position.y >= 50 || position.y <= -50)
	{
		enemyAlive = false;
	}

	enemy->SetPosition(position);
	enemy->Update();
}

void Enemy::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	

	if (enemyAlive == true) {
		EnemyModel::PreDraw(cmdList);
		enemy->Draw();
		EnemyModel::PostDraw();
	}
}
