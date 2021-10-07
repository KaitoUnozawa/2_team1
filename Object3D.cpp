#include "Object3D.h"

Object3D::PipelineSet Object3D::ObjectCreateGraphicsPipeline(ID3D12Device* dev)
{
	HRESULT result;

	//頂点シェーダファイルの読み込みとコンパイル
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob; // ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	// 頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/BasicVS.hlsl",  // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "vs_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&vsBlob, &errorBlob);

	//頂点シェーダのエラーを表示
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
					errorBlob->GetBufferSize(),
					errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}


	//ピクセルシェーダファイルの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/BasicPS.hlsl",   // シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // インクルード可能にする
		"main", "ps_5_0", // エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, // デバッグ用設定
		0,
		&psBlob, &errorBlob);

	//ピクセルシェーダのエラーを表示
	if (FAILED(result)) {
		// errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
					errorBlob->GetBufferSize(),
					errstr.begin());
		errstr += "\n";
		// エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());
		exit(1);
	}


	// 頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
			{ //xyz座標
				"POSITION", //セマンティック名
				0, //同じセマンティック名が複数ある時に使うインデックス(0でよい)
				DXGI_FORMAT_R32G32B32_FLOAT, //要素数とビット数
				0, //入力スロットインデックス(0でよい)
				D3D12_APPEND_ALIGNED_ELEMENT, //データのオフセット値
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, //入力データ種別
				0}, //xyz
			{ //法線ベクトル
				"NORMAL",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
			}, //法線ベクトル
			{ //uv座標
				"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
				D3D12_APPEND_ALIGNED_ELEMENT,
				D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,0
			}, //uv

	};


	// グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};

	//頂点シェーダ
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	//ピクセルシェーダ
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());
	//サンプルマスクとラスタライザステート（標準設定(背面カリング/塗りつぶし/深度クリッピング有効)）
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

	//頂点レイアウトの設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	//図形の形状を三角形に設定
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	//その他の設定
	gpipeline.NumRenderTargets = 1; // 描画対象は1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; // 0～255指定のRGBA
	gpipeline.SampleDesc.Count = 1; // 1ピクセルにつき1回サンプリング

	//ブレンドステートの設定
	//gpipeline.BlendState.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;  // RBGA全てのチャンネルを描画
	D3D12_RENDER_TARGET_BLEND_DESC& blenddesc = gpipeline.BlendState.RenderTarget[0];
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL; //標準設定

	//共通設定
	blenddesc.BlendEnable = true; //ブレンドを有効にする
	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD; //加算
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE; //ソース(新しい色)の値を100%使う
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO; //デスト(元ある色)の値を0%使う

	////加算合成（微妙に別物）
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD; //加算
	//blenddesc.SrcBlend = D3D12_BLEND_ONE; //ソースの値100%
	//blenddesc.DestBlend = D3D12_BLEND_ONE; //デストの値100%

	////減算合成
	//blenddesc.BlendOp = D3D12_BLEND_OP_REV_SUBTRACT; //デストからソースを減算
	//blenddesc.SrcBlend = D3D12_BLEND_ONE; //ソースの値100%
	//blenddesc.DestBlend = D3D12_BLEND_ONE; //デストの値100%

	////色反転
	//blenddesc.BlendOp = D3D12_BLEND_OP_ADD; //加算
	//blenddesc.SrcBlend = D3D12_BLEND_INV_DEST_COLOR; //1.0f - デストカラーの値
	//blenddesc.DestBlend = D3D12_BLEND_ZERO; //使わない

	//半透明合成
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD; //加算
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA; //ソースのアルファ値
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA; //1.0f - ソースのアルファ値

	//デプスステンシルステートの設定
	//標準設定（深度テストを行う/書き込み許可/深度が小さければ合格）
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT; //深度値フォーマット

	//デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); //t0レジスタ
	//ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[2];
	rootparams[0].InitAsConstantBufferView(0); //定数バッファビューとして初期化(b0レジスタ)
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV);

	//テクスチャサンプラー（スタティックサンプラー）
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0);

	//ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc,
							   D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	//パイプラインとルートシグネチャのセット
	PipelineSet pipelineSet;

	ComPtr<ID3DBlob> rootSigBlob;
	//バージョン自動判定でのシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0,
												   &rootSigBlob, &errorBlob);
	//ルートシグネチャの生成
	result = dev->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(),
									  IID_PPV_ARGS(&pipelineSet.rootsignature));

	// パイプラインにルートシグネチャをセット
	gpipeline.pRootSignature = pipelineSet.rootsignature.Get();

	result = dev->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineSet.pipelinestate));

	return pipelineSet;
}

Object3D::ObjectCommon Object3D::ObjectCommonCreate(ID3D12Device * dev, int window_width, int window_height)
{
	HRESULT result = S_FALSE;
	//新たなオブジェクト共通データを生成
	ObjectCommon objectCommon{};
	//オブジェクト用パイプライン生成
	objectCommon.pipelineSet = ObjectCreateGraphicsPipeline(dev);
	//透視投影変換
	objectCommon.matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		window_width / window_height,
		0.1f, 1000.0f
	);

	//デスクリプタヒープの生成
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	descHeapDesc.NumDescriptors = spriteSRVCount;
	result = dev->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&objectCommon.descHeap));

	return objectCommon;
}

void Object3D::ObjectCommonLoadTexture(ObjectCommon & objectCommon, UINT texnumber, const wchar_t * filename, ID3D12Device * dev)
{
	assert(texnumber <= spriteSRVCount - 1);
	HRESULT result;

	//テクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};
	result = LoadFromWICFile(
		filename,
		WIC_FLAGS_NONE,
		&metadata, scratchImg);
	const Image *img = scratchImg.GetImage(0, 0, 0);

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc =
		CD3DX12_RESOURCE_DESC::Tex2D(
			metadata.format,
			metadata.width,
			(UINT)metadata.height,
			(UINT16)metadata.arraySize,
			(UINT16)metadata.mipLevels);

	// テクスチャバッファ生成
	result = dev->CreateCommittedResource(	//GPUリソースの生成
										  &CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0),
										  D3D12_HEAP_FLAG_NONE,
										  &texresDesc,
										  D3D12_RESOURCE_STATE_GENERIC_READ,	//テクスチャ用指定
										  nullptr,
										  IID_PPV_ARGS(&objectCommon.texBuff[texnumber]));

	// テクスチャバッファへのデータ転送
	result = objectCommon.texBuff[texnumber]->WriteToSubresource(
		0,
		nullptr,	//全領域へコピー
		img->pixels,	//元データアドレス
		(UINT)img->rowPitch,	//1ラインサイズ
		(UINT)img->slicePitch	//全サイズ
	);


	//シェーダリソースビュー設定
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};	//設定構造体
	srvDesc.Format = metadata.format;	//RGBA
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;	//2Dテクスチャ
	srvDesc.Texture1D.MipLevels = 1;

	//シェーダーリソースビュー作成
	dev->CreateShaderResourceView(
		objectCommon.texBuff[texnumber].Get(),	//ビューと関連付けるバッファ
		&srvDesc,	//テクスチャ設定情報
		CD3DX12_CPU_DESCRIPTOR_HANDLE(objectCommon.descHeap->GetCPUDescriptorHandleForHeapStart(), texnumber, dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV))
	);
}

void Object3D::ObjectCommonBeginDraw(ID3D12GraphicsCommandList * cmdList, const ObjectCommon & objectCommon)
{
	//パイプラインステートの設定
	cmdList->SetPipelineState(objectCommon.pipelineSet.pipelinestate.Get());
	//ルートシグネチャの設定
	cmdList->SetGraphicsRootSignature(objectCommon.pipelineSet.rootsignature.Get());
	//トポロジー
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//テクスチャ用デスクリプタヒープの設定
	ID3D12DescriptorHeap *ppHeaps[] = { objectCommon.descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
}

Object3D::Object Object3D::ObjectCreate(int index, ID3D12Device* dev, int window_width, int window_height, ID3D12DescriptorHeap* descHeap)
{
	HRESULT result;

	Object object;

	//定数バッファの生成
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&object.constBuff));

	//デスクリプタ1つ分のサイズ
	UINT descHandleIncrementSize = dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	//CBVのCPUデスクリプタハンドルを計算
	object.cpuDescHandleCBV = CD3DX12_CPU_DESCRIPTOR_HANDLE(
		descHeap->GetCPUDescriptorHandleForHeapStart(), index, descHandleIncrementSize);
	//CBVのGPUデスクリプタハンドルを計算
	object.gpuDescHandleCBV = CD3DX12_GPU_DESCRIPTOR_HANDLE(
		descHeap->GetGPUDescriptorHandleForHeapStart(), index, descHandleIncrementSize);

	//定数バッファビューの作成
	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc{};
	cbvDesc.BufferLocation = object.constBuff->GetGPUVirtualAddress();
	cbvDesc.SizeInBytes = (UINT)object.constBuff->GetDesc().Width;
	dev->CreateConstantBufferView(&cbvDesc, object.cpuDescHandleCBV);

	//定数バッファ
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(Object3D::ConstBufferData)),
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&object.constBuff)
	);

	//定数バッファにデータを転送
	ConstBufferData *constMap = nullptr;
	result = object.constBuff->Map(0, nullptr, (void **)&constMap);
	constMap->color = XMFLOAT4(1, 1, 1, 1);
	//平衡投影行列
	constMap->mat = XMMatrixOrthographicOffCenterLH(
		0.0f, window_width, window_height, 0.0f, 0.0f, 1.0f
	);
	object.constBuff->Unmap(0, nullptr);

	return object;
}

void Object3D::ObjectUpdate(Object& object, const XMMATRIX& matView, const ObjectCommon& objectCommon)
{
	XMMATRIX matScale, matRot, matTrans;

	//スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(object.scale.x, object.scale.y, object.scale.z); //スケーリング

	matRot = XMMatrixIdentity(); //回転行列
	matRot *= XMMatrixRotationZ(XMConvertToRadians(object.rotation.z)); //Z軸周りに回転
	matRot *= XMMatrixRotationX(XMConvertToRadians(object.rotation.x)); //X軸周りに回転
	matRot *= XMMatrixRotationY(XMConvertToRadians(object.rotation.y)); //Y軸周りに回転

	matTrans = XMMatrixTranslation(object.position.x, object.position.y, object.position.z); //平行移動

	//ワールド行列の合成
	object.matWorld = XMMatrixIdentity(); //単位行列
	object.matWorld *= matScale; //ワールド座標にスケーリングを反映
	object.matWorld *= matRot; //ワールド行列に回転を反映
	object.matWorld *= matTrans; //ワールド行列に平行移動を反映

	//親オブジェクトがあれば
	if (object.parent != nullptr)
	{
		//親オブジェクトのワールド行列を掛ける
		object.matWorld *= object.parent->matWorld;
	}

	//定数バッファへデータ転送
	ConstBufferData* constMap = nullptr;
	if (SUCCEEDED(object.constBuff->Map(0, nullptr, (void**)&constMap)))
	{
		constMap->color = XMFLOAT4(1, 1, 1, 1.0f);
		constMap->mat = object.matWorld * matView * objectCommon.matProjection;
		object.constBuff->Unmap(0, nullptr);
	}
}

void Object3D::ObjectDraw(const Object &object, const ObjectCommon &objectCommon, ID3D12Device *dev, ID3D12GraphicsCommandList* cmdList, D3D12_VERTEX_BUFFER_VIEW& vbView, D3D12_INDEX_BUFFER_VIEW& ibView, UINT numIndices)
{
	//オブジェクト用共通グラフィックスコマンド
	Object3D::ObjectCommonBeginDraw(cmdList, objectCommon);
	//頂点バッファの生成
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	//インデックスバッファの設定
	cmdList->IASetIndexBuffer(&ibView);
	//定数バッファビューをセット
	cmdList->SetGraphicsRootConstantBufferView(0, object.constBuff->GetGPUVirtualAddress());
	//シェーダーリソースビューをセット
	cmdList->SetGraphicsRootDescriptorTable(1, 
											CD3DX12_GPU_DESCRIPTOR_HANDLE(
												objectCommon.descHeap->GetGPUDescriptorHandleForHeapStart(),
												object.texNumber,
												dev->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)
											));
	//描画コマンド
	cmdList->DrawIndexedInstanced(numIndices, 1, 0, 0, 0);
}
