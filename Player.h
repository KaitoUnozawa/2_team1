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
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Player();
	~Player();
	void Initialize(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool PressSpace() { return true; }


public:
	PlayerBullet* bullet = nullptr;
	//弾発射時に使用するフラグ
	int bulletMoveFlag = 0;

private:
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;

	
	//Bullet2* bullet2 = nullptr;

	//プレイヤー
	PlayerModel* playerObj[4];
	//弾を発射できるプレイヤー
	PlayerActiveModel* activePlayerObj[4];
	//方向に対応
	enum Direction {
		DOWN, //0
		LEFT, //1
		UP,   //2
		RIGHT //3
	};
	Direction direction = DOWN;

	//注目プレイヤー切り替え
	int bulletSelectFlag = 0;
	
	//注目されてるよ
	bool playerActive[4] = { 1,0,0,0 };

	//プレイヤーのスピード
	float playerSpeed[4] = { 0.5f,-0.5f,-0.5f,0.5f };
	


};