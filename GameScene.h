#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
#include "Object3D.h"
#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"

class GameScene
{
private:
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectXを省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;


private: //静的メンバ変数
	//デバッグテキスト用のテクスチャ
	static const int debugTextTexNum = 0;

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;
	Object2D::SpriteCommon spriteCommon;

	//ゲームシーン用
	Object2D* spriteBG = nullptr;
	Object3D* object3d = nullptr;


public: //メンバ関数
	//コンストラクタ
	GameScene();

	//デストラクタ
	~GameScene();

	//初期化
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);

	//毎フレーム更新処理
	void Update();

	//描画
	void Draw();

};

