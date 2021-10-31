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


private:
	DirectXCommon* dxCommon = nullptr;
	//KeyboardInput* input = nullptr;
	//Audio* audio = nullptr;

	//エネミーモデル
	EnemyModel* enemy = nullptr;

	//プレイヤーの弾
	PlayerBullet* bullet = nullptr;

	//移動用？のスピード
	float enemySpeed1 = 0.05f;
	float enemyMoveSpeed = -0.05f;

	//生成したエネミーの総数？
	int enemyCount = 0;

	//どの方向に敵を移動させるか
	float angle = 0;

	//多分敵と弾の半径
	const float radius1 = 2.0f;
	const float radius2 = 2.0f;
	
	// スポーン用タイマー
	int spownTimer = 25;

public:
	//生存フラグ
	bool enemyAlive = false;

	//位置
	XMFLOAT3 position;
};