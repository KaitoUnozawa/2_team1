#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
#include "Object3D.h"
#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"

class GameScene
{
private:
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


private: //�ÓI�����o�ϐ�
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`��
	static const int debugTextTexNum = 0;

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Object2D::SpriteCommon spriteCommon;

	//�Q�[���V�[���p
	Object2D* spriteBG = nullptr;
	Object3D* object3d = nullptr;


public: //�����o�֐�
	//�R���X�g���N�^
	GameScene();

	//�f�X�g���N�^
	~GameScene();

	//������
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);

	//���t���[���X�V����
	void Update();

	//�`��
	void Draw();

};

