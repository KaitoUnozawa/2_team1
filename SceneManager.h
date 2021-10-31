#pragma once
#include "GameScene.h"
#include "Title.h"
#include "Tutorial.h"

class SceneManager
{
#pragma region 変数
private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	GameScene* game = nullptr;
	Title* title = nullptr;
	Tutorial* tutorial = nullptr;

	enum Scene {
		titleScene,
		tutorialScene,
		gameScene
	};
	Scene scene = titleScene;

#pragma endregion

#pragma region 関数
public: //メンバ関数
	//コンストラクタ
	SceneManager();
	//デストラクタ
	~SceneManager();
	//初期化
	void Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio);
	//毎フレーム更新処理
	void Update();
	//描画
	void Draw();
};

