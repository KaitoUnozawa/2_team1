#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include"PlayerObject.h"
#include"PlayerObject2.h"
#include"bullet.h"
#include"bullet2.h"
#include <DirectXMath.h>
class Player {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Player();
	~Player();
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private:
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	
	Bullet* bullet = nullptr;
	Bullet2* bullet2 = nullptr;

	PlayerObject* pobject = nullptr;
	PlayerObject* pobject2 = nullptr;
	PlayerObject* pobject3 = nullptr;
	PlayerObject* pobject4 = nullptr;

	PlayerObject2* p2object = nullptr;
	PlayerObject2* p2object2 = nullptr;
	PlayerObject2* p2object3 = nullptr;
	PlayerObject2* p2object4 = nullptr;
	int bflag = 0;
	int mflag = 0;
	int playerActive1 = 1;
	int playerActive2 = 0;
	int playerActive3 = 0;
	int playerActive4 = 0;

	//プレイヤーのスピード
	float playerSpeed1 = 0.5f;
	float playerSpeed2 = -0.5f;
	float playerSpeed3 = -0.5f;
	float playerSpeed4 = 0.5f;


};