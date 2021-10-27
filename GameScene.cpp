#include "GameScene.h"
#include <cassert>
#include <time.h>

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
	safe_delete(spown);

	safe_delete(player);
	safe_delete(*enemy);
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
	//プレイヤー
	player = new Player();
	player->Initialize(dxCommon, input, audio);

	//エネミー
	for (int i = 0; i < enemyMaxNum; i++)
	{
		enemy[i] = new Enemy();
		enemy[i]->Init(dxCommon, input, audio);
	}
	for (int i = 0; i < enemyMaxNum; i++)
	{
		XMFLOAT3 enemyPosition[enemyMaxNum] = { { 0, 0, 0} };
		enemyPosition[i] = enemy[i]->GetPosition();
		enemy[i]->SetPosition(enemyPosition[i]);

		enemy[i]->Update();
	}
	srand(time(NULL));

	//スポーンポイント
	spown = SpownPointModel::Create();
	spown->Update();

	//音楽
	soundData[0] = audio->SoundLoadWave("Resources/Shot.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Destroy.wav");
	soundData[2] = audio->SoundLoadWave("Resources/musicloop.wav");
	//再生
	//audio->SoundPlayWave(audio->xAudio2.Get(), soundData[2]);
}

void GameScene::Update()
{
#pragma region 弾とエネミーの当たり判定


#pragma endregion

#pragma region エネミー発生
	if (spownTimer > 0) {
		spownTimer--;
	}
	if (spownTimer <= 0) {
		if (enemyCount < enemyMaxNum) {
			enemyCount;
		}
		spownTimer = 100;
	}
	enemyAlive[enemyCount] = true;
	enemy[enemyCount]->Update();
	for (int i = 0; i < enemyMaxNum; i++) {
		enemy[i]->Update();

	}
#pragma endregion

	//Spaceで弾発射
	if (input->PressKeyTrigger(DIK_SPACE))
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0]);
		player->Update();
	}

	//壁
	{
		wallUp->Update();
		wallDown->Update();
		wallRight->Update();
		wallLeft->Update();
	}
	//プレイヤー
	player->Update();
	//スポーンポイント
	spown->Update();
	//キーボード入力更新
	input->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	//Object3D::PreDraw(cmdList);
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
	//スポーンポイント
	SpownPointModel::PreDraw(cmdList);
	spown->Draw();
	SpownPointModel::PostDraw();

	//プレイヤー
	player->Draw();
	//エネミー
	for (int i = 0; i < enemyMaxNum; i++) {
		if (enemyAlive[i])
		{
			enemy[i]->Draw();
		}
	}


	//ModelObj::PreDraw(cmdList);
	//ModelObj::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Object2D::PreDraw(cmdList);
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Object2D::PostDraw();
#pragma endregion
}
