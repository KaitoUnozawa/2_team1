#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(sprite1);
	safe_delete(sprite2);

	safe_delete(object3d);
	safe_delete(object3d2);
	safe_delete(object3d3);
	safe_delete(object3d4);
	
	safe_delete(p2object);
	safe_delete(p2object2);
	safe_delete(p2object3);
	safe_delete(p2object4);

	safe_delete(pobject);
	safe_delete(pobject2);
	safe_delete(pobject3);
	safe_delete(pobject4);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio * audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return ;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	Sprite::LoadTexture(2, L"Resources/texture.png");
	sprite1 = Sprite::Create(2, { 0,0 });
	sprite2 = Sprite::Create(2, { 500,500 }, { 1,0,0,1 }, { 0,0 }, false, true);
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// 3Dオブジェクト生成
	object3d = Object3d::Create();
	object3d->Update();
	object3d2 = Object3d::Create();
	object3d2->Update();
	object3d3 = Object3d::Create();
	object3d3->Update();
	object3d4 = Object3d::Create();
	object3d4->Update();

	pobject = PlayerObject::Create();
	pobject->Update();
	pobject2 = PlayerObject::Create();
	pobject2->Update();
	pobject3 = PlayerObject::Create();
	pobject3->Update();
	pobject4 = PlayerObject::Create();
	pobject4->Update();

	p2object = PlayerObject2::Create();
	p2object->Update();
	p2object2 = PlayerObject2::Create();
	p2object2->Update();
	p2object3 = PlayerObject2::Create();
	p2object3->Update();
	p2object4 = PlayerObject2::Create();
	p2object4->Update();

	bullet = Bullet::Create();
	bullet->Update();

	enemy = Enemy::Create();
	enemy->Update();

	//プレイヤーのポジションとスケール
	XMFLOAT3 position21 = pobject->GetPosition();
	XMFLOAT3 position22 = pobject2->GetPosition();
	XMFLOAT3 position23 = pobject3->GetPosition();
	XMFLOAT3 position24 = pobject4->GetPosition();
	position21 = { 0.0f,-42.0f,0.0f };
	position22 = { 0.0f,42.0f,0.0f };
	position23 = { -42.0f,0.0f,0.0f };
	position24 = { 42.0f,0.0f,0.0f };
	pobject->SetPosition(position21);
	pobject2->SetPosition(position22);
	pobject3->SetPosition(position23);
	pobject4->SetPosition(position24);

	XMFLOAT3 scale21 = pobject->GetScale();
	XMFLOAT3 scale22 = pobject2->GetScale();
	XMFLOAT3 scale23 = pobject3->GetScale();
	XMFLOAT3 scale24 = pobject4->GetScale();
	scale21 = { 2.0f,2.0f,2.0f };
	scale22 = { 2.0f,2.0f,2.0f };
	scale23 = { 2.0f,2.0f,2.0f };
	scale24 = { 2.0f,2.0f,2.0f };
	pobject->SetScale(scale21);
	pobject2->SetScale(scale22);
	pobject3->SetScale(scale23);
	pobject4->SetScale(scale24);

	//プレイヤーのポジションとスケール
	XMFLOAT3 p2position1 = p2object->GetPosition();
	XMFLOAT3 p2position2 = pobject2->GetPosition();
	XMFLOAT3 p2position3 = pobject3->GetPosition();
	XMFLOAT3 p2position4 = pobject4->GetPosition();
	p2position1 = { 0.0f,-42.0f,0.0f };
	p2position2 = { 0.0f,42.0f,0.0f };
	p2position3 = { -42.0f,0.0f,0.0f };
	p2position4 = { 42.0f,0.0f,0.0f };
	p2object->SetPosition(p2position1);
	p2object2->SetPosition(p2position2);
	p2object3->SetPosition(p2position3);
	p2object4->SetPosition(p2position4);

	XMFLOAT3 p2scale1 = p2object->GetScale();
	XMFLOAT3 p2scale2 = pobject2->GetScale();
	XMFLOAT3 p2scale3 = pobject3->GetScale();
	XMFLOAT3 p2scale4 = pobject4->GetScale();
	p2scale1 = { 2.0f,2.0f,2.0f };
	p2scale2 = { 2.0f,2.0f,2.0f };
	p2scale3 = { 2.0f,2.0f,2.0f };
	p2scale4 = { 2.0f,2.0f,2.0f };
	p2object->SetScale(p2scale1);
	p2object2->SetScale(p2scale2);
	p2object3->SetScale(p2scale3);
	p2object4->SetScale(p2scale4);

	XMFLOAT3 Bscale1 = bullet->GetScale();

	Bscale1 = { 1.0f,1.0f,1.0f };

	bullet->SetScale(Bscale1);

}

