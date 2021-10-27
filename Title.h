#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
//#include "Object3D.h"
//#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"
//#include "ModelObj.h"
#include "EnemyModel.h"
#include "TitleFont.h"
#include "Wall.h"
#include "PressSpaceFont.h"

using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class Title
{
#pragma region 変数
private: //静的メンバ変数
	//デバッグテキスト用のテクスチャ
	//static const int debugTextTexNum = 0;

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	//DebugText debugText;


	//ゲームシーン用
	TitleFont* titleFont = nullptr;
	PressSpaceFont* pressFont = nullptr;
	Wall* background = nullptr;
	EnemyModel* enemy[4];
	//Audio::SoundData soundData[2];
#pragma endregion

#pragma region 関数
public: //メンバ関数
	//コンストラクタ
	Title();
	//デストラクタ
	~Title();
	//初期化
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//毎フレーム更新処理
	void Update();
	//描画
	void Draw();
#pragma endregion
};
