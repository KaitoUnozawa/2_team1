#include<Windows.h>
#include<DirectXTex.h>
#include<wrl.h>
#include<d3d12.h>
#include<dxgi1_6.h>
#include<d3dx12.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>

#include"WindowsAPI.h"  //ウィンドウ表示
#include"KeyboardInput.h"  //キーボード入力
#include"Object2D.h"  //2D画像(sprite)
#include"Object3D.h"  //3Dオブジェクト(Object)
#include"Audio.h" //音楽再生
#include"DebugText.h" //デバッグテキスト
#include"DirectXCommon.h"
#include"SafeDelete.h"
#include"GameScene.h"
#include"ModelObj.h"
#include"Title.h"
#include "SceneManager.h"
#include "PressSpaceFont.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xaudio2.lib")


using namespace DirectX;
using namespace Microsoft::WRL;


//Windowsアプリでのエントリーポイント（main関数）
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//ウィンドウ
	WindowsAPI* win = nullptr;
	win = new WindowsAPI();
	win->WindowCreate();

	MSG msg{}; //メッセージ



#ifdef _DEBUG
	//デバッグレイヤーをオンに
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG


	////DirectX初期化処理　ここから
		
	//DirectX汎用部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

	//初期化
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();

	
	////DirectInput(入力)初期化処理
	KeyboardInput* input = KeyboardInput::GetInstance();
	input->Init(win->hwnd);

	////DirectX初期化処理　ここまで


	////描画初期化処理　ここから
	// スプライト静的初期化
	if (!Object2D::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dオブジェクト静的初期化
	if (!Object3D::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// 3Dモデル静的初期化
	if (!ModelObj::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}
	if (!Wall::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}
	if (!EnemyModel::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}
	if (!TitleFont::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}
	if (!PressSpaceFont::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// ゲームシーンの初期化
	SceneManager* sceneManager = nullptr;
	sceneManager = new SceneManager();
	sceneManager->Init(dxCommon, input, audio);

	
	////描画初期化処理　ここまで


	while (true) //ゲームループ
	{
		//メッセージがあるか
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); //キー入力メッセージの処理
			DispatchMessage(&msg); //プロシージャにメッセージを送る
		}

		//×ボタンで終了メッセージが来たらゲームループを抜ける
		if (msg.message == WM_QUIT)
		{
			break;
		}


		////////////////DirectX毎フレーム処理 ここから

#pragma region 更新処理
		input->Update();
		sceneManager->Update();

#pragma endregion
		

		//////４．描画コマンド　ここから

#pragma region 描画コマンド
		//描画前処理
		dxCommon->PreDraw();

		sceneManager->Draw();
		
		//描画終了
		dxCommon->PostDraw();
#pragma endregion
		//////４．描画コマンド　ここまで


		////////////////DirectX毎フレーム処理 ここまで
	}
	//クラス(new)の消去
	//音声データ解放
	
	safe_delete(dxCommon);
	safe_delete(audio);
	//safe_delete(input);
	safe_delete(sceneManager);
	//safe_delete(gameScene);
	//safe_delete(title);

	//ウィンドウクラスを登録解除
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	return 0;
}

