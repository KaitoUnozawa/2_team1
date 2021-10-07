#pragma once
#include<DirectXTex.h>
#include<wrl.h>

#include<d3d12.h>
#include<d3dx12.h>

#include<DirectXMath.h>

#include<d3dcompiler.h>

using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")


class Object3D
{
public:
	//パイプラインセット構造体
	struct PipelineSet
	{
		//パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
		//ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
	};
	//3Dオブジェクト用パイプライン生成
	static PipelineSet ObjectCreateGraphicsPipeline(ID3D12Device* dev);

	//3Dオブジェクト型
	struct Object
	{
		//頂点バッファ
		ComPtr<ID3D12Resource> vertBuff;
		//頂点バッファビュー
		D3D12_VERTEX_BUFFER_VIEW vbView{};

		//定数バッファ
		ComPtr<ID3D12Resource> constBuff;
		//定数バッファビューのハンドル(CPU)
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleCBV;
		//定数バッファビューのハンドル(GPU)
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleCBV;

		//アフィン変換情報
		XMFLOAT3 scale = { 1,1,1 };
		XMFLOAT3 rotation = { 90,0,0 };
		XMFLOAT3 position = { 0,0,0 };
		//ワールド変換座標
		XMMATRIX matWorld;
		//色 RGBA
		XMFLOAT4 color = { 1,1,1,1 };

		//親オブジェクトへのポインタ
		Object* parent = nullptr;

		//テクスチャ番号
		UINT texNumber = 0;
	};
	//3Dオブジェクト共通データ
	static const int spriteSRVCount = 512; //テクスチャの最大枚数
	struct ObjectCommon
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

	//定数バッファデータ構造体（送りたいデータが増えたらここに書く）
	struct ConstBufferData
	{
		XMFLOAT4 color; //色(RGBA)
		XMMATRIX mat; //3D変換行列
	};


	////3Dオブジェクト生成用関数
	 //スプライト共通データ生成
	static ObjectCommon ObjectCommonCreate(ID3D12Device* dev, int window_width, int window_height);
	//スプライト共通テクスチャ読み込み
	static void ObjectCommonLoadTexture(ObjectCommon& objectCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);
	//スプライト用共通グラフィックスコマンド
	static void ObjectCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const ObjectCommon& objectCommon);


	//3Dオブジェクト初期化
	static Object ObjectCreate(int index, ID3D12Device* dev, int window_width, int window_height, ID3D12DescriptorHeap* descHeap);
	//オブジェクト更新処理
	static void ObjectUpdate(Object& object, const XMMATRIX& matView, const ObjectCommon& objectCommon);
	//オブジェクト描画処理
	static void ObjectDraw(const Object &object, const ObjectCommon &objectCommon, ID3D12Device *dev, ID3D12GraphicsCommandList* cmdList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices);


};

