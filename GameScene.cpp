#include "GameScene.h"

//�R���X�g���N�^
GameScene::GameScene()
{
}

//�f�X�g���N�^
GameScene::~GameScene()
{
	//delete����
	safe_delete(spriteBG);
	safe_delete(object3d);
}

//������
void GameScene::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	////nullptr�`�F�b�N
	//assert(dxCommon);
	//assert(input);
	//assert(audio);

	//this->dxCommon = dxCommon;
	//this->input = input;
	//this->audio = audio;


	//�f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
	//if(!Object2D::SpriteCommonLoadTexture(spriteCommon,debugTextTexNum,L"Resources/DebugText.png",))
}

//���t���[��
void GameScene::Update()
{
}

//�`��
void GameScene::Draw()
{
}
