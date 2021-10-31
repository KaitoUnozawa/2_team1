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
	float GetRadius() { return radius; }

private:
	DirectXCommon* dxCommon = nullptr;
	//�G�l�~�[���f��
	EnemyModel* enemy = nullptr;

	//�ړ��p�H�̃X�s�[�h
	float enemyMoveSpeed = -0.05f;


	//�ǂ̕����ɓG���ړ������邩
	float angle = 0;
	XMFLOAT3 moveVector;


public:
	//�����t���O
	bool enemyAlive = false;

	//�ʒu
	XMFLOAT3 position;
	float radius = 4.0f;
};