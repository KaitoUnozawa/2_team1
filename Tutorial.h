#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
#include "Object3D.h"
#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"
#include "ModelObj.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class Tutorial
{
#pragma region 変数
private: //静的メンバ変数
	

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	//ゲームシーン用
	Object2D* spriteBG = nullptr;
	Object2D* sprite1 = nullptr;

	//Audio::SoundData soundData[2];
#pragma endregion

#pragma region 関数
public: //メンバ関数
	//コンストラクタ
	Tutorial();
	//デストラクタ
	~Tutorial();
	//初期化
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//毎フレーム更新処理
	void Update();
	//描画
	void Draw();
#pragma endregion
};

