#include "GameScene.h"
#include <cassert>
#include <time.h>

using namespace DirectX;

//球同士の当たり判定
bool GameScene::CollisionBalltoBall(XMFLOAT3 aPos, float aRadius, XMFLOAT3 bPos, float bRadius)
{
	float x = (aPos.x / 2 - bPos.x);
	float y = (aPos.y / 2 - bPos.y);
	float z = (aPos.z / 2 - bPos.z);
	float r = (aRadius + bRadius);
	return ((x * x) + (y * y) + (z * z)) <= (r * r);
}


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

	GameCounter = 0;

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
	bullet = new PlayerBullet();
	bullet->Initialize(dxCommon);

	//エネミー
	enemys.push_back(new Enemy());
	enemys.push_back(new Enemy());
	enemys.push_back(new Enemy());
	enemys.push_back(new Enemy());
	enemys.push_back(new Enemy());
	enemys.push_back(new Enemy());
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->Init(dxCommon);
	}

	//スポーンポイント
	spown = SpownPointModel::Create();
	spown->Update();

	//音楽
	soundData[0] = audio->SoundLoadWave("Resources/Shot.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Destroy.wav");
	soundData[2] = audio->SoundLoadWave("Resources/musicloop.wav");
	//再生
	audio->SoundPlayWave(audio->xAudio2.Get(), soundData[2], Audio::loop);
}

void GameScene::Update()
{
	GameCounter++;

	//120fごとに敵を追加
	if (GameCounter % 120 == 0) {
		enemys.push_back(new Enemy());
		enemys[enemys.size() - 1]->Init(dxCommon);
	}

	//Spaceで弾発射
	if (input->PressKeyTrigger(DIK_SPACE) && !bullet->GetIsAlive())
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0]);
		bullet->ShotInit(player->GetActiveNumber(),player->GetActivePos());
		player->ChangeActivePlayer();
	}
	//敵更新
	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->Update();
	}
	//敵の消去処理
	for (int i = enemys.size() - 1; i >= 0; i--) {
		if (!enemys[i]->enemyAlive) {
			delete enemys[i];
			enemys.erase(enemys.begin() + i);
		}
	}


#pragma region 弾とエネミーの当たり判定

	for (int i = 0; i < enemys.size(); i++) {
		if (CollisionBalltoBall(
			bullet->GetPosition(), bullet->GetRadius(),
			enemys[i]->GetPosition(), enemys[i]->GetRadius())) {
			enemys[i]->enemyAlive = false;
			score = score + 100;
			audio->SoundPlayWave(audio->xAudio2.Get(), soundData[1]);
		}
	}



#pragma endregion

#pragma region エネミー発生
	/*if (spownTimer > 0) {
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

	}*/
#pragma endregion

	
	//壁
	{
		wallUp->Update();
		wallDown->Update();
		wallRight->Update();
		wallLeft->Update();
	}
	//弾
	bullet->Update();
	//プレイヤー
	player->Update();
	//スポーンポイント
	spown->Update();

	//スコア表示
	//debugText.PrintDebugText("%s", score, 0.0f, -20.0f);
	
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
	bullet->Draw();
	////エネミー
	//for (int i = 0; i < enemyMaxNum; i++) {
	//	if (enemyAlive[i])
	//	{
	//		enemy[i]->Draw();
	//	}
	//}

#pragma endregion


	for (int i = 0; i < enemys.size(); i++) {
		enemys[i]->Draw();
	}

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Object2D::PreDraw(cmdList);
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	// スプライト描画後処理
	Object2D::PostDraw();
#pragma endregion
}
