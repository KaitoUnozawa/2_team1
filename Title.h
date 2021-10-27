#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
//#include "Object3D.h"
//#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"
//#include "ModelObj.h"
#include "EnemyModel.h"
#include "TitleFont.h"
#include "Wall.h"
#include "PressSpaceFont.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class Title
{
#pragma region �ϐ�
private: //�ÓI�����o�ϐ�
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`��
	//static const int debugTextTexNum = 0;

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	//DebugText debugText;


	//�Q�[���V�[���p
	TitleFont* titleFont = nullptr;
	PressSpaceFont* pressFont = nullptr;
	Wall* background = nullptr;
	EnemyModel* enemy[4];
	//Audio::SoundData soundData[2];
#pragma endregion

#pragma region �֐�
public: //�����o�֐�
	//�R���X�g���N�^
	Title();
	//�f�X�g���N�^
	~Title();
	//������
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//���t���[���X�V����
	void Update();
	//�`��
	void Draw();
#pragma endregion
};
