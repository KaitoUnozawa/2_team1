#pragma once
#include<DirectXTex.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>

using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")


class Object2D
{
public:  //メンバ変数、構造体
	//パイプラインセット構造体
	struct PipelineSet
	{
		//パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
		//ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
	};
	//スプライト用パイプライン生成
	static PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* dev);

	//スプライト1枚分のデータ
	struct Sprite
	{
		//頂点バッファ
		ComPtr<ID3D12Resource> vertBuff;
		//頂点バッファビュー
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		//定数バッファ
		ComPtr<ID3D12Resource> constBuff;

		//Z軸周りの回転角
		float rotation = 0.0f;
		//座標
		XMFLOAT3 position = { 0,0,0 };
		//ワールド行列
		XMMATRIX matWorld;
		//色 RGBA
		XMFLOAT4 color = { 1,1,1,1 };
		//使用するテクスチャの番号
		UINT texNumber = 0;
		//画像のサイズ(大きさ)
		XMFLOAT2 size = { 100,100 };
		//アンカーポイント
		XMFLOAT2 anchorpoint = { 0,0 };
		//左右反転
		bool isFlipX = false;
		//上下反転
		bool isFlipY = false;
		//非表示
		bool isInvisible = false;
		//テクスチャ左上座標
		XMFLOAT2 texLeftTop = { 0,0 };
		//テクスチャ切り出しサイズ
		XMFLOAT2 texSize = { 100,100 };
	};
	//スプライト共通データ
	static const int spriteSRVCount = 512; //テクスチャの最大枚数
	struct SpriteCommon
	{
		//パイプラインセット
		PipelineSet pipelineSet;
		//射影行列
		XMMATRIX matProjection{};

		//テクスチャ用デスクリプタヒープの生成
		ComPtr<ID3D12DescriptorHeap> descHeap;
		//テクスチャリソース（テクスチャバッファ）の生成
		ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	};

	//頂点構造体データ
	struct VertexPosUv
	{
		XMFLOAT3 pos; //xyz座標
		XMFLOAT2 uv; //uv座標
	};
	//定数バッファデータ構造体（送りたいデータが増えたらここに書く）
	struct ConstBufferData
	{
		XMFLOAT4 color; //色(RGBA)
		XMMATRIX mat; //3D変換行列
	};




	////スプライト生成用関数
    //スプライト共通データ生成
	static SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);
	//スプライト共通テクスチャ読み込み
	static void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);
	//スプライト用共通グラフィックスコマンド
	static void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	//スプライト単体頂点バッファの転送
	//通常
	static void SpriteTransferVertexBuffer(const Sprite& sprite);
	//テクスチャ切り出し
	static void SpriteTransferVertexBuffer(const Sprite& sprite, const SpriteCommon& spriteCommon);

	//スプライト生成初期化
	static Sprite SpriteCreate(ID3D12Device* dev, int window_width, int window_height, UINT texNumber,const SpriteCommon& spriteCommon, XMFLOAT2 anchorpoint = { 0,0 },bool isFlipX = false, bool isFlipY = false);
	//スプライト単体更新処理
	static void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);
	//スプライト単体描画コマンド
	static void SpriteDraw(const Sprite& sprite, ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon, ID3D12Device* dev);

};

