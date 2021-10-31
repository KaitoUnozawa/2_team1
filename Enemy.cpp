#include "Enemy.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	//safe_delete(bullet);
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
}

void Enemy::Update()
{

#pragma region エネミー移動

	position = enemy->GetPosition();
	enemyAlive = true;
	if (angle == 0) {
		angle = rand() % 360 + 1;
	}

	position.x += (cosf(angle)) * enemyMoveSpeed;
	position.y += (sinf(angle)) * enemyMoveSpeed;
	
	enemy->Update();
#pragma endregion

	//XMFLOAT3 BMposition = bullet->GetPosition();
	////上下当たり判定
	//if (enemyAlive== 1 bflag == 1 || bflag == 3) {
	//	float a = BM2position.x - Eposition.x;
	//	float b = BM2position.y - Eposition.y;
	//	float c = sqrt(a * a + b * b);
	//	if (c <= radius1 + radius2) {
	//		tflag = 1;
	//	}
	//}
	//左右当たり判定
	/*if (enemyAlive == 1) {
		float d = BMposition.x - position.x;
		float e = BMposition.y - position.y;
		float f = sqrt(d * d + e * e);
		if (f <= radius1 + radius2) {
			enemyAlive = 0;
		}
	}*/
	//bullet->SetPosition(BMposition);
	if (enemy->GetPosition().x >= 50 || enemy->GetPosition().x <= -50 ||
		enemy->GetPosition().y >= 50 || enemy->GetPosition().y <= -50)
	{
		enemyAlive = false;
	}

	enemy->SetPosition(position);
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
