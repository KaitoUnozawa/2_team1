#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
//#include "KeyboardInput.h"
//#include "Audio.h"
#include "EnemyModel.h"
#include "PlayerBullet.h"
#include <DirectXMath.h>

class Enemy {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Enemy();
	~Enemy();
	void Init(DirectXCommon* dxCommon);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }


private:
	DirectXCommon* dxCommon = nullptr;
	//KeyboardInput* input = nullptr;
	//Audio* audio = nullptr;

	//�G�l�~�[���f��
	EnemyModel* enemy = nullptr;

	//�v���C���[�̒e
	PlayerBullet* bullet = nullptr;

	//�ړ��p�H�̃X�s�[�h
	float enemySpeed1 = 0.05f;
	float enemyMoveSpeed = -0.05f;

	//���������G�l�~�[�̑����H
	int enemyCount = 0;

	//�ǂ̕����ɓG���ړ������邩
	float angle = 0;

	//�����G�ƒe�̔��a
	const float radius1 = 2.0f;
	const float radius2 = 2.0f;
	
	// �X�|�[���p�^�C�}�[
	int spownTimer = 25;

public:
	//�����t���O
	bool enemyAlive = false;

	//�ʒu
	XMFLOAT3 position;
};