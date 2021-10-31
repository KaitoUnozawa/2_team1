#include "GameScene.h"
#include <cassert>
#include <time.h>

using namespace DirectX;

//�����m�̓����蔻��
bool GameScene::CollisionBalltoBall(XMFLOAT3 aPos, float aRadius, XMFLOAT3 bPos, float bRadius)
{
	float x = (aPos.x - bPos.x);
	float y = (aPos.y - bPos.y);
	float z = (aPos.z - bPos.z);
	float r = (aRadius + bRadius);
	return ((x * x + y * y + z * z) <= r * r);
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
	safe_delete(*enemy);
}

void GameScene::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	if (!Object2D::LoadTexture(debugTextTexNum, L"Resources/DebugText.png")) {
		assert(0);
		return;
	}
	// �f�o�b�O�e�L�X�g������
	debugText.Init(debugTextTexNum);

	//3D���f��
#pragma region ��
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

	//�v���C���[
	player = new Player();
	player->Initialize(dxCommon, input, audio);
	bullet = new PlayerBullet();
	bullet->Initialize(dxCommon);

	//�G�l�~�[
	

	//�X�|�[���|�C���g
	spown = SpownPointModel::Create();
	spown->Update();

	//���y
	soundData[0] = audio->SoundLoadWave("Resources/Shot.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Destroy.wav");
	soundData[2] = audio->SoundLoadWave("Resources/musicloop.wav");
	//�Đ�
	//audio->SoundPlayWave(audio->xAudio2.Get(), soundData[2], Audio::loop);
}

void GameScene::Update()
{

	//Space�Œe����
	if (input->PressKeyTrigger(DIK_SPACE) && !bullet->GetIsAlive())
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0]);
		bullet->ShotInit(player->GetActiveNumber(),player->GetActivePos());
		player->ChangeActivePlayer();
		
	}

#pragma region �e�ƃG�l�~�[�̓����蔻��

	//for (int i = 0; i < enemyMaxNum; i++)
	//{
	//	/*float x = (player->bullet->GetPosition().x - enemy[i]->position.x);
	//	float y = (player->bullet->GetPosition().y - enemy[i]->position.y);
	//	float z = (enemy[i]->position.z - player->bullet->GetPosition().z);
	//	float r = (bulletRadius + enemyRadius);
	//	if ((x*x + y*y + z*z) <= r*r) {
	//		enemy[i]->enemyAlive = false;
	//		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[1]);
	//	}*/
	//}

#pragma endregion

#pragma region �G�l�~�[����
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

	
	//��
	{
		wallUp->Update();
		wallDown->Update();
		wallRight->Update();
		wallLeft->Update();
	}
	//�e
	bullet->Update();
	//�v���C���[
	player->Update();
	//�X�|�[���|�C���g
	spown->Update();
	
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	//Object3D::PreDraw(cmdList);
	//Object3D::PostDraw();
#pragma endregion

#pragma region 3D���f���`��
	//��
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
	//�X�|�[���|�C���g
	SpownPointModel::PreDraw(cmdList);
	spown->Draw();
	SpownPointModel::PostDraw();

	//�v���C���[
	player->Draw();
	bullet->Draw();
	////�G�l�~�[
	//for (int i = 0; i < enemyMaxNum; i++) {
	//	if (enemyAlive[i])
	//	{
	//		enemy[i]->Draw();
	//	}
	//}

#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Object2D::PreDraw(cmdList);
	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);
	// �X�v���C�g�`��㏈��
	Object2D::PostDraw();
#pragma endregion
}
