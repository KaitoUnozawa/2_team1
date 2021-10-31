#pragma once
#include "GameScene.h"
#include "Title.h"
#include "Tutorial.h"

class SceneManager
{
#pragma region �ϐ�
private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	GameScene* game = nullptr;
	Title* title = nullptr;
	Tutorial* tutorial = nullptr;

	enum Scene {
		titleScene,
		tutorialScene,
		gameScene
	};
	Scene scene = titleScene;

#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	//�R���X�g���N�^
	SceneManager();
	//�f�X�g���N�^
	~SceneManager();
	//������
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//���t���[���X�V����
	void Update();
	//�`��
	void Draw();
};

