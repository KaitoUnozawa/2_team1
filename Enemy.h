#pragma once
#include<DirectXMath.h>

#include"Object3D.h"


using namespace DirectX;


class Enemy
{
public:
	Object3D::Object enemy; //“G‹@
	int HP; //‘Ì—Í


	void Init(ID3D12Device *dev, int texNumber, int window_width, int window_height, ID3D12DescriptorHeap *descheap);
	void Update();
	void Draw(ID3D12Device *dev, ID3D12GraphicsCommandList *cmdList, const Object3D::ObjectCommon &objectCommon,
			  D3D12_VERTEX_BUFFER_VIEW &vbView, D3D12_INDEX_BUFFER_VIEW &ibView, UINT numIndices, const XMMATRIX &matView);

};

