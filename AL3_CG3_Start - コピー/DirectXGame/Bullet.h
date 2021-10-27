#pragma once
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include"BulletObject.h"
#include <DirectXMath.h>
class Bullet {
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	Bullet();
	~Bullet();
	void Initialize(DirectXCommon* dxCommon);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();
	const XMFLOAT3& GetPosition() { return position; }
	void SetPosition(XMFLOAT3 position) { this->position = position; }


private:
	DirectXCommon* dxCommon = nullptr;

	BulletObject* Bulletobj = nullptr;

	XMFLOAT3 position;

};