#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Object2D.h"
#include "DebugText.h"
#include "Audio.h"
#include "KeyboardInput.h"
#include "Player.h"
#include "Enemy.h"
#include "SpownPointModel.h"
#include "GamesceneWallUp.h"
#include "GamesceneWallLR.h"


using namespace Microsoft::WRL;
using namespace DirectX;

//ゲームシーン
class GameScene
{
#pragma region 変数
private: //静的メンバ変数
	//デバッグテキスト用のテクスチャ
	static const int debugTextTexNum = 0;

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyboardInput* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	//ゲームシーン用
	//音楽
	Audio::SoundData soundData[3];

	//壁
	GamesceneWallUp* wallUp = nullptr;
	GamesceneWallUp* wallDown = nullptr;
	GamesceneWallLR* wallRight = nullptr;
	GamesceneWallLR* wallLeft = nullptr;

	//スポーンポイント
	SpownPointModel* spown = nullptr;

	//プレイヤー
	Player* player = nullptr;
	PlayerBullet* bullet = nullptr;
	float bulletRadius = 1.0f;

	//エネミー
	static const int enemyMaxNum = 10; //最大数
	Enemy* enemy[enemyMaxNum]; //エネミー実体
	float enemyRadius = 4.0f;

	//スポーン用タイマー
	int spownTimer = 50;
	//発生したエネミーのカウント
	int enemyCount = 0;
	//生存フラグ
	bool enemyAlive[enemyMaxNum] = { false };


#pragma endregion

#pragma region 関数
private:
	bool CollisionBalltoBall(XMFLOAT3 aPos, float aRadius, XMFLOAT3 bPos, float bRadius);
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
#pragma endregion
};

