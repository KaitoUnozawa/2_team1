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
	HRESULT result;
		

	//DirectX汎用部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);


	//初期化
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();
	////音声読み込み
	Audio::SoundData soundData[2];
	soundData[0] = audio->SoundLoadWave("Resources/Sounds/test.wav");
	soundData[1] = audio->SoundLoadWave("Resources/Sounds/Destroy.wav");

	
	////DirectInput(入力)初期化処理
	KeyboardInput* input = nullptr;
	input = new KeyboardInput();
	input->Init(WindowsAPI::hwnd);


	////DirectX初期化処理　ここまで

	


	////描画初期化処理　ここから
	

	////3Dオブジェクト初期化
 //   Object3D::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height);
	////スプライト用パイプライン生成
	//Object2D::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height);

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

	//定数バッファへのデータ転送（初期化）
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f), //上下画角60度
		(float)WindowsAPI::window_width / WindowsAPI::window_height, //アスペクト比
		0.1f, 1000.0f);//手前，奥

	//定数バッファ・テクスチャバッファ用のデスクリプタヒープ
	const int constantBufferNum = 128; //定数バッファの最大数
	ComPtr<ID3D12DescriptorHeap> basicDescHeap;
	//情報構造体
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; //シェーダーから見える
	descHeapDesc.NumDescriptors = constantBufferNum + 1; //定数バッファの数(+1->SRV)


	//デスクリプタヒープの生成
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&basicDescHeap));
	

	//デバッグテキスト
	DebugText debugText;

	//デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 2;
	//デバッグテキスト用のテクスチャ読み込み
	Object2D::LoadTexture(debugTextTexNumber, L"Resources/DebugText.png");
	//デバッグテキスト初期化
	debugText.Init(debugTextTexNumber);

	// ゲームシーンの初期化
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Init(dxCommon, input, audio);
	
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
		gameScene->Update();
		//キーが押されているときの処理例
		if (KeyboardInput::PressKeyTrigger(DIK_0))
		{
			audio->SoundPlayWave(audio->xAudio2.Get(), soundData[1]);
		}

		//音声再生例
		//SoundPlayWave(xAudio2.Get(),soundData1);
		if (KeyboardInput::PressKeyTrigger(DIK_M))
		{
			audio->SoundPlayWave(audio->xAudio2.Get(), soundData[0]);
		}

#pragma endregion
		

		//////４．描画コマンド　ここから

#pragma region 描画コマンド
		//描画前処理
		dxCommon->PreDraw();

		gameScene->Draw();

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
	safe_delete(input);
	safe_delete(gameScene);

	//ウィンドウクラスを登録解除
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	//コンソールへの文字出力
	OutputDebugStringA("Hello,DirectX!!\n");

	return 0;
}

