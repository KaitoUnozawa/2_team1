#include "Enemy.h"

void Enemy::Init(ID3D12Device * dev, int texNumber, int window_width, int window_height, ID3D12DescriptorHeap * descheap)
{
	//èâä˙âª(ê∂ê¨)

}

void Enemy::Update()
{
	//à⁄ìÆ
	enemy.position.y -= 0.5f;
}

void Enemy::Draw(ID3D12Device * dev, ID3D12GraphicsCommandList * cmdList, const Object3D::ObjectCommon & objectCommon, D3D12_VERTEX_BUFFER_VIEW & vbView, D3D12_INDEX_BUFFER_VIEW & ibView, UINT numIndices, const XMMATRIX & matView)
{
	//ï`âÊ
	Object3D::ObjectUpdate(enemy, matView, objectCommon);
	Object3D::Update();
	Object3D::ObjectDraw(enemy, objectCommon, dev, cmdList, vbView, ibView, numIndices);
}
