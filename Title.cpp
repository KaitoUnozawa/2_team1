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
	// nullptr�`�F�b�N
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;


	//3D���f���쐬
	background = Wall::Create();
	background->Update();

	for (int i = 0; i < 4; i++)
	{
		enemy[i] = EnemyModel::Create();
	}
#pragma region �ʒu����
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



	//���y�ǂݍ���
	

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

	//�L�[�{�[�h���͍X�V
	KeyboardInput::Update();
}

void Title::Draw()
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
	//�w�i
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

#pragma region �O�i�X�v���C�g�`��
	// �O�i�X�v���C�g�`��O����
	//Object2D::PreDraw(cmdList);

	/// <summary>
	/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ��ł���

	//AL3 1-2�ǉ�
	//sprite1->Draw();
	//sprite2->Draw();

	/// </summary>


	// �f�o�b�O�e�L�X�g�̕`��
	//debugText.DrawAll(cmdList);

	// �X�v���C�g�`��㏈��
	//Object2D::PostDraw();
#pragma endregion
}
