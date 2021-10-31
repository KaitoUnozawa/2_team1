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

	if (position.x >= 50 || position.x <= -50 || 
		position.y >= 50 || position.y <= -50) 
	{
		isAlive = false;
		position = { -500,-500,-500 };
	}

	bulletObj->Update();
}

void PlayerBullet::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	BulletModel::PreDraw(cmdList);
	if (isAlive) {
		bulletObj->Draw();

	}
	BulletModel::PostDraw();

}

void PlayerBullet::ShotInit(int posNumber,XMFLOAT3 startPos)
{
	position = startPos;
	
	switch (posNumber)
	{
		case 0:
			moveVector = { 0,2,0 };
			break;
		case 1:
			moveVector = { 2,0,0 };
			break;
		case 2:
			moveVector = { 0,-2,0 };
			break;
		case 3:
			moveVector = { -2,0,0 };
			break;
	}
	isAlive = true;
}
