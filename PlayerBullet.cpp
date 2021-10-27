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
	// nullptr�`�F�b�N
	assert(dxCommon);
	this->dxCommon = dxCommon;

	bulletObj = BulletModel::Create();
	bulletObj->Update();
}

void PlayerBullet::Update()
{
	//�ʒu���擾
	position = bulletObj->GetPosition();
	position = { 1.0f,1.0f,1.0f };
	bulletObj->SetPosition(position);

}

void PlayerBullet::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
	BulletModel::PreDraw(cmdList);
	bulletObj->Draw();
	BulletModel::PostDraw();

}
