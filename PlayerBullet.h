#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "BulletModel.h"
#include <DirectXMath.h>

class PlayerBullet {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::Çè»ó™
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	PlayerBullet();
	~PlayerBullet();
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// ñàÉtÉåÅ[ÉÄèàóù
	/// </summary>
	void Update();

	/// <summary>
	/// ï`âÊ
	/// </summary>
	void Draw();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }
	void ShotInit(int posNumber, XMFLOAT3 startPos);
	bool GetIsAlive() { return isAlive; }
	

private:
	DirectXCommon* dxCommon = nullptr;
	BulletModel* bulletObj = nullptr;
	XMFLOAT3 position;
	XMFLOAT3 moveVector;
	bool isAlive;

};