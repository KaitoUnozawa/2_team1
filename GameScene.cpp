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

	// �w�i�e�N�X�`���ǂݍ���
	if (!Object2D::LoadTexture(1, L"Resources/titleFont/blue.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	//spriteBG = Object2D::CreateSprite(1, { 0.0f,0.0f });

	// 3D�I�u�W�F�N�g����
	//object3d = Object3D::CreateObject();
	//object3d->Update();

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



	soundData[0] = audio->SoundLoadWave("Resources/Shot.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Destroy.wav");
}

void GameScene::Update()
{
	//// �I�u�W�F�N�g�ړ�
	//if (input->PressKey(DIK_UP) || input->PressKey(DIK_DOWN) || input->PressKey(DIK_RIGHT) || input->PressKey(DIK_LEFT))
	//{
	//	// ���݂̍��W���擾
	//	XMFLOAT3 position = model->GetPosition();

	//	// �ړ���̍��W���v�Z
	//	if (input->PressKey(DIK_UP)) { position.y += 1.0f; }
	//	else if (input->PressKey(DIK_DOWN)) { position.y -= 1.0f; }
	//	if (input->PressKey(DIK_RIGHT)) { position.x += 1.0f; }
	//	else if (input->PressKey(DIK_LEFT)) { position.x -= 1.0f; }

	//	// ���W�̕ύX�𔽉f
	//	model->SetPosition(position);
	//}

	//// �J�����ړ�
	//if (input->PressKey(DIK_W) || input->PressKey(DIK_S) || input->PressKey(DIK_D) || input->PressKey(DIK_A))
	//{
	//	if (input->PressKey(DIK_W)) { Object3D::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
	//	else if (input->PressKey(DIK_S)) { Object3D::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
	//	if (input->PressKey(DIK_D)) { Object3D::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
	//	else if (input->PressKey(DIK_A)) { Object3D::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	//}

	//�L�[��������Ă���Ƃ��̏�����
	if (input->PressKeyTrigger(DIK_0))
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[1]);
	}

	//�����Đ���
	//SoundPlayWave(xAudio2.Get(),soundData1);
	if (input->PressKeyTrigger(DIK_M))
	{
		audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0]);
	}

	//model->Update();
	//�L�[�{�[�h���͍X�V
	input->Update();

	//��
	{
		wallUp->Update();
		wallDown->Update();
		wallRight->Update();
		wallLeft->Update();
	}
	
	
}

void GameScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region �w�i�X�v���C�g�`��
	// �w�i�X�v���C�g�`��O����
	//Object2D::PreDraw(cmdList);
	// �w�i�X�v���C�g�`��
	//spriteBG->Draw();

	/// <summary>
	/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ��ł���
	/// </summary>

	// �X�v���C�g�`��㏈��
	//Object2D::PostDraw();
	// �[�x�o�b�t�@�N���A
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D�I�u�W�F�N�g�`��
	// 3D�I�u�W�F�N�g�`��O����
	//Object3D::PreDraw(cmdList);

	// 3D�I�u�N�W�F�N�g�̕`��
	//object3d->Draw();

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
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
	

	ModelObj::PreDraw(cmdList);
	ModelObj::PostDraw();

	
#pragma endregion

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	Object2D::PreDraw(cmdList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���

	//AL3 1-2�ǉ�
	//sprite1->Draw();
	//sprite2->Draw();

	/// </summary>


	// �f�o�b�O�e�L�X�g�̕`��
	debugText.DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	Object2D::PostDraw();
#pragma endregion
}
