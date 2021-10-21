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
#include"Camera.h" //�J��������
#include"Player.h" //�v���C���[
#include"Audio.h" //���y�Đ�
#include"DebugText.h" //�f�o�b�O�e�L�X�g
#include"DirectXCommon.h"
#include"SafeDelete.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xaudio2.lib")


using namespace DirectX;
using namespace Microsoft::WRL;

//////�I�[�f�B�I
////�`�����N�w�b�_
//struct ChunkHeader
//{
//	char id[4]; //�`�����N����ID
//	int32_t size; //�`�����N�T�C�Y
//};
//
////RIFF�w�b�_�`�����N
//struct RiffHeader
//{
//	ChunkHeader chunk; //"RIFF"
//	char type[4]; //"WAVE"
//};
//
////FMT�`�����N
//struct FormatChunk
//{
//	ChunkHeader chunk; //"fmt"
//	WAVEFORMATEX fmt; //�g�`�t�H�[�}�b�g
//};
//
////�����f�[�^
//struct SoundData
//{
//	//�g�`�t�H�[�}�b�g
//	WAVEFORMATEX wfex;
//	//�o�b�t�@�̐擪�A�h���X
//	BYTE* pBuffer;
//	//�o�b�t�@�̃T�C�Y
//	unsigned int bufferSize;
//};
//
//
////�����f�[�^�ǂݍ��݊֐�
//SoundData SoundLoadWave(const char* filename)
//{
//	HRESULT result;
//
//	////�t�@�C���I�[�v��
//	//�t�@�C�����̓X�g���[���̃C���X�^���X
//	std::ifstream file;
//	//wav�t�@�C�����o�C�i�����[�h�ŊJ��
//	file.open(filename, std::ios_base::binary);
//	//�t�@�C���I�[�v�����s�����o����
//	assert(file.is_open());
//
//
//	////wav�f�[�^�ǂݍ���
//	//RIFF�w�b�_�[�̓ǂݍ���
//	RiffHeader riff;
//	file.read((char*)&riff, sizeof(riff));
//	//�t�@�C����RIFF���`�F�b�N
//	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
//		assert(0);
//	}
//	//�^�C�v��WAVE���`�F�b�N
//	if (strncmp(riff.type, "WAVE", 4) != 0) {
//		assert(0);
//	}
//	//Format�`�����N�̓ǂݍ���
//	FormatChunk format = {};
//	//�`�����N�w�b�_�[�̊m�F
//	file.read((char*)&format, sizeof(ChunkHeader));
//	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
//		assert(0);
//	}
//
//	//�`�����N�{�̂̓ǂݍ���
//	assert(format.chunk.size <= sizeof(format.fmt));
//	file.read((char*)&format.fmt, format.chunk.size);
//	//Data�`�����N�̓ǂݍ���
//	ChunkHeader data;
//	file.read((char*)&data, sizeof(data));
//	//JUNK�`�����N�����o�����ꍇ
//	if (strncmp(data.id, "JUNK", 4) == 0) {
//		//�ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
//		file.seekg(data.size, std::ios_base::cur);
//		//�ēǂݍ���
//		file.read((char*)&data, sizeof(data));
//	}
//	if (strncmp(data.id, "data", 4) != 0) {
//		assert(0);
//	}
//
//	//Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
//	char* pBuffer = new char[data.size];
//	file.read(pBuffer, data.size);
//
//	//Wave�t�@�C�������
//	file.close();
//
//
//	//�ǂݍ��񂾉����f�[�^��return����
//	SoundData soundData = {};
//
//	soundData.wfex = format.fmt;
//	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
//	soundData.bufferSize = data.size;
//
//	return soundData;
//}
//
////�����f�[�^����֐�
//void SoundUnLoad(SoundData* soundData)
//{
//	//�o�b�t�@�̃����������
//	delete[] soundData->pBuffer;
//
//	soundData->pBuffer = 0;
//	soundData->bufferSize = 0;
//	soundData->wfex = {};
//}
//
////�����Đ��֐�
//void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData)
//{
//	HRESULT result;
//
//	//�g�`�t�H�[�}�b�g������SourceVoice�̐���
//	IXAudio2SourceVoice* pSourceVoice = nullptr;
//	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
//	assert(SUCCEEDED(result));
//
//	//�Đ�����g�`�f�[�^�̐ݒ�
//	XAUDIO2_BUFFER buf{};
//	buf.pAudioData = soundData.pBuffer;
//	buf.AudioBytes = soundData.bufferSize;
//	buf.Flags = XAUDIO2_END_OF_STREAM;
//
//	//�g�`�f�[�^�̍Đ�
//	result = pSourceVoice->SubmitSourceBuffer(&buf);
//	result = pSourceVoice->Start();
//}


//�E�B���h�E�v���V�[�W��
LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//���b�Z�[�W�ŕ���
	switch (msg)
	{
		case WM_DESTROY: //�E�B���h�E���j�����ꂽ
			PostQuitMessage(0); //OS�ɑ΂��āA�A�v���̏I����`����
			return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam); //�W���̏������s��
}


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
	/*ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;*/

	

	//DirectX�ėp����
	DirectXCommon* dxCommon = nullptr;
	dxCommon = new DirectXCommon();
	dxCommon->Init(win);

	////DXGI�t�@�N�g���[�̐���
	//result = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	////�A�_�v�^�[�̗񋓗p
	//std::vector<ComPtr<IDXGIAdapter1>> adapters;
	////�����ɓ���̖��O�����A�_�v�^�[�I�u�W�F�N�g������
	//ComPtr<IDXGIAdapter1> tmpAdapter;
	//for (int i = 0;
	//	 dxgiFactory->EnumAdapters1(i, &tmpAdapter) !=
	//	 DXGI_ERROR_NOT_FOUND;
	//	 i++)
	//{
	//	adapters.push_back(tmpAdapter); //���I�z��ɒǉ�����
	//}
	//for (int i = 0; i < adapters.size(); i++)
	//{
	//	DXGI_ADAPTER_DESC1 adesc;
	//	adapters[i]->GetDesc1(&adesc); //�A�_�v�^�[�̏����擾
	//	//�\�t�g�E�F�A�f�o�C�X�����
	//	if (adesc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
	//	{
	//		continue;
	//	}
	//	std::wstring strDesc = adesc.Description; //�A�_�v�^�[��
	//	//Intel UHD Graphics�i�I���{�[�h�O���t�B�b�N�j�����
	//	if (strDesc.find(L"Intel") == std::wstring::npos)
	//	{
	//		tmpAdapter = adapters[i]; //�̗p
	//		break;
	//	}
	//}
	////�Ή����x���̔z��
	//D3D_FEATURE_LEVEL levels[] =
	//{
	//	D3D_FEATURE_LEVEL_12_1,
	//	D3D_FEATURE_LEVEL_12_0,
	//	D3D_FEATURE_LEVEL_11_1,
	//	D3D_FEATURE_LEVEL_11_0
	//};
	//D3D_FEATURE_LEVEL featureLevel;
	//for (int i = 0; i < _countof(levels); i++)
	//{
	//	//�̗p�����A�_�v�^�[�Ńf�o�C�X�𐶐�
	//	result = D3D12CreateDevice(tmpAdapter.Get(), levels[i], IID_PPV_ARGS(&dev));
	//	if (result == S_OK)
	//	{
	//		//�f�o�C�X�𐶐��ł������_�Ń��[�v�𔲂���
	//		featureLevel = levels[i];
	//		break;
	//	}
	//}
	////�R�}���h�A���P�[�^�𐶐�
	//result = dev->CreateCommandAllocator(
	//	D3D12_COMMAND_LIST_TYPE_DIRECT,
	//	IID_PPV_ARGS(&cmdAllocator));
	////�R�}���h���X�g�𐶐�
	//result = dev->CreateCommandList(0,
	//								D3D12_COMMAND_LIST_TYPE_DIRECT,
	//								cmdAllocator.Get(), nullptr,
	//								IID_PPV_ARGS(&cmdList));
	////�W���ݒ�ŃR�}���h�L���[�𐶐�
	//D3D12_COMMAND_QUEUE_DESC cmdQueueDesc{};
	//dev->CreateCommandQueue(&cmdQueueDesc, IID_PPV_ARGS(&cmdQueue));
	////�e��ݒ�����ăX���b�v�`�F�[���𐶐�
	//DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
	//swapchainDesc.Width = 1280;
	//swapchainDesc.Height = 720;
	//swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //�F���̏���
	//swapchainDesc.SampleDesc.Count = 1; //�}���`�T���v�����Ȃ�
	//swapchainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER; //�o�b�N�o�b�t�@�p
	//swapchainDesc.BufferCount = 2; //�o�b�t�@����2�ɐݒ�
	//swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD; //�t���b�v��͔j��
	//swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	////IDXGISwapChain1��ComPtr��p��
	//ComPtr<IDXGISwapChain1> swapchain1;
	////�X���b�v�`�F�[���̐���
	//dxgiFactory->CreateSwapChainForHwnd(
	//	cmdQueue.Get(),
	//	WindowsAPI::hwnd,
	//	&swapchainDesc,
	//	nullptr,
	//	nullptr,
	//	&swapchain1);
	////��������IDXGISwapChain1�̃I�u�W�F�N�g��IDXGISwapChain4�ɕϊ�����
	//swapchain1.As(&swapchain);
	////�e��ݒ�����ăf�X�N���v�^�q�[�v�𐶐�
	//D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	//heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; //�����_�[�^�[�Q�b�g�r���[
	//heapDesc.NumDescriptors = 2; //���\��2��
	//dev->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&rtvHeaps));
	////���\��2���ɂ���
	//std::vector<ComPtr<ID3D12Resource>> backBuffers(2);
	//for (int i = 0; i < 2; i++)
	//{
	//	//�X���b�v�`�F�[������o�b�t�@���擾
	//	result = swapchain->GetBuffer(i, IID_PPV_ARGS(&backBuffers[i]));
	//	//�����_�[�^�[�Q�b�g�r���[�̐���
	//	dev->CreateRenderTargetView(
	//		backBuffers[i].Get(),
	//		nullptr,
	//		CD3DX12_CPU_DESCRIPTOR_HANDLE(
	//			rtvHeaps->GetCPUDescriptorHandleForHeapStart(), //�q�[�v�̐擪�A�h���X
	//			i, //�f�X�N���v�^�̔ԍ�
	//			dev->GetDescriptorHandleIncrementSize(heapDesc.Type) //�f�X�N���v�^1���̃T�C�Y
	//		));
	//
	//////�[�x�o�b�t�@���\�[�X�̐���
	//ComPtr<ID3D12Resource> depthBuffer;
	////�[�x�o�b�t�@���\�[�X�ݒ�
	//CD3DX12_RESOURCE_DESC depthResDesc = CD3DX12_RESOURCE_DESC::Tex2D(
	//	DXGI_FORMAT_D32_FLOAT,
	//	WindowsAPI::window_width,
	//	WindowsAPI::window_height,
	//	1, 0,
	//	1, 0,
	//	D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);
	////�[�x�o�b�t�@�̐���
	//result = dev->CreateCommittedResource(
	//	&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
	//	D3D12_HEAP_FLAG_NONE,
	//	&depthResDesc,
	//	D3D12_RESOURCE_STATE_DEPTH_WRITE, //�[�x�l�������݂Ɏg�p
	//	&CD3DX12_CLEAR_VALUE(DXGI_FORMAT_D32_FLOAT,1.0f,0),
	//	IID_PPV_ARGS(&depthBuffer));
	////�t�F���X�̐���
	//ComPtr<ID3D12Fence> fence;
	//UINT64 fenceVal = 0;
	//result = dev->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));


	//�T�E���h�Đ�
	//ComPtr<IXAudio2> xAudio2;
	//IXAudio2MasteringVoice* masterVoice;
	//XAudio�G���W���̃C���X�^���X�𐶐�
	//result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	//�}�X�^�[�{�C�X�𐶐�
	//result = xAudio2->CreateMasteringVoice(&masterVoice);

	//������
	Audio audio;
	audio.Init();
	////�����ǂݍ���
	Audio::SoundData soundData[2];
	soundData[0] = audio.SoundLoadWave("Resources/Alarm01.wav");
	soundData[1] = audio.SoundLoadWave("Resources/musicbox.wav");
	//SoundData soundData1 = SoundLoadWave("Resources/Alarm01.wav");


	////DirectX�����������@�����܂�

	////DirectInput(����)����������
	KeyboardInput::Init(WindowsAPI::hwnd);


	////�`�揉���������@��������

	//�J��������(����)
	Camera nowCam({ 0,0,-100 });
	//�v���C���[�i���@�j����
	Player player;




	//3D�I�u�W�F�N�g�̐�
	//const int OBJECT_NUM = 2;
	//Object3D::Object object3ds[OBJECT_NUM];


	//���_�f�[�^�\����
	struct Vertex
	{
		XMFLOAT3 pos; //xyz���W
		XMFLOAT3 normal; //�@���x�N�g��
		XMFLOAT2 uv; //uv���W
	};

	//���_�f�[�^
	const int DIV = 3; //���p��
	const float radius = 10.0f; //���a�̑傫��
	const float topHeight = 15.0f; //�V��̍���
	Vertex vertices[DIV + 1 + 1];
	for (int i = 0; i < DIV; i++)
	{
		vertices[i].pos.x = radius * sinf(2 * XM_PI / DIV * i);
		vertices[i].pos.y = radius * cosf(2 * XM_PI / DIV * i);
		vertices[i].pos.z = 0;
		vertices[i].uv = { 0.0f,1.0f };
	};
	vertices[DIV].pos = { 0,0,0 };
	vertices[DIV].uv = { 1.0f,1.0f };
	vertices[DIV + 1].pos = { 0,0,-topHeight };
	vertices[DIV + 1].uv = { 1.0f,0.0f };

	//���_�C���f�b�N�X
	unsigned short indices[] = {
		1,0,3,
		2,1,3,
		0,2,3,

		0,1,4,
		1,2,4,
		2,0,4,
	};



	//���_�f�[�^�S�̂̃T�C�Y�����_�f�[�^1���̃T�C�Y�����_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(sizeof(Vertex) * _countof(vertices));
	//�C���f�b�N�X�f�[�^�S�̂̃T�C�Y
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * _countof(indices));

	//���_�o�b�t�@�̐���
	ComPtr<ID3D12Resource> vertBuff;
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));

	//�C���f�b�N�X�o�b�t�@�̐���
	ComPtr<ID3D12Resource> indexBuff;
	result = dxCommon->GetDevice()->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), //�A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));


	//�@���x�N�g���̌v�Z
	for (int i = 0; i < _countof(indices) / 3; i++)
	{//�O�p�`1���ƂɌv�Z���Ă���
		//�O�p�`�̃C���f�b�N�X�����o���Ĉꎞ�I�ȕϐ��ɓ����
		unsigned short idx0 = indices[i * 3 + 0];
		unsigned short idx1 = indices[i * 3 + 1];
		unsigned short idx2 = indices[i * 3 + 2];

		//�O�p�`���\�����钸�_���W���x�N�g���ɑ��
		XMVECTOR p0 = XMLoadFloat3(&vertices[idx0].pos);
		XMVECTOR p1 = XMLoadFloat3(&vertices[idx1].pos);
		XMVECTOR p2 = XMLoadFloat3(&vertices[idx2].pos);

		//p0->p1�x�N�g��,p0->p2�x�N�g�����v�Z�i�x�N�g���̌��Z�j
		XMVECTOR v1 = XMVectorSubtract(p1, p0);
		XMVECTOR v2 = XMVectorSubtract(p2, p0);
		//�O�ς͗������琂���ȃx�N�g��
		XMVECTOR normal = XMVector3Cross(v1, v2);
		//���K��
		normal = XMVector3Normalize(normal);

		//���߂��@���𒸓_�f�[�^�ɑ��
		XMStoreFloat3(&vertices[idx0].normal, normal);
		XMStoreFloat3(&vertices[idx1].normal, normal);
		XMStoreFloat3(&vertices[idx2].normal, normal);
	}


	//���_�o�b�t�@�ւ̃f�[�^�]��
	// GPU��̃o�b�t�@�ɑΉ��������z���������擾
	Vertex* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	// �S���_�ɑ΂���
	for (int i = 0; i < _countof(vertices); i++)
	{
		vertMap[i] = vertices[i];   // ���W���R�s�[
	}
	// �}�b�v������
	vertBuff->Unmap(0, nullptr);

	//�C���f�b�N�X�o�b�t�@�ւ̃f�[�^�]��
	//GPU��̃o�b�t�@�ɑΉ��������z���������擾
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	//�S�C���f�b�N�X�ɑ΂���
	for (int i = 0; i < _countof(indices); i++)
	{
		indexMap[i] = indices[i];   //�C���f�b�N�X���R�s�[
	}
	//�q���������
	indexBuff->Unmap(0, nullptr);


	//���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(Vertex);

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;

	//3D�I�u�W�F�N�g�p�p�C�v���C������
	Object3D::ObjectCommon objectCommon;
	objectCommon = Object3D::ObjectCommonCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height);
	//�X�v���C�g�p�p�C�v���C������
	Object2D::SpriteCommon spriteCommon;
	spriteCommon = Object2D::SpriteCommonCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height);

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


	//�z����̑S�I�u�W�F�N�g�ɑ΂���
	//for (int i = 0; i < _countof(object3ds); i++)
	//{
	//	//������
	//	object3ds[i] = Object3D::ObjectCreate(i, dev.Get(),WindowsAPI::window_width,WindowsAPI::window_height, basicDescHeap.Get());
	//	object3ds[i].texNumber = 0;
	//	////�ȉ��͐e�q�\���T���v��
	//	////�擪�ȊO�Ȃ�
	//	//if (i > 0)
	//	//{
	//	//	//1�O�̃I�u�W�F�N�g��e�I�u�W�F�N�g�Ƃ���
	//	//	object3ds[i].parent = &object3ds[i - 1];
	//	//	//�e�I�u�W�F�N�g��9���̑傫��
	//	//	object3ds[i].scale = { 0.9f,0.9f,0.9f };
	//	//	//�e�I�u�W�F�N�g�ɑ΂���Z���܂���30�x��]
	//	//	object3ds[i].rotation = { 0,0,30.0f };
	//	//	//�e�I�u�W�F�N�g�ɑ΂���Z����-8.0���炷
	//	//	object3ds[i].position = { 0,0,-8.0f };
	//	//}
	//}

	//�v���C���[������
	player.Init(dxCommon->GetDevice(), 0, WindowsAPI::window_width, WindowsAPI::window_height, basicDescHeap.Get());



	//�e�N�X�`���ǂݍ���
	Object3D::ObjectCommonLoadTexture(objectCommon, 0, L"Resources/texture.png", dxCommon->GetDevice());

	//�f�X�N���v�^�q�[�v�̐擪�n���h�����擾
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV =
		CD3DX12_CPU_DESCRIPTOR_HANDLE(basicDescHeap->GetCPUDescriptorHandleForHeapStart(),
									  constantBufferNum,
									  dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV =
		CD3DX12_GPU_DESCRIPTOR_HANDLE(basicDescHeap->GetGPUDescriptorHandleForHeapStart(),
									  constantBufferNum,
									  dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

	//3�̃r���[��GPU���̃A�h���X�L�^
	D3D12_GPU_DESCRIPTOR_HANDLE gpuDescHandle[3];
	for (int i = 0; i < 3; i++) {
		gpuDescHandle[i] = basicDescHeap->GetGPUDescriptorHandleForHeapStart();
		gpuDescHandle[i].ptr += i * dxCommon->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	}


	////�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	//D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	//dsvHeapDesc.NumDescriptors = 1; //�[�x�r���[��1��
	//dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV; //�f�v�X�X�e���V���r���[
	//ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//result = dev->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));
	////�[�x�r���[�쐬
	//D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	//dsvDesc.Format = DXGI_FORMAT_D32_FLOAT; //�[�x�l�t�H�[�}�b�g
	//dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//dev->CreateDepthStencilView(
	//	depthBuffer.Get(),
	//	&dsvDesc,
	//	dsvHeap->GetCPUDescriptorHandleForHeapStart());


	//�X�v���C�g���ʃe�N�X�`���ǂݍ���
	Object2D::SpriteCommonLoadTexture(spriteCommon, 0, L"Resources/texture.png", dxCommon->GetDevice());
	Object2D::SpriteCommonLoadTexture(spriteCommon, 1, L"Resources/uni.png", dxCommon->GetDevice());


	//�X�v���C�g
	const int spriteNumber = 2;
	Object2D::Sprite sprite[spriteNumber];
	//�X�v���C�g�̐���
	sprite[0] = Object2D::SpriteCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height, 0, spriteCommon);

	sprite[1] = Object2D::SpriteCreate(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height, 1, spriteCommon);
	sprite[1].size = { 250,100 };
	sprite[1].position = { 1280 - sprite[1].size.x,0,0 };

	//�T�C�Y�ύX�𒸓_�o�b�t�@�ɔ��f
	for (int i = 0; i < spriteNumber; i++)
	{
		Object2D::SpriteTransferVertexBuffer(sprite[i]);
	}


	//�f�o�b�O�e�L�X�g
	DebugText debugText;

	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ԍ����w��
	const int debugTextTexNumber = 2;
	//�f�o�b�O�e�L�X�g�p�̃e�N�X�`���ǂݍ���
	Object2D::SpriteCommonLoadTexture(spriteCommon, debugTextTexNumber, L"Resources/DebugText.png", dxCommon->GetDevice());
	//�f�o�b�O�e�L�X�g������
	debugText.Init(dxCommon->GetDevice(), WindowsAPI::window_width, WindowsAPI::window_height, debugTextTexNumber, spriteCommon);


	
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
		//�L�[�{�[�h���͍X�V
		KeyboardInput::Update();
		//�L�[��������Ă���Ƃ��̏�����
		/*if (KeyboardInput::PressKeyTrigger(DIK_0))
		{
			OutputDebugStringA("Hit 0\n");
		}*/


		//�����Đ���
		//SoundPlayWave(xAudio2.Get(),soundData1);
		if (KeyboardInput::PressKeyTrigger(DIK_M))
		{
			audio.SoundPlayWave(audio.xAudio2.Get(), soundData[0]);
		}
		//audio.SoundLoopPlayWave(audio.xAudio2.Get(), soundData[1]);
		/*if (KeyboardInput::PressKeyTrigger(DIK_N))
		{
			audio.SoundStop(audio.xAudio2.Get(), soundData[1]);
		}*/


		////���_���W�̕ύX
		//if (keyboard->PressKey(DIK_RIGHT) || keyboard->PressKey(DIK_LEFT)
		//	|| keyboard->PressKey(DIK_UP) || keyboard->PressKey(DIK_DOWN)
		//	|| keyboard->PressKey(DIK_O) || keyboard->PressKey(DIK_P))
		//{
		//	if (keyboard->PressKey(DIK_RIGHT)) { object3ds[0].position.x += 1.0f; }
		//	else if (keyboard->PressKey(DIK_LEFT)) { object3ds[0].position.x -= 1.0f; }
		//	if (keyboard->PressKey(DIK_UP)) { object3ds[0].position.y += 1.0f; }
		//	else if (keyboard->PressKey(DIK_DOWN)) { object3ds[0].position.y -= 1.0f; }
		//	if (keyboard->PressKey(DIK_O)) { object3ds[0].position.z += 1.0f; }
		//	else if (keyboard->PressKey(DIK_P)) { object3ds[0].position.z -= 1.0f; }
		//}

		//�X�v���C�g�X�V
		for (int i = 0; i < spriteNumber; i++)
		{
			Object2D::SpriteUpdate(sprite[i], spriteCommon);
		}

		////�X�V�����̌Ăяo��
		//for (int i = 0; i < _countof(object3ds); i++)
		//{
		//	Object3D::ObjectUpdate(object3ds[i], nowCam.matView, objectCommon);
		//}
		player.Update();
#pragma endregion
		

		//////�S�D�`��R�}���h�@��������

#pragma region �`��R�}���h
		//�`��O����
		dxCommon->PreDraw();


		////�`��R�}���h
		//�`�揈���֐��̌Ăяo��
		player.Draw(dxCommon->GetDevice(), dxCommon->GetCommandList(), objectCommon, vbView, ibView, _countof(indices), nowCam.matView);


		////�X�v���C�g�`��p

		//�X�v���C�g�`��
		for (int i = 0; i < spriteNumber; i++)
		{
			Object2D::SpriteDraw(sprite[i], dxCommon->GetCommandList(), spriteCommon, dxCommon->GetDevice());
		}

		////�f�o�b�O�e�L�X�g�\��
		//�\�����������������
		debugText.PrintDebugText(spriteCommon, "I am goat.", 400, 100);
		debugText.PrintDebugText(spriteCommon, "I'm not egg.", 400, 150, 1.0f);
		//�f�o�b�O�e�L�X�g�`��
		debugText.DrawAll(dxCommon->GetCommandList(), spriteCommon, dxCommon->GetDevice());


		//�`��I��
		dxCommon->PostDraw();
#pragma endregion
		//////�S�D�`��R�}���h�@�����܂�


		////////////////DirectX���t���[������ �����܂�


	}
	//�N���X(new)�̏���
	//�����f�[�^���
	audio.SoundUnLoad(soundData);
	safe_delete(dxCommon);

	//�E�B���h�E�N���X��o�^����
	WindowsAPI::WindowClassRelease();
	safe_delete(win);

	//�R���\�[���ւ̕����o��
	OutputDebugStringA("Hello,DirectX!!\n");

	return 0;
}

