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

	bool PressSpace() { return true; }


public:
	PlayerBullet* bullet = nullptr;
	//�e���ˎ��Ɏg�p����t���O
	int bulletMoveFlag = 0;

private:
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;

	
	//Bullet2* bullet2 = nullptr;

	//�v���C���[
	PlayerModel* playerObj[4];
	//�e�𔭎˂ł���v���C���[
	PlayerActiveModel* activePlayerObj[4];
	//�����ɑΉ�
	enum Direction {
		DOWN, //0
		LEFT, //1
		UP,   //2
		RIGHT //3
	};
	Direction direction = DOWN;

	//���ڃv���C���[�؂�ւ�
	int bulletSelectFlag = 0;
	
	//���ڂ���Ă��
	bool playerActive[4] = { 1,0,0,0 };

	//�v���C���[�̃X�s�[�h
	float playerSpeed[4] = { 0.5f,-0.5f,-0.5f,0.5f };
	


};