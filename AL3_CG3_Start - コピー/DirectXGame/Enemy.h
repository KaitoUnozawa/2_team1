#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include"EnemyObject.h"
#include"Bullet.h"
#include <DirectXMath.h>
class Enemy {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Enemy();
	~Enemy();
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// ñàÉtÉåÅ[ÉÄèàóù
	/// </summary>
	void Update();

	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
private:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	EnemyObject* enemy = nullptr;
	Bullet*bullet = nullptr;
	int enemyAlive;
	float enemySpeed1 =  0.05f;
	float enemySpeed2 =  -0.05f;
	int enemyCount = 0;
	float angle =  0 ;
	const float radius1 = 2.0f;
	const float radius2 = 2.0f;
	XMFLOAT3 position;
};