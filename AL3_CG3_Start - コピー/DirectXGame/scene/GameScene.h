#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "Object3d2.h"
#include "DebugText.h"
#include "Audio.h"
#include"Player.h"

#include"Enemy.h"

#include"SpawnObject.h"
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;	
	Sprite* sprite1 = nullptr;
	Sprite* sprite2 = nullptr;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* spriteBG = nullptr;
	Object3d* object3d = nullptr;
	Object3d* object3d2 = nullptr;
	Object3d2* object3d3 = nullptr;
	Object3d2* object3d4 = nullptr;

	Player* player = nullptr;






	static const int enemy_max = 100;

	Enemy* enemy[enemy_max] = {0};

	Spawn* spawn = nullptr;
	
	// フラグ
	int bflag = 0;
	int mflag = 0;
	int tflag = 0;
	int emflag[enemy_max] = { 0 };
	int enemyAlive[enemy_max];



	float enemySpeed1[enemy_max] = { 0.05f };
	float enemySpeed2[enemy_max] = { -0.05f };

	const float radius1 = 2.0f;
	const float radius2 = 2.0f;
	int spawntimer = 50;
	int timer = 50;
	
	float angle[enemy_max] = { 0 };

	int enemyCount = 0;
	int CollisionCount = 0;
	int score = 0;
	char str[100];
	XMFLOAT3 BMposition;
	XMFLOAT3 BM2position;

};

