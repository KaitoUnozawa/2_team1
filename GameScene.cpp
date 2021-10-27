#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(wallUp);
	safe_delete(wallDown);
	safe_delete(wallRight);
	safe_delete(wallLeft);
}

void GameScene::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// デバッグテキスト用テクスチャ読み込み
	if (!Object2D::LoadTexture(debugTextTexNum, L"Resources/DebugText.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Init(debugTextTexNum);

	// 背景テクスチャ読み込み
	if (!Object2D::LoadTexture(1, L"Resources/titleFont/blue.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	//spriteBG = Object2D::CreateSprite(1, { 0.0f,0.0f });

	// 3Dオブジェクト生成
	//object3d = Object3D::CreateObject();
	//object3d->Update();

	//3Dモデル
#pragma region 壁
	wallUp = GamesceneWallUp::Create();
	wallUp->SetPosition({ 0.0f,25.0f,0.0f });
	wallUp->SetRotation({ 0.0f,0.0f,90.0f });
	wallUp->SetScale({ 2.5f,14.0f,1.0f });
	wallUp->Update();

	wallDown = GamesceneWallUp::Create();
	wallDown->SetPosition({ 0.0f,-25.0f,0.0f });
	wallDown->SetRotation({ 0.0f,0.0f,90.0f });
	wallDown->SetScale({ 2.5f,14.0f,1.0f });
	wallDown->Update();

	wallRight = GamesceneWallLR::Create();
	wallRight->SetPosition({37.0f,0.0f,0.0f });
	wallRight->SetRotation({ 0.0f,0.0f,0.0f });
	wallRight->SetScale({ 15.0f,3.5f,1.0f });
	wallRight->Update();

	wallLeft = GamesceneWallLR::Create();
	wallLeft->SetPosition({ -37.0f,0.0f,0.0f });
	wallLeft->SetRotation({ 0.0f,0.0f,0.0f });
	wallLeft->SetScale({ 15.0f,3.5f,1.0f });
	wallLeft->Update();
#pragma endregion



	soundData[0] = audio->SoundLoadWave("Resources/Shot.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Destroy.wav");
}

void GameScene::Update()
{
	//// オブジェクト移動
	//if (input->PressKey(DIK_UP) || input->PressKey(DIK_DOWN) || input->PressKey(DIK_RIGHT) || input->PressKey(DIK_LEFT))
	//{
	//	// 現在の座標を取得
	//	XMFLOAT3 position = model->GetPosition();

	//	// 移動後の座標を計算
	//	if (input->PressKey(DIK_UP)) { position.y += 1.0f; }
	//	else if (input->PressKey(DIK_DOWN)) { position.y -= 1.0f; }
	//	if (input->PressKey(DIK_RIGHT)) { position.x += 1.0f; }
	//	else if (input->PressKey(DIK_LEFT)) { position.x -= 1.0f; }

	//	// 座標の変更を反映
	//	model->SetPosition(position);
	//}

	//// カメラ移動
	//if (input->PressKey(DIK_W) || input->PressKey(DIK_S) || input->PressKey(DIK_D) || input->PressKey(DIK_A))
	//{
	//	if (input->PressKey(DIK_W)) { Object3D::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
	//	else if (input->PressKey(DIK_S)) { Object3D::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
	//	if (input->PressKey(DIK_D)) { Object3D::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
	//	else if (input->PressKey(DIK_A)) { Object3D::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	//}

	//キーが押されているときの処理例
	if (input->PressKeyTrigger(DIK_0))
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[1]);
	}

	//音声再生例
	//SoundPlayWave(xAudio2.Get(),soundData1);
	if (input->PressKeyTrigger(DIK_M))
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0]);
	}

	//model->Update();
	//キーボード入力更新
	input->Update();

	//壁
	{
		wallUp->Update();
		wallDown->Update();
		wallRight->Update();
		wallLeft->Update();
	}
	
	
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	//Object2D::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	//Object2D::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	//Object3D::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	//object3d->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	//Object3D::PostDraw();
#pragma endregion

#pragma region 3Dモデル描画
	//壁
	{
		GamesceneWallUp::PreDraw(cmdList);
		wallUp->Draw();
		wallDown->Draw();
		GamesceneWallUp::PostDraw();

		GamesceneWallLR::PreDraw(cmdList);
		wallRight->Draw();
		wallLeft->Draw();
		GamesceneWallLR::PostDraw();
	}
	

	ModelObj::PreDraw(cmdList);
	ModelObj::PostDraw();

	
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Object2D::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	//AL3 1-2追加
	//sprite1->Draw();
	//sprite2->Draw();

	/// </summary>


	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Object2D::PostDraw();
#pragma endregion
}
