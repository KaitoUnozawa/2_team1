#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(object3d);
	safe_delete(model);
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
	if (!Object2D::LoadTexture(1, L"Resources/texture.png")) {
		assert(0);
		return;
	}
	// �w�i�X�v���C�g����
	spriteBG = Object2D::CreateSprite(1, { 0.0f,0.0f });
	// 3D�I�u�W�F�N�g����
	object3d = Object3D::CreateObject();
	object3d->Update();
	//3D���f���쐬
	model = ModelObj::Create();
	model->Update();

	soundData[0] = audio->SoundLoadWave("Resources/test.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Alarm01.wav");
}

void GameScene::Update()
{
	// �I�u�W�F�N�g�ړ�
	if (input->PressKey(DIK_UP) || input->PressKey(DIK_DOWN) || input->PressKey(DIK_RIGHT) || input->PressKey(DIK_LEFT))
	{
		// ���݂̍��W���擾
		XMFLOAT3 position = model->GetPosition();

		// �ړ���̍��W���v�Z
		if (input->PressKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PressKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PressKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PressKey(DIK_LEFT)) { position.x -= 1.0f; }

		// ���W�̕ύX�𔽉f
		model->SetPosition(position);
	}

	// �J�����ړ�
	if (input->PressKey(DIK_W) || input->PressKey(DIK_S) || input->PressKey(DIK_D) || input->PressKey(DIK_A))
	{
		if (input->PressKey(DIK_W)) { Object3D::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PressKey(DIK_S)) { Object3D::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PressKey(DIK_D)) { Object3D::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PressKey(DIK_A)) { Object3D::CameraMoveVector({ -1.0f,0.0f,0.0f }); }
	}

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

	model->Update();
	//�L�[�{�[�h���͍X�V
	KeyboardInput::Update();

	
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
// 3D���f���`��O����
	ModelObj::PreDraw(cmdList);

// 3D�I�u�N�W�F�N�g�̕`��
	model->Draw();

/// <summary>
/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
/// </summary>

// 3D�I�u�W�F�N�g�`��㏈��
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
