#include "Player.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Player::Player()
{
}

Player::~Player()
{
	safe_delete(p2object);
	safe_delete(p2object2);
	safe_delete(p2object3);
	safe_delete(p2object4);

	safe_delete(pobject);
	safe_delete(pobject2);
	safe_delete(pobject3);
	safe_delete(pobject4);

}

void Player::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;
	pobject = PlayerObject::Create();
	XMFLOAT3 position21 = pobject->GetPosition();
	position21 = { 0.0f,-42.0f,0.0f };
	pobject->SetPosition(position21);
	XMFLOAT3 scale21 = pobject->GetScale();
	scale21 = { 2.0f,2.0f,2.0f };
	pobject->SetScale(scale21);
	pobject->Update();

	pobject2 = PlayerObject::Create();
	XMFLOAT3 position22 = pobject2->GetPosition();
	position22 = { 0.0f,42.0f,0.0f };
	pobject2->SetPosition(position22);
	XMFLOAT3 scale22 = pobject2->GetScale();
	scale22 = { 2.0f,2.0f,2.0f };
	pobject2->SetScale(scale22);
	pobject2->Update();

	pobject3 = PlayerObject::Create();
	XMFLOAT3 position23 = pobject3->GetPosition();
	position23 = { -42.0f,0.0f,0.0f };
	pobject3->SetPosition(position23);
	XMFLOAT3 scale23 = pobject3->GetScale();
	scale23 = { 2.0f,2.0f,2.0f };
	pobject3->SetScale(scale23);
	pobject3->Update();

	pobject4 = PlayerObject::Create();
	XMFLOAT3 position24 = pobject4->GetPosition();
	position24 = { 42.0f,0.0f,0.0f };
	pobject4->SetPosition(position24);
	XMFLOAT3 scale24 = pobject4->GetScale();
	scale24 = { 2.0f,2.0f,2.0f };
	pobject4->SetScale(scale24);
	pobject4->Update();

	p2object = PlayerObject2::Create();
	XMFLOAT3 p2position1 = p2object->GetPosition();
	p2position1 = { 0.0f,-42.0f,0.0f };
	p2object->SetPosition(p2position1);
	XMFLOAT3 p2scale1 = p2object->GetScale();
	p2scale1 = { 2.0f,2.0f,2.0f };
	p2object->SetScale(p2scale1);
	p2object->Update();

	p2object2 = PlayerObject2::Create();
	XMFLOAT3 p2position2 = pobject2->GetPosition();
	p2position2 = { 0.0f,42.0f,0.0f };
	p2object2->SetPosition(p2position2);
	XMFLOAT3 p2scale2 = pobject2->GetScale();
	p2scale2 = { 2.0f,2.0f,2.0f };
	p2object2->SetScale(p2scale2);
	p2object2->Update();

	p2object3 = PlayerObject2::Create();
	XMFLOAT3 p2position3 = pobject3->GetPosition();
	p2position3 = { -42.0f,0.0f,0.0f };
	p2object3->SetPosition(p2position3);
	XMFLOAT3 p2scale3 = pobject3->GetScale();
	p2scale3 = { 2.0f,2.0f,2.0f };
	p2object3->SetScale(p2scale3);
	p2object3->Update();

	p2object4 = PlayerObject2::Create();
	XMFLOAT3 p2position4 = pobject4->GetPosition();
	p2position4 = { 42.0f,0.0f,0.0f };
	p2object4->SetPosition(p2position4);
	XMFLOAT3 p2scale4 = pobject4->GetScale();
	p2scale4 = { 2.0f,2.0f,2.0f };
	p2object4->SetScale(p2scale4);
	p2object4->Update();


	bullet= new Bullet();
	bullet->Initialize(dxCommon);

	bullet2 = new Bullet2();
	bullet2->Initialize(dxCommon);
}

