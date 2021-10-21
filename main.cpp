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
#include"Camera.h" //カメラ制御
#include"Player.h" //プレイヤー
#include"Audio.h" //音楽再生
#include"DebugText.h" //デバッグテキスト
#include"DirectXCommon.h"
#include"SafeDelete.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xaudio2.lib")


using namespace DirectX;
using namespace Microsoft::WRL;


////ウィンドウプロシージャ
//LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	//メッセージで分岐
//	switch (msg)
//	{
//		case WM_DESTROY: //ウィンドウが破棄された
//			PostQuitMessage(0); //OSに対して、アプリの終了を伝える
//			return 0;
//	}
//	return DefWindowProc(hwnd, msg, wparam, lparam); //標準の処理を行う
//}


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
	/*ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;*/

	

	//DirectX汎用部分
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);


	//サウンド再生
	//ComPtr<IXAudio2> xAudio2;
	//IXAudio2MasteringVoice* masterVoice;
	//XAudioエンジンのインスタンスを生成
	//result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	//マスターボイスを生成
	//result = xAudio2->CreateMasteringVoice(&masterVoice);

	//初期化
	Audio audio;
	audio.Init();
	////音声読み込み
	Audio::SoundData soundData[2];
	soundData[0] = audio.SoundLoadWave("Resources/Alarm01.wav");
	soundData[1] = audio.SoundLoadWave("Resources/musicbox.wav");
	//SoundData soundData1 = SoundLoadWave("Resources/Alarm01.wav");


	////DirectX初期化処理　ここまで

	////DirectInput(入力)初期化処理
	KeyboardInput::Init(WindowsAPI::hwnd);


	////描画初期化処理　ここから

	//カメラ生成(制御)
	Camera nowCam({ 0,0,-100 });
	//プレイヤー（自機）生成
	Player player;




	//3Dオブジェクトの数
	//const int OBJECT_NUM = 2;
	//Object3D::Object object3ds[OBJECT_NUM];


	////頂点データ構造体
	//struct Vertex
	//{
	//	XMFLOAT3 pos; //xyz座標
	//	XMFLOAT3 normal; //法線ベクトル
	//	XMFLOAT2 uv; //uv座標
	//};

	////頂点データ
	//const int DIV = 3; //何角錐
	//const float radius = 10.0f; //半径の大きさ
	//const float topHeight = 15.0f; //天井の高さ
	//Vertex vertices[DIV + 1 + 1];
	//for (int i = 0; i < DIV; i++)
	//{
	//	vertices[i].pos.x = radius * sinf(2 * XM_PI / DIV * i);
	//	vertices[i].pos.y = radius * cosf(2 * XM_PI / DIV * i);
	//	vertices[i].pos.z = 0;
	//	vertices[i].uv = { 0.0f,1.0f };
	//};
	//vertices[DIV].pos = { 0,0,0 };
	//vertices[DIV].uv = { 1.0f,1.0f };
	//vertices[DIV + 1].pos = { 0,0,-topHeight };
	//vertices[DIV + 1].uv = { 1.0f,0.0f };

	////頂点インデックス
	//unsigned short indices[] = {
	//	1,0,3,
	//	2,1,3,
	//	0,2,3,

	//	0,1,4,
	//	1,2,4,
	//	2,0,4,
	//};



	////頂点データ全体のサイズ＝頂点データ1つ分のサイズ＊頂点データの要素数
	//UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * _countof(vertices));
	////インデックスデータ全体のサイズ
	//UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * _countof(indices));

	////頂点バッファの生成
	//ComPtr<ID3D12Resource> vertBuff;
	//result = dxCommon->GetDevice()->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //アップロード可能
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&vertBuff));

	////インデックスバッファの生成
	//ComPtr<ID3D12Resource> indexBuff;
	//result = dxCommon->GetDevice()->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //アップロード可能
	//	D3D12_HEAP_FLAG_NONE,
	//	&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
	//	D3D12_RESOURCE_STATE_GENERIC_READ,
	//	nullptr,
	//	IID_PPV_ARGS(&indexBuff));


	////法線ベクトルの計算
	//for (int i = 0; i < _countof(indices) / 3; i++)
	//{//三角形1つごとに計算していく
	//	//三角形のインデックスを取り出して一時的な変数に入れる
	//	unsigned short idx0 = indices[i * 3 + 0];
	//	unsigned short idx1 = indices[i * 3 + 1];
	//	unsigned short idx2 = indices[i * 3 + 2];

	//	//三角形を構成する頂点座標をベクトルに代入
	//	XMVECTOR p0 = XMLoadFloat3(&vertices[idx0].pos);
	//	XMVECTOR p1 = XMLoadFloat3(&vertices[idx1].pos);
	//	XMVECTOR p2 = XMLoadFloat3(&vertices[idx2].pos);

	//	//p0->p1ベクトル,p0->p2ベクトルを計算（ベクトルの減算）
	//	XMVECTOR v1 = XMVectorSubtract(p1, p0);
	//	XMVECTOR v2 = XMVectorSubtract(p2, p0);
	//	//外積は両方から垂直なベクトル
	//	XMVECTOR normal = XMVector3Cross(v1, v2);
	//	//正規化
	//	normal = XMVector3Normalize(normal);

	//	//求めた法線を頂点データに代入
	//	XMStoreFloat3(&vertices[idx0].normal, normal);
	//	XMStoreFloat3(&vertices[idx1].normal, normal);
	//	XMStoreFloat3(&vertices[idx2].normal, normal);
	//}


	////頂点バッファへのデータ転送
	//// GPU上のバッファに対応した仮想メモリを取得
	//Vertex* vertMap = nullptr;
	//result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	//// 全頂点に対して
	//for (int i = 0; i < _countof(vertices); i++)
	//{
	//	vertMap[i] = vertices[i];   // 座標をコピー
	//}
	//// マップを解除
	//vertBuff->Unmap(0, nullptr);

	////インデックスバッファへのデータ転送
	////GPU上のバッファに対応した仮想メモリを取得
	//unsigned short* indexMap = nullptr;
	//result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	////全インデックスに対して
	//for (int i = 0; i < _countof(indices); i++)
	//{
	//	indexMap[i] = indices[i];   //インデックスをコピー
	//}
	////繋がりを解除
	//indexBuff->Unmap(0, nullptr);


	////頂点バッファビューの作成
	//D3D12_VERTEX_BUFFER_VIEW vbView{};
	//vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	//vbView.SizeInBytes = sizeVB;
	//vbView.StrideInBytes = sizeof(Vertex);

	////インデックスバッファビューの作成
	//D3D12_INDEX_BUFFER_VIEW ibView{};
	//ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	//ibView.Format = DXGI_FORMAT_R16_UINT;
	//ibView.SizeInBytes = sizeIB;

	//3Dオブジェクト用パイプライン生成
	Object3D::Object objectCommon;
	objectCommon = Object3D::ObjectCommonCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height);
	//スプライト用パイプライン生成
	Object2D::SpriteCommon spriteCommon;
	spriteCommon = Object2D::SpriteCommonCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height);

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


	//配列内の全オブジェクトに対して
	//for (int i = 0; i < _countof(object3ds); i++)
	//{
	//	//初期化
	//	object3ds[i] = Object3D::ObjectCreate(i, dev.Get(),WindowsAPI::window_width,WindowsAPI::window_height, basicDescHeap.Get());
	//	object3ds[i].texNumber = 0;
	//	////以下は親子構造サンプル
	//	////先頭以外なら
	//	//if (i > 0)
	//	//{
	//	//	//1つ前のオブジェクトを親オブジェクトとする
	//	//	object3ds[i].parent = &object3ds[i - 1];
	//	//	//親オブジェクトの9割の大きさ
	//	//	object3ds[i].scale = { 0.9f,0.9f,0.9f };
	//	//	//親オブジェクトに対してZ軸まわりに30度回転
	//	//	object3ds[i].rotation = { 0,0,30.0f };
	//	//	//親オブジェクトに対してZ方向-8.0ずらす
	//	//	object3ds[i].position = { 0,0,-8.0f };
	//	//}
	//}

	//プレイヤー初期化
	player.Init(dxCommon->GetDevice(), 0, WindowsAPI::window_width, WindowsAPI::window_height, basicDescHeap.Get());



	//テクスチャ読み込み
	Object3D::ObjectCommonLoadTexture(objectCommon, 0, L"Resources/texture.png", dxCommon->GetDevice());

	//デスクリプタヒープの先頭ハンドルを取得
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV =
		CD3DX12_CPU_DESCRIPTOR_HANDLE(basicDescHeap->GetCPUDescriptorHandleForHeapStart(),
									  constantBufferNum,
									  dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV =
		CD3DX12_GPU_DESCRIPTOR_HANDLE(basicDescHeap->GetGPUDescriptorHandleForHeapStart(),
									  constantBufferNum,
									  dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

	//3つのビューのGPU側のアドレス記録
	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandle[3];
	for (int i = 0; i < 3; i++) {
		gpuDescHandle[i] = basicDescHeap->GetGPUDescriptorHandleForHeapStart();
		gpuDescHandle[i].ptr += i * dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	}


	////深度ビュー用デスクリプタヒープ作成
	//D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	//dsvHeapDesc.NumDescriptors = 1; //深度ビューは1つ
	//dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; //デプスステンシルビュー
	//ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//result = dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	////深度ビュー作成
	//D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	//dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; //深度値フォーマット
	//dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//dev->CreateDepthStencilView(
	//	depthBuffer.Get(),
	//	&dsvDesc,
	//	dsvHeap->GetCPUDescriptorHandleForHeapStart());


	//スプライト共通テクスチャ読み込み
	Object2D::SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/texture.png", dxCommon->GetDevice());
	Object2D::SpriteCommonLoadTexture(spriteCommon, 1, L"Resources/uni.png", dxCommon->GetDevice());


	//スプライト
	const int spriteNumber = 2;
	Object2D::Sprite sprite[spriteNumber];
	//スプライトの生成
	sprite[0] = Object2D::SpriteCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height, 0, spriteCommon);

	sprite[1] = Object2D::SpriteCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height, 1, spriteCommon);
	sprite[1].size = { 250,100 };
	sprite[1].position = { 1280 - sprite[1].size.x,0,0 };

	//サイズ変更を頂点バッファに反映
	for (int i = 0; i < spriteNumber; i++)
	{
		Object2D::SpriteTransferVertexBuffer(sprite[i]);
	}


	//デバッグテキスト
	DebugText debugText;

	//デバッグテキスト用のテクスチャ番号を指定
	const int debugTextTexNumber = 2;
	//デバッグテキスト用のテクスチャ読み込み
	Object2D::SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber, L"Resources/DebugText.png", dxCommon->GetDevice());
	//デバッグテキスト初期化
	debugText.Init(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height, debugTextTexNumber, spriteCommon);


	
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
		//キーボード入力更新
		KeyboardInput::Update();
		//キーが押されているときの処理例
		/*if (KeyboardInput::PressKeyTrigger(DIK_0))
		{
			OutputDebugStringA("Hit 0\n");
		}*/


		//音声再生例
		//SoundPlayWave(xAudio2.Get(),soundData1);
		if (KeyboardInput::PressKeyTrigger(DIK_M))
		{
			audio.SoundPlayWave(audio.xAudio2.Get(), soundData[0]);
		}
		//audio.SoundLoopPlayWave(audio.xAudio2.Get(), soundData[1]);
		/*if (KeyboardInput::PressKeyTrigger(DIK_N))
		{
			audio.SoundStop(audio.xAudio2.Get(), soundData[1]);
		}*/


		////頂点座標の変更
		//if (keyboard->PressKey(DIK_RIGHT) || keyboard->PressKey(DIK_LEFT)
		//	|| keyboard->PressKey(DIK_UP) || keyboard->PressKey(DIK_DOWN)
		//	|| keyboard->PressKey(DIK_O) || keyboard->PressKey(DIK_P))
		//{
		//	if (keyboard->PressKey(DIK_RIGHT)) { object3ds[0].position.x += 1.0f; }
		//	else if (keyboard->PressKey(DIK_LEFT)) { object3ds[0].position.x -= 1.0f; }
		//	if (keyboard->PressKey(DIK_UP)) { object3ds[0].position.y += 1.0f; }
		//	else if (keyboard->PressKey(DIK_DOWN)) { object3ds[0].position.y -= 1.0f; }
		//	if (keyboard->PressKey(DIK_O)) { object3ds[0].position.z += 1.0f; }
		//	else if (keyboard->PressKey(DIK_P)) { object3ds[0].position.z -= 1.0f; }
		//}

		//スプライト更新
		for (int i = 0; i < spriteNumber; i++)
		{
			Object2D::SpriteUpdate(sprite[i], spriteCommon);
		}

		////更新処理の呼び出し
		//for (int i = 0; i < _countof(object3ds); i++)
		//{
		//	Object3D::ObjectUpdate(object3ds[i], nowCam.matView, objectCommon);
		//}
		player.Update();
