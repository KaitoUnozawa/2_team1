#include "GameScene.h"

//コンストラクタ
GameScene::GameScene()
{
}

//デストラクタ
GameScene::~GameScene()
{
	//delete処理
	safe_delete(spriteBG);
	safe_delete(object3d);
}

//初期化
void GameScene::Init(DirectXCommon* dxCommon, KeyboardInput* input, Audio* audio)
{
	////nullptrチェック
	//assert(dxCommon);
	//assert(input);
	//assert(audio);

	//this->dxCommon = dxCommon;
	//this->input = input;
	//this->audio = audio;


	//デバッグテキスト用テクスチャ読み込み
	//if(!Object2D::SpriteCommonLoadTexture(spriteCommon,debugTextTexNum,L"Resources/DebugText.png",))
}

//毎フレーム
void GameScene::Update()
{
}

//描画
void GameScene::Draw()
{
}
