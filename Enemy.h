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
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Enemy();
	~Enemy();
	void Init(DirectXCommon* dxCommon);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	float GetRadius() { return radius; }

private:
	DirectXCommon* dxCommon = nullptr;
	//エネミーモデル
	EnemyModel* enemy = nullptr;

	//移動用？のスピード
	float enemyMoveSpeed = -0.05f;


	//どの方向に敵を移動させるか
	float angle = 0;
	XMFLOAT3 moveVector;


public:
	//生存フラグ
	bool enemyAlive = false;

	//位置
	XMFLOAT3 position;
	float radius = 4.0f;
};