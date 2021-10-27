#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include"BulletObject2.h"
#include <DirectXMath.h>
class Bullet2 {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Bullet2();
	~Bullet2();
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }


private:
	DirectXCommon* dxCommon = nullptr;


	BulletObject2* Bulletobj2 = nullptr;


	//プレイヤーのスピード


	XMFLOAT3 position;

};