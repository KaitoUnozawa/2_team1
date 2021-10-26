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

#include"WindowsAPI.h"  //�E�B���h�E�\��
#include"KeyboardInput.h"  //�L�[�{�[�h����
#include"Object2D.h"  //2D�摜(sprite)
#include"Object3D.h"  //3D�I�u�W�F�N�g(Object)
#include"Audio.h" //���y�Đ�
#include"DebugText.h" //�f�o�b�O�e�L�X�g
#include"DirectXCommon.h"
#include"SafeDelete.h"
#include"GameScene.h"
#include"ModelObj.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xaudio2.lib")


using namespace DirectX;
using namespace Microsoft::WRL;


//Windows�A�v���ł̃G���g���[�|�C���g�imain�֐��j
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//�E�B���h�E
	WindowsAPI* win = nullptr;
	win = new WindowsAPI();
	win->WindowCreate();

	MSG msg{}; //���b�Z�[�W



#ifdef _DEBUG
	//�f�o�b�O���C���[���I����
	ComPtr<ID3D12Debug> debugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
	{
		debugController->EnableDebugLayer();
	}
#endif // _DEBUG


	////DirectX�����������@��������
	HRESULT result;
		

	//DirectX�ėp����
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);


	//������
	Audio* audio = nullptr;
	audio = new Audio();
	audio->Init();
	////�����ǂݍ���
	
	

	
	////DirectInput(����)����������
	KeyboardInput* input = nullptr;
	input = new KeyboardInput();
	input->Init(win->hwnd);


	////DirectX�����������@�����܂�

	


	////�`�揉���������@��������
	
	// �X�v���C�g�ÓI������
	if (!Object2D::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// 3D�I�u�W�F�N�g�ÓI������
	if (!Object3D::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	// 3D���f���ÓI������
	if (!ModelObj::StaticInit(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height)) {
		assert(0);
		return 1;
	}

	//�萔�o�b�t�@�ւ̃f�[�^�]���i�������j
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f), //�㉺��p60�x
		(float)WindowsAPI::window_width / WindowsAPI::window_height, //�A�X�y�N�g��
		0.1f, 1000.0f);//��O�C��

	//�萔�o�b�t�@�E�e�N�X�`���o�b�t�@�p�̃f�X�N���v�^�q�[�v
	const int constantBufferNum = 128; //�萔�o�b�t�@�̍ő吔
	ComPtr<ID3D12DescriptorHeap> basicDescHeap;
	//���\����
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc{};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; //�V�F�[�_�[���猩����
	descHeapDesc.NumDescriptors = constantBufferNum + 1; //�萔�o�b�t�@�̐�(+1->SRV)


	//�f�X�N���v�^�q�[�v�̐���
	result = dxCommon->GetDevice()->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&basicDescHeap));
	

	//�f�o�b�O�e�L�X�g
	DebugText debugText;

	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 2;
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	Object2D::LoadTexture(debugTextTexNumber, L"Resources/DebugText.png");
	//�f�o�b�O�e�L�X�g������
	debugText.Init(debugTextTexNumber);

	// �Q�[���V�[���̏�����
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Init(dxCommon, input, audio);
	
	////�`�揉���������@�����܂�



	while (true) //�Q�[�����[�v
	{
		//���b�Z�[�W�����邩
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); //�L�[���̓��b�Z�[�W�̏���
			DispatchMessage(&msg); //�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
		}

		//�~�{�^���ŏI�����b�Z�[�W��������Q�[�����[�v�𔲂���
		if (msg.message == WM_QUIT)
		{
			break;
		}


		////////////////DirectX���t���[������ ��������

#pragma region �X�V����
		input->Update();
		gameScene->Update();

		

#pragma endregion
		

		//////�S�D�`��R�}���h�@��������

#pragma region �`��R�}���h
		//�`��O����
		dxCommon->PreDraw();

		gameScene->Draw();

		//�`��I��
		dxCommon->PostDraw();
#pragma endregion
		//////�S�D�`��R�}���h�@�����܂�


		////////////////DirectX���t���[������ �����܂�
	}
	//�N���X(new)�̏���
	//�����f�[�^���
	
	safe_delete(dxCommon);
	safe_delete(audio);
	safe_delete(input);
	safe_delete(gameScene);

	//�E�B���h�E�N���X��o�^����
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello,DirectX!!\n");

	return 0;
}

