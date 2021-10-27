#include "Player.h"
#include <time.h>
#include <cassert>

using namespace DirectX;

Player::Player()
{
}

Player::~Player()
{
	safe_delete(*activePlayerObj);
	safe_delete(*playerObj);

}

void Player::Initialize(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	//プレイヤー初期化
	{
		playerObj[DOWN] = PlayerModel::Create();
		playerObj[DOWN]->SetPosition({ 0.0f,-42.0f,0.0f });
		playerObj[DOWN]->SetScale({ 2.0f,2.0f,2.0f });
		playerObj[DOWN]->Update();

		playerObj[LEFT] = PlayerModel::Create();
		playerObj[LEFT]->SetPosition({ -42.0f,0.0f,0.0f });
		playerObj[LEFT]->SetScale({ 2.0f,2.0f,2.0f });
		playerObj[LEFT]->Update();

		playerObj[UP] = PlayerModel::Create();
		playerObj[UP]->SetPosition({ 0.0f,42.0f,0.0f });
		playerObj[UP]->SetScale({ 2.0f,2.0f,2.0f });
		playerObj[UP]->Update();

		playerObj[RIGHT] = PlayerModel::Create();
		playerObj[RIGHT]->SetPosition({ 42.0f,0.0f,0.0f });
		playerObj[RIGHT]->SetScale({ 2.0f,2.0f,2.0f });
		playerObj[RIGHT]->Update();
	}

	//アチーブ化プレイヤー初期化
	{
		activePlayerObj[DOWN] = PlayerActiveModel::Create();
		activePlayerObj[DOWN]->SetPosition({ 0.0f,-42.0f,0.0f });
		activePlayerObj[DOWN]->SetScale({ 3.0f,3.0f,3.0f });
		activePlayerObj[DOWN]->Update();

		activePlayerObj[LEFT] = PlayerActiveModel::Create();
		activePlayerObj[LEFT]->SetPosition({ -42.0f,0.0f,0.0f });
		activePlayerObj[LEFT]->SetScale({ 3.0f,3.0f,3.0f });
		activePlayerObj[LEFT]->Update();

		activePlayerObj[UP] = PlayerActiveModel::Create();
		activePlayerObj[UP]->SetPosition({ 0.0f,42.0f,0.0f });
		activePlayerObj[UP]->SetScale({ 3.0f,3.0f,3.0f });
		activePlayerObj[UP]->Update();

		activePlayerObj[RIGHT] = PlayerActiveModel::Create();
		activePlayerObj[RIGHT]->SetPosition({ 42.0f,0.0f,0.0f });
		activePlayerObj[RIGHT]->SetScale({ 3.0f,3.0f,3.0f });
		activePlayerObj[RIGHT]->Update();
	}

	bullet = new PlayerBullet();
	bullet->Initialize(dxCommon);
	bullet->SetPosition({ -500,-500,-500 });

	/*bullet2 = new Bullet2();
	bullet2->Initialize(dxCommon);*/
}

void Player::Update()
{
	XMFLOAT3 movePosition[4];
	for (int i = 0; i < 4; i++)
	{
		movePosition[i] = playerObj[i]->GetPosition();
	}

	XMFLOAT3 moveActivePosition[4];
	for (int i = 0; i < 4; i++)
	{
		moveActivePosition[i] = activePlayerObj[i]->GetPosition();
	}
	
	XMFLOAT3 bulletPos = bullet->GetPosition();
	//XMFLOAT3 position2 = bullet2->GetPosition();

#pragma region	プレイヤー操作と弾
	if (bulletMoveFlag == 0) {
		if (input->PressKeyTrigger(DIK_SPACE)) {
			bulletSelectFlag++;

			if (bulletSelectFlag == 5) {
				bulletSelectFlag = 1;
			}
			if (bulletSelectFlag == 1) {
				bulletMoveFlag = 1;
				playerActive[DOWN] = 0;
				playerActive[RIGHT] = 1;
				bulletPos.x = movePosition[0].x;
				bulletPos.y = movePosition[0].y;
				bulletPos.z = movePosition[0].z;
				bullet->SetPosition(bulletPos);
			}
			if (bulletSelectFlag == 2) {
				bulletMoveFlag = 1;
				playerActive[RIGHT] = 0;
				playerActive[UP] = 1;
				bulletPos.x = movePosition[1].x;
				bulletPos.y = movePosition[1].y;
				bulletPos.z = movePosition[1].z;
				bullet->SetPosition(bulletPos);
			}
			if (bulletSelectFlag == 3) {
				bulletMoveFlag = 1;
				playerActive[UP] = 0;
				playerActive[LEFT] = 1;
				bulletPos.x = movePosition[2].x;
				bulletPos.y = movePosition[2].y;
				bulletPos.z = movePosition[2].z;
				bullet->SetPosition(bulletPos);
			}
			if (bulletSelectFlag == 4) {
				bulletMoveFlag = 1;
				playerActive[LEFT] = 0;
				playerActive[DOWN] = 1;
				bulletPos.x = movePosition[3].x;
				bulletPos.y = movePosition[3].y;
				bulletPos.z = movePosition[3].z;
				bullet->SetPosition(bulletPos);
			}
		}

		
	}
	if (bulletMoveFlag == 1)
	{
		if (bulletSelectFlag == 1) {
			bulletPos.y += 2;
			if (bulletPos.y >= 50) {
				bulletMoveFlag = 0;
				bulletPos = { -500,-500,-500 };
			}
		}
		if (bulletSelectFlag == 2) {
			bulletPos.x += 2;
			if (bulletPos.x >= 50) {
				bulletMoveFlag = 0;
				bulletPos = { -500,-500,-500 };
			}
		}
		if (bulletSelectFlag == 3) {
			bulletPos.y -= 2;
			if (bulletPos.y <= -50) {
				bulletMoveFlag = 0;
				bulletPos = { -500,-500,-500 };
			}
		}
		if (bulletSelectFlag == 4) {
			bulletPos.x -= 2;
			if (bulletPos.x <= -50) {
				bulletMoveFlag = 0;
				bulletPos = { -500,-500,-500 };
			}
			
		}
	}
#pragma endregion

#pragma region	プレイヤー移動
	// プレイヤーオブジェクト移動
	for (int i = 0; i < 4; i++)
	{
		if (i % 2 == 0)movePosition[i].x += playerSpeed[i];
		else movePosition[i].y += playerSpeed[i];
		if (i % 2 == 0) moveActivePosition[i].x += playerSpeed[i];
		else moveActivePosition[i].y += playerSpeed[i];
		
	}
	
	//反転通常処理
	{
		if (movePosition[0].x <= -43) { playerSpeed[0] = 0.5f; }
		else if (movePosition[0].x >= 43) { playerSpeed[0] = -0.5f; }
		if (movePosition[1].y >= 43) { playerSpeed[1] = -0.5f; }
		else if (movePosition[1].y <= -43) { playerSpeed[1] = 0.5f; }
		if (movePosition[2].x >= 43) { playerSpeed[2] = -0.5f; }
		else if (movePosition[2].x <= -43) { playerSpeed[2] = 0.5f; }
		if (movePosition[3].y <= -43) { playerSpeed[3] = 0.5f; }
		else if (movePosition[3].y >= 43) { playerSpeed[3] = -0.5f; }

	}
	//アチーブ用反転処理
	{
		if (moveActivePosition[0].x <= -43) { playerSpeed[0] = 0.5f; }
		else if (moveActivePosition[0].x >= 43) { playerSpeed[0] = -0.5f; }
		if (moveActivePosition[1].y >= 43) { playerSpeed[1] = -0.5f; }
		else if (moveActivePosition[1].y <= -43) { playerSpeed[1] = 0.5f; }
		if (moveActivePosition[2].x >= 43) { playerSpeed[2] = -0.5f; }
		else if (moveActivePosition[2].x <= -43) { playerSpeed[2] = 0.5f; }
		if (moveActivePosition[3].y <= -43) { playerSpeed[3] = 0.5f; }
		else if (moveActivePosition[3].y >= 43) { playerSpeed[3] = -0.5f; }

	}
	
#pragma region	エネミー以外のSetter

	for (int i = 0; i < 4; i++)
	{
		playerObj[i]->SetPosition(movePosition[i]);
	}
	
	for (int i = 0; i < 4; i++)
	{
		activePlayerObj[i]->SetPosition(moveActivePosition[i]);
	}
	
	bullet->SetPosition(bulletPos);
	//bullet2->SetPosition(position2);

#pragma endregion

	for (int i = 0; i < 4; i++)
	{
		playerObj[i]->Update();
	}

	for (int i = 0; i < 4; i++)
	{
		activePlayerObj[i]->Update();
	}

	bullet->Update();
	//bullet2->Update();
#pragma endregion

	bullet->Update();
}

void Player::Draw()
{
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
	PlayerModel::PreDraw(cmdList);
	PlayerActiveModel::PreDraw(cmdList);
	bullet->Draw();
	//bullet2->Draw();

	if (playerActive[0] == 0) {
		playerObj[DOWN]->Draw();
	}
	else if (playerActive[0] == 1) {
		activePlayerObj[DOWN]->Draw();
	}

	if (playerActive[1] == 0) {
		playerObj[RIGHT]->Draw();
	}
	else if (playerActive[1] == 1) {
		activePlayerObj[RIGHT]->Draw();
	}

	if (playerActive[2] == 0) {
		playerObj[UP]->Draw();
	}
	else if (playerActive[2] == 1) {
		activePlayerObj[UP]->Draw();
	}

	if (playerActive[3] == 0) {
		playerObj[LEFT]->Draw();
	}
	else if (playerActive[3] == 1) {
		activePlayerObj[LEFT]->Draw();
	}
	
	
	PlayerModel::PostDraw();
	PlayerActiveModel::PostDraw();

}
