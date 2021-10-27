#include "Enemy.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	safe_delete(bullet);
	safe_delete(enemy);


}

void Enemy::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	assert(dxCommon);
	this->dxCommon = dxCommon;
	enemy = EnemyModel::Create();
	XMFLOAT3 Eposition = enemy->GetPosition();
	Eposition = { 0.0f,0.0f,0.0f };
	enemy->SetPosition(Eposition);
	enemy->Update();
	bullet = new PlayerBullet();
	bullet->Initialize(dxCommon);
	srand(time(NULL));
}

void Enemy::Update()
{

#pragma region エネミー移動
	position = enemy->GetPosition();

	enemyAlive = 1;
	if (angle == 0) {
		angle = rand() % 360 + 1;
	}

	position.x += (cosf(angle) + enemySpeed1) / 2;
	position.y += (sinf(angle) + enemySpeed2) / 2;

	enemy->SetPosition(position);
	enemy->Update();
#pragma endregion

	XMFLOAT3 BMposition = bullet->GetPosition();

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

	if (enemyAlive == 1) {
		float d = BMposition.x - position.x;
		float e = BMposition.y - position.y;
		float f = sqrt(d * d + e * e);
		if (f <= radius1 + radius2) {
			enemyAlive = 0;
		}
	}
	bullet->SetPosition(BMposition);

}

void Enemy::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	EnemyModel::PreDraw(cmdList);

	if (enemyAlive == 1) {
		enemy->Draw();
	}

	EnemyModel::PostDraw();
}
