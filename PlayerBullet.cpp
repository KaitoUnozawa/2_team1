#include "PlayerBullet.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
	safe_delete(bulletObj);

}

void PlayerBullet::Initialize(DirectXCommon* dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;

	bulletObj = BulletModel::Create();
	bulletObj->Update();
	moveVector = { 0,0,0 };
	isAlive = false;
}

void PlayerBullet::Update()
{
	if (isAlive == true)
	{
		position.x = position.x + moveVector.x;
		position.y = position.y + moveVector.y;
		position.z = position.z + moveVector.z;
		bulletObj->SetPosition(position);
	}
	bulletObj->Update();
}

void PlayerBullet::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	BulletModel::PreDraw(cmdList);
	bulletObj->Draw();
	BulletModel::PostDraw();

}