void GameScene::Update()
{
	//壁のポジションとスケール
	XMFLOAT3 position1 = object3d->GetPosition();
	XMFLOAT3 position2 = object3d2->GetPosition();
	XMFLOAT3 position3 = object3d3->GetPosition();
	XMFLOAT3 position4 = object3d4->GetPosition();
	position1 = { 0.0f,-53.0f,0.0f };
	position2 = { 0.0f,53.0f,0.0f };
	position3 = { -73.0f,0.0f,0.0f };
	position4 = { 73.0f,0.0f,0.0f };
	object3d->SetPosition(position1);
	object3d2->SetPosition(position2);
	object3d3->SetPosition(position3);
	object3d4->SetPosition(position4);

	XMFLOAT3 rotation1 = object3d->GetRotation();
	XMFLOAT3 rotation2 = object3d2->GetRotation();
	XMFLOAT3 rotation3 = object3d3->GetRotation();
	XMFLOAT3 rotation4 = object3d4->GetRotation();
	rotation1 = { 0.0f,0.0f,90.0f };
	rotation2 = { 0.0f,0.0f,90.0f };
	rotation3 = { 0.0f,0.0f,0.0f };
	rotation4 = { 0.0f,0.0f,0.0f };
	object3d->SetRotation(rotation1);
	object3d2->SetRotation(rotation2);
	object3d3->SetRotation(rotation3);
	object3d4->SetRotation(rotation4);

	XMFLOAT3 scale1 = object3d->GetScale();
	XMFLOAT3 scale2 = object3d2->GetScale();
	XMFLOAT3 scale3 = object3d3->GetScale();
	XMFLOAT3 scale4 = object3d4->GetScale();
	scale1 = { 10.0f,14.0f,1.0f };
	scale2 = { 10.0f,14.0f,1.0f };
	scale3 = { 30.0f,6.0f,1.0f };
	scale4 = { 30.0f,6.0f,1.0f };
	object3d->SetScale(scale1);
	object3d2->SetScale(scale2);
	object3d3->SetScale(scale3);
	object3d4->SetScale(scale4); 
	


	//// オブジェクト移動
	//if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	//{
	//	// 現在の座標を取得
	//	XMFLOAT3 position = object3d->GetPosition();

	//	// 移動後の座標を計算
	//	if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
	//	else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
	//	if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
	//	else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

	//	// 座標の変更を反映
	//	object3d->SetPosition(position);
	//}
	// オブジェクト移動
	XMFLOAT3 Mposition1 = pobject->GetPosition();
	XMFLOAT3 Mposition2 = pobject2->GetPosition();
	XMFLOAT3 Mposition3 = pobject3->GetPosition();
	XMFLOAT3 Mposition4 = pobject4->GetPosition();

	XMFLOAT3 M2position1 = p2object->GetPosition();
	XMFLOAT3 M2position2 = p2object2->GetPosition();
	XMFLOAT3 M2position3 = p2object3->GetPosition();
	XMFLOAT3 M2position4 = p2object4->GetPosition();

	XMFLOAT3 BMposition = bullet->GetPosition();
	XMFLOAT3 Eposition = enemy->GetPosition();
	if (mflag == 0) {
		if (input->TriggerKey(DIK_SPACE)) {
		
			bflag++;
			if (bflag == 5) {
				bflag = 1;
			}
			if (bflag == 1) {
				mflag = 1;
				BMposition.x = Mposition1.x;
				BMposition.y = Mposition1.y;
				BMposition.z = Mposition1.z;

			}
			if (bflag == 3) {
				mflag = 1;
				BMposition.x = Mposition2.x;
				BMposition.y = Mposition2.y;
				BMposition.z = Mposition2.z;

			}
			if (bflag == 4) {	
				mflag = 1;
				BMposition.x = Mposition3.x;
				BMposition.y = Mposition3.y;
				BMposition.z = Mposition3.z;

			}
			if (bflag == 2) {
				mflag = 1;
				BMposition.x = Mposition4.x;
				BMposition.y = Mposition4.y;
				BMposition.z = Mposition4.z;

			}
		}
	}
	if (mflag == 1)
	{
		if (bflag == 1) {
			BMposition.y += 2;
			if (BMposition.y >= position2.y) {
				playerActive2 = 1;
				playerActive1 = 0;
				mflag = 0;
			}
		}
		if (bflag == 3) {
			BMposition.y -= 2;
			if (BMposition.y <= position1.y) {
				playerActive4 = 1;
				playerActive3 = 0;
				mflag = 0;
			}
		}
		if (bflag == 4) {
			BMposition.x += 2;
			if (BMposition.x >= position4.x) {
				playerActive1 = 1;
				playerActive4 = 0;
				mflag = 0;
			}
		}
		if (bflag == 2) {
			BMposition.x -= 2;
			if (BMposition.x <= position3.x) {
				playerActive3 = 1;
				playerActive2 = 0;
				mflag = 0;
			}
		}
	}

	Mposition1.x += playerSpeed1;
	Mposition2.x += playerSpeed2;
	Mposition3.y += playerSpeed3;
	Mposition4.y += playerSpeed4;
	
	M2position1.x += playerSpeed1;
	M2position2.x += playerSpeed2;
	M2position3.y += playerSpeed3;
	M2position4.y += playerSpeed4;

	Mposition1 = M2position1;
	Mposition2 = M2position2;
	Mposition3 = M2position3;
	Mposition4 = M2position4;

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

	pobject->SetPosition(Mposition1);
	pobject2->SetPosition(Mposition2);
	pobject3->SetPosition(Mposition3);
	pobject4->SetPosition(Mposition4);

	p2object->SetPosition(M2position1);
	p2object2->SetPosition(M2position2);
	p2object3->SetPosition(M2position3);
	p2object4->SetPosition(M2position4);

	//当たり判定
		bullet->SetPosition(BMposition);
		enemy->SetPosition(Eposition);
		if (enemyAlive == 1 && mflag == 1) {

			float a = BMposition.x - Eposition.x;
			float b = BMposition.y - Eposition.y;
			float c = sqrt(a * a + b * b);

			if (c <= radius1 + radius2) {
				if (bflag == 2 || bflag == 4) {
					enemyAlive = 0;
				}
				if (bflag == 1 || bflag == 3) {
				
				}
			}


		}
	object3d->Update();
	object3d2->Update();
	object3d3->Update();
	object3d4->Update();

	pobject->Update();
	pobject2->Update();
	pobject3->Update();
	pobject4->Update();

	p2object->Update();
	p2object2->Update();
	p2object3->Update();
	p2object4->Update();

	bullet->Update();
	
	enemy->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();
	//sprite1->Draw();
	//sprite2->Draw();
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	PlayerObject::PreDraw(cmdList);
	PlayerObject2::PreDraw(cmdList);
	Bullet::PreDraw(cmdList);
	Enemy::PreDraw(cmdList);
	// 3Dオブクジェクトの描画
	object3d->Draw();
	object3d2->Draw();
	object3d3->Draw();
	object3d4->Draw();

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
	if (mflag == 1) {
		bullet->Draw();
	}
	if (enemyAlive == 1) {
		enemy->Draw();
	}
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
	PlayerObject::PostDraw();
	PlayerObject2::PostDraw();
	Bullet::PostDraw();
	Enemy::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

