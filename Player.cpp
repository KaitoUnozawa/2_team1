#include "Player.h"

void Player::Init(ID3D12Device * dev, int texNumber, int window_width, int window_height, ID3D12DescriptorHeap * descheap)
{
	//èâä˙âª(ê∂ê¨)
	player = Object3D::ObjectCreate(0, dev, window_width, window_height, descheap);
	player.texNumber = texNumber;
	player.position = { 0.0f,0.0f,0.0f };
	player.scale = { 1.0f,1.0f,1.0f };
	//player.rotation.x = 90.0f;
	HP = 3;
}

void Player::Update()
{

	//à⁄ìÆ
	if (KeyboardInput::PressKey(DIK_D) || KeyboardInput::PressKey(DIK_RIGHT))
	{
		player.position.x += 1.0f;
	}
	if (KeyboardInput::PressKey(DIK_A) || KeyboardInput::PressKey(DIK_LEFT))
	{
		player.position.x -= 1.0f;
	}
	if (KeyboardInput::PressKey(DIK_W) || KeyboardInput::PressKey(DIK_UP))
	{
		player.position.y += 1.0f;
	}
	if (KeyboardInput::PressKey(DIK_S) || KeyboardInput::PressKey(DIK_DOWN))
	{
		player.position.y -= 1.0f;
	}
}

void Player::Draw(ID3D12Device * dev, ID3D12GraphicsCommandList * cmdList, const Object3D::ObjectCommon & objectCommon, D3D12_VERTEX_BUFFER_VIEW & vbView, D3D12_INDEX_BUFFER_VIEW & ibView, UINT numIndices, const XMMATRIX & matView)
{
	Object3D::ObjectUpdate(player, matView, objectCommon);
	Object3D::ObjectDraw(player, objectCommon, dev, cmdList, vbView, ibView, numIndices);
}
