#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "KeyboardInput.h"
#include "Audio.h"
#include"PlayerModel.h"
#include"PlayerActiveModel.h"
#include"PlayerBullet.h"
//#include"bullet2.h"
#include <DirectXMath.h>
class Player {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Player();
	~Player();
	void Initialize(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();


private:
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;

	PlayerBullet* bullet = nullptr;
	//Bullet2* bullet2 = nullptr;

	//�v���C���[
	PlayerModel* pobject = nullptr;
	PlayerModel* pobject2 = nullptr;
	PlayerModel* pobject3 = nullptr;
	PlayerModel* pobject4 = nullptr;

	//�e�𔭎˂ł���v���C���[
	PlayerActiveModel* p2object = nullptr;
	PlayerActiveModel* p2object2 = nullptr;
	PlayerActiveModel* p2object3 = nullptr;
	PlayerActiveModel* p2object4 = nullptr;
	//���ڃv���C���[�؂�ւ�
	int bflag = 0;
	//�e���ˎ��Ɏg�p����t���O
	int mflag = 0;
	//���ڂ���Ă��
	int playerActive1 = 1;
	int playerActive2 = 0;
	int playerActive3 = 0;
	int playerActive4 = 0;

	//�v���C���[�̃X�s�[�h
	float playerSpeed1 = 0.5f;
	float playerSpeed2 = -0.5f;
	float playerSpeed3 = -0.5f;
	float playerSpeed4 = 0.5f;


};