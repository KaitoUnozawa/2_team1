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
}

void PlayerBullet::Update()
{
	bulletObj->SetPosition(position);
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
