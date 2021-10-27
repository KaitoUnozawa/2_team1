#include "Bullet2.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Bullet2::Bullet2()
{
}

Bullet2::~Bullet2()
{
	
	safe_delete(Bulletobj2);
}

void Bullet2::Initialize(DirectXCommon* dxCommon)
{
	// nullptrチェック
	assert(dxCommon);
	this->dxCommon = dxCommon;



	Bulletobj2 = BulletObject2::Create();
	XMFLOAT3 Bscale2 = Bulletobj2->GetScale();
	Bscale2 = { 1.0f,1.0f,1.0f };
	Bulletobj2->SetScale(Bscale2);
	Bulletobj2->Update();
}

void Bullet2::Update()
{

	position = Bulletobj2->GetPosition();
	position= { 1.0f,1.0f,1.0f };
	

	Bulletobj2->SetPosition(position);

}

void Bullet2::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();


	BulletObject2::PreDraw(cmdList);


	Bulletobj2->Draw();


	BulletObject2::PostDraw();
}