void Player::Update()
{
	XMFLOAT3 Mposition1 = pobject->GetPosition();
	XMFLOAT3 Mposition2 = pobject2->GetPosition();
	XMFLOAT3 Mposition3 = pobject3->GetPosition();
	XMFLOAT3 Mposition4 = pobject4->GetPosition();

	XMFLOAT3 M2position1 = p2object->GetPosition();
	XMFLOAT3 M2position2 = p2object2->GetPosition();
	XMFLOAT3 M2position3 = p2object3->GetPosition();
	XMFLOAT3 M2position4 = p2object4->GetPosition();
	XMFLOAT3 position = bullet->GetPosition();
	XMFLOAT3 position2 = bullet2->GetPosition();

#pragma region	プレイヤー操作と弾
	if (mflag == 0) {
		if (input->TriggerKey(DIK_SPACE)) {
			playerSpeed1 = -playerSpeed1;
			playerSpeed2 = -playerSpeed2;
			playerSpeed3 = -playerSpeed3;
			playerSpeed4 = -playerSpeed4;

			bflag++;
			if (bflag == 5) {
				bflag = 1;
			}
			if (bflag == 1) {
				mflag = 1;
				playerActive2 = 1;
				playerActive1 = 0;
				position2.x = Mposition1.x;
				position2.y = Mposition1.y;
				position2.z = Mposition1.z;
			}
			if (bflag == 3) {
				mflag = 1;
				playerActive4 = 1;
				playerActive3 = 0;
				position2.x = Mposition2.x;
				position2.y = Mposition2.y;
				position2.z = Mposition2.z;
			}
			if (bflag == 4) {
				mflag = 1;
				playerActive1 = 1;
				playerActive4 = 0;
				position.x = Mposition3.x;
				position.y = Mposition3.y;
				position.z = Mposition3.z;
			}
			if (bflag == 2) {
				mflag = 1;
				playerActive3 = 1;
				playerActive2 = 0;
				position.x = Mposition4.x;
				position.y = Mposition4.y;
				position.z = Mposition4.z;
			}
		}
	}
	if (mflag == 1)
	{
		if (bflag == 1) {
			position2.y += 2;
			if (position2.y >= 100) {
				mflag = 0;
			}
		}
		if (bflag == 3) {
			position2.y -= 2;
			if (position2.y <= -100) {
				mflag = 0;
			}
		}
		if (bflag == 4) {
			position.x += 2;
			if (position.x >= 110) {
				mflag = 0;
			}
		}
		if (bflag == 2) {
			position.x -= 2;
			if (position.x <= -110) {
				mflag = 0;
			}
		}
	}
#pragma endregion

#pragma region	プレイヤー移動
	// プレイヤーオブジェクト移動
	Mposition1.x += playerSpeed1;
	Mposition2.x += playerSpeed2;
	Mposition3.y += playerSpeed3;
	Mposition4.y += playerSpeed4;

	M2position1.x += playerSpeed1;
	M2position2.x += playerSpeed2;
	M2position3.y += playerSpeed3;
	M2position4.y += playerSpeed4;

	if (Mposition1.x >= -43 && Mposition1.x <= -43) { playerSpeed1 = 0.5f; }
	if (Mposition2.x >= 43 && Mposition2.x <= 43) { playerSpeed2 = -0.5f; }
	if (Mposition3.y >= 43 && Mposition3.y <= 43) { playerSpeed3 = -0.5f; }
	if (Mposition4.y >= -43 && Mposition4.y <= -43) { playerSpeed4 = 0.5f; }

	if (M2position1.x >= -43 && M2position1.x <= -43) { playerSpeed1 = 0.5f; }
	if (M2position2.x >= 43 && M2position2.x <= 43) { playerSpeed2 = -0.5f; }
	if (M2position3.y >= 43 && M2position3.y <= 43) { playerSpeed3 = -0.5f; }
	if (M2position4.y >= -43 && M2position4.y <= -43) { playerSpeed4 = 0.5f; }


	if (Mposition1.x >= 43 && Mposition1.x <= 43) { playerSpeed1 = -0.5f; }
	if (Mposition2.x >= -43 && Mposition2.x <= -43) { playerSpeed2 = 0.5f; }
	if (Mposition3.y >= -43 && Mposition3.y <= -43) { playerSpeed3 = 0.5f; }
	if (Mposition4.y >= 43 && Mposition4.y <= 43) { playerSpeed4 = -0.5f; }

	if (M2position1.x >= 43 && M2position1.x <= 43) { playerSpeed1 = -0.5f; }
	if (M2position2.x >= -43 && M2position2.x <= -43) { playerSpeed2 = 0.5f; }
	if (M2position3.y >= -43 && M2position3.y <= -43) { playerSpeed3 = 0.5f; }
	if (M2position4.y >= 43 && M2position4.y <= 43) { playerSpeed4 = -0.5f; }
	
#pragma region	エネミー以外のSetter

	pobject->SetPosition(Mposition1);
	pobject2->SetPosition(Mposition2);
	pobject3->SetPosition(Mposition3);
	pobject4->SetPosition(Mposition4);

	p2object->SetPosition(M2position1);
	p2object2->SetPosition(M2position2);
	p2object3->SetPosition(M2position3);
	p2object4->SetPosition(M2position4);
	bullet->SetPosition(position);
	bullet2->SetPosition(position2);
#pragma endregion


	pobject->Update();
	pobject2->Update();
	pobject3->Update();
	pobject4->Update();

	p2object->Update();
	p2object2->Update();
	p2object3->Update();
	p2object4->Update();


	bullet->Update();
	bullet2->Update();
#pragma endregion


}

void Player::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	PlayerObject::PreDraw(cmdList);
	PlayerObject2::PreDraw(cmdList);
	bullet->Draw();
	bullet2->Draw();
	if (playerActive1 == 0) {
		pobject->Draw();
	}
	if (playerActive2 == 0) {
		pobject4->Draw();
	}
	if (playerActive3 == 0) {
		pobject2->Draw();
	}
	if (playerActive4 == 0) {
		pobject3->Draw();
	}
	if (playerActive1 == 1) {
		p2object->Draw();
	}
	if (playerActive2 == 1) {
		p2object4->Draw();
	}
	if (playerActive3 == 1) {
		p2object2->Draw();
	}
	if (playerActive4 == 1) {
		p2object3->Draw();
	}


	PlayerObject::PostDraw();
	PlayerObject2::PostDraw();

}