#pragma endregion
		

		//////４．描画コマンド　ここから

#pragma region 描画コマンド
		//描画前処理
		dxCommon->PreDraw();


		////描画コマンド
		//描画処理関数の呼び出し
		//player.Draw(dxCommon->GetDevice(), dxCommon->GetCommandList(), objectCommon, vbView, ibView, _countof(indices), nowCam.matView);


		////スプライト描画用

		//スプライト描画
		for (int i = 0; i < spriteNumber; i++)
		{
			Object2D::SpriteDraw(sprite[i], dxCommon->GetCommandList(), spriteCommon, dxCommon->GetDevice());
		}

		////デバッグテキスト表示
		//表示したい文字を入力
		debugText.PrintDebugText(spriteCommon, "I am goat.", 400, 100);
		debugText.PrintDebugText(spriteCommon, "I'm not egg.", 400, 150, 1.0f);
		//デバッグテキスト描画
		debugText.DrawAll(dxCommon->GetCommandList(), spriteCommon, dxCommon->GetDevice());


		//描画終了
		dxCommon->PostDraw();
#pragma endregion
		//////４．描画コマンド　ここまで


		////////////////DirectX毎フレーム処理 ここまで


	}
	//クラス(new)の消去
	//音声データ解放
	audio.SoundUnLoad(soundData);
	safe_delete(dxCommon);

	//ウィンドウクラスを登録解除
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	//コンソールへの文字出力
	OutputDebugStringA("Hello,DirectX!!\n");

	return 0;
}

