#include "GameScene.h"
#include <cassert>
#include <time.h>

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
	

	for (int i = 0; i < enemy_max; i++) {
		safe_delete(enemy[i]);
	}
	safe_delete(player);
	safe_delete(spawn);
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
	XMFLOAT3 position1 = object3d->GetPosition();
	position1 = { 0.0f,-53.0f,0.0f };
	object3d->SetPosition(position1);
	XMFLOAT3 rotation1 = object3d->GetRotation();
	rotation1 = { 0.0f,0.0f,90.0f };
	object3d->SetRotation(rotation1);
	XMFLOAT3 scale1 = object3d->GetScale();
	scale1 = { 10.0f,14.0f,1.0f };
	object3d->SetScale(scale1);
	object3d->Update();

	object3d2 = Object3d::Create();
	XMFLOAT3 position2 = object3d2->GetPosition();
	position2 = { 0.0f,53.0f,0.0f };
	object3d2->SetPosition(position2);
	XMFLOAT3 rotation2 = object3d2->GetRotation();
	rotation2 = { 0.0f,0.0f,90.0f };
	object3d2->SetRotation(rotation2);
	XMFLOAT3 scale2 = object3d2->GetScale();
	scale2 = { 10.0f,14.0f,1.0f };
	object3d2->SetScale(scale2);
	object3d2->Update();

	object3d3 = Object3d2::Create();
	XMFLOAT3 position3 = object3d3->GetPosition();
	position3 = { -73.0f,0.0f,0.0f };
	object3d3->SetPosition(position3);
	XMFLOAT3 rotation3 = object3d3->GetRotation();
	rotation3 = { 0.0f,0.0f,0.0f };
	object3d3->SetRotation(rotation3);
	XMFLOAT3 scale3 = object3d3->GetScale();
	scale3 = { 30.0f,6.0f,1.0f };
	object3d3->SetScale(scale3);
	object3d3->Update();

	object3d4 = Object3d2::Create();
	XMFLOAT3 position4 = object3d4->GetPosition();
	position4 = { 73.0f,0.0f,0.0f };
	object3d4->SetPosition(position4);
	XMFLOAT3 rotation4 = object3d4->GetRotation();
	rotation4 = { 0.0f,0.0f,0.0f };
	object3d4->SetRotation(rotation4);
	XMFLOAT3 scale4 = object3d4->GetScale();
	scale4 = { 30.0f,6.0f,1.0f };
	object3d4->SetScale(scale4);
	object3d4->Update();

	player = new Player();
	player->Initialize(dxCommon, input, audio);

	for (int i = 0; i < enemy_max; i++) {
		enemy[i] = new Enemy();
		enemy[i]->Initialize(dxCommon,input, audio);
	
	}
	for (int i = 0; i < enemy_max; i++) {
		XMFLOAT3 Eposition[enemy_max];
		Eposition[i] = { 0.0f,0.0f,0.0f };
		Eposition[i] = enemy[i]->GetPosition();
		enemy[i]->SetPosition(Eposition[i]);

		enemy[i]->Update();
	}
	spawn = Spawn::Create();
	spawn->Update();

	srand(time(NULL));
}

void GameScene::Update()
{

	player->Update();

#pragma region スポーン

	if (spawntimer > 0) {
		spawntimer--;
	}
	if (spawntimer == 0) {
		if (enemyCount < enemy_max) {
			enemyCount++;

		}
		spawntimer = 150;
	}
	enemyAlive[enemyCount] = 1;
	enemy[enemyCount]->Update();

#pragma endregion



		object3d->Update();
		object3d2->Update();
		object3d3->Update();
		object3d4->Update();




		spawn->Update();

	
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画 
	//spriteBG->Draw();
	//sprite1->Draw();
	//sprite2->Draw();


	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
#pragma region	3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);
	Object3d2::PreDraw(cmdList);


	
	Spawn::PreDraw(cmdList);
#pragma endregion	
#pragma region 3Dオブクジェクトの描画
	for (int i = 0; i < enemy_max; i++) {
		if (enemyAlive[i]) {
			enemy[i]->Draw();
		}
	}
	player->Draw();
	object3d->Draw();
	object3d2->Draw();
	object3d3->Draw();
	object3d4->Draw();
	spawn->Draw();


#pragma endregion	
#pragma region	3Dオブジェクト描画後処理
	Object3d::PostDraw();
	Object3d2::PostDraw();


	Spawn::PostDraw();
#pragma endregion
#pragma endregion	
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	sprintf_s(str, "%d", score);
	debugText.Print(str, 10, 100, 1);
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

