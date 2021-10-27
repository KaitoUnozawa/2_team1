#include "Bullet.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
	safe_delete(Bulletobj);

}

void Bullet::Initialize(DirectXCommon* dxCommon)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	this->dxCommon = dxCommon;

	Bulletobj = BulletObject::Create();
	XMFLOAT3 Bscale = Bulletobj->GetScale();
	Bscale = { 1.0f,1.0f,1.0f };
	Bulletobj->SetScale(Bscale);
	Bulletobj->Update();

	

}

void Bullet::Update()
{
	position = Bulletobj->GetPosition();

	position= { 1.0f,1.0f,1.0f };
	

	Bulletobj->SetPosition(position);
	
}

void Bullet::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();

	BulletObject::PreDraw(cmdList);


	Bulletobj->Draw();


	BulletObject::PostDraw();

}
