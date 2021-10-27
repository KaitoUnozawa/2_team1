#include "Title.h"
#include <cassert>

using namespace DirectX;

Title::Title()
{
}

Title::~Title()
{
	safe_delete(titleFont);
	safe_delete(pressFont);
	safe_delete(background);
	safe_delete(*enemy);
}

void Title::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;


	//3Dモデル作成
	background = Wall::Create();
	background->Update();

	for (int i = 0; i < 4; i++)
	{
		enemy[i] = EnemyModel::Create();
	}
#pragma region 位置調整
	enemy[0]->SetPosition({ -30,25,10 });
	enemy[0]->SetScale(1.5f);
	enemy[1]->SetPosition({ 60,60,100 });
	enemy[1]->SetScale(10);
	enemy[2]->SetPosition({ 5,0,0 });
	//enemy[2]->SetScale(1);
	enemy[3]->SetPosition({ -40,-20,0 });
	enemy[3]->SetScale(6);
#pragma endregion
	for (int i = 0; i < 4; i++)
	{
		enemy[i]->Update();
	}

	pressFont = PressSpaceFont::Create();
	pressFont->Update();
	titleFont = TitleFont::Create();
	titleFont->Update();



	//音楽読み込み
	

}

void Title::Update()
{
	background->Update();

	for (int i = 0; i < 4; i++)
	{
		enemy[i]->Update();
	}

	pressFont->Update();
	titleFont->Update();

	//キーボード入力更新
	KeyboardInput::Update();
}

void Title::Draw()
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
	//背景
	background->PreDraw(cmdList);
	background->Draw();
	background->PostDraw();
	
	for (int i = 0; i < 4; i++)
	{
		enemy[i]->PreDraw(cmdList);
		enemy[i]->Draw();
		enemy[i]->PostDraw();
	}

	pressFont->PreDraw(cmdList);
	pressFont->Draw();
	pressFont->PostDraw();

	titleFont->PreDraw(cmdList);
	titleFont->Draw();
	titleFont->PostDraw();
	
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	//Object2D::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	//AL3 1-2追加
	//sprite1->Draw();
	//sprite2->Draw();

	/// </summary>


	// デバッグテキストの描画
	//debugText.DrawAll(cmdList);

	// スプライト描画後処理
	//Object2D::PostDraw();
#pragma endregion
}
