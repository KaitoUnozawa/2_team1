#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"
#include "Player.h"
#include "Enemy.h"
#include "SpownPointModel.h"
#include "GamesceneWallUp.h"
#include "GamesceneWallLR.h"
#include <vector>


using namespace Microsoft::WRL;
using namespace DirectX;

//�Q�[���V�[��
class GameScene
{
#pragma region �ϐ�
private: //�ÓI�����o�ϐ�
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`��
	static const int debugTextTexNum = 0;

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	//�Q�[���V�[���p
	//���y
	Audio::SoundData soundData[3];

	//��
	GamesceneWallUp* wallUp = nullptr;
	GamesceneWallUp* wallDown = nullptr;
	GamesceneWallLR* wallRight = nullptr;
	GamesceneWallLR* wallLeft = nullptr;

	//�X�|�[���|�C���g
	SpownPointModel* spown = nullptr;

	//�v���C���[
	Player* player = nullptr;
	PlayerBullet* bullet = nullptr;

	//�G�l�~�[
	std::vector<Enemy *> enemys; //�G�l�~�[����

	//�X�|�[���p�^�C�}�[
	int spownTimer = 50;
	
	//�X�R�A
	int score = 0;

#pragma endregion

#pragma region �֐�
private:
	bool CollisionBalltoBall(XMFLOAT3 aPos, float aRadius, XMFLOAT3 bPos, float bRadius);
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
#pragma endregion
private:
	int GameCounter;
};

