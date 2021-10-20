#pragma once
#include<DirectXTex.h>
#include<wrl.h>
#include<d3d12.h>
#include<d3dx12.h>
#include<vector>
#include<string>
#include<DirectXMath.h>
#include<d3dcompiler.h>

using namespace Microsoft::WRL;
using namespace DirectX;
#pragma comment(lib,"d3dcompiler.lib")


class Object2D
{
public:  //�����o�ϐ��A�\����
	//�p�C�v���C���Z�b�g�\����
	struct PipelineSet
	{
		//�p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
		//���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
	};
	//�X�v���C�g�p�p�C�v���C������
	static PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* dev);

	//�X�v���C�g1�����̃f�[�^
	struct Sprite
	{
		//���_�o�b�t�@
		ComPtr<ID3D12Resource> vertBuff;
		//���_�o�b�t�@�r���[
		D3D12_VERTEX_BUFFER_VIEW vbView{};
		//�萔�o�b�t�@
		ComPtr<ID3D12Resource> constBuff;

		//Z������̉�]�p
		float rotation = 0.0f;
		//���W
		XMFLOAT3 position = { 0,0,0 };
		//���[���h�s��
		XMMATRIX matWorld;
		//�F RGBA
		XMFLOAT4 color = { 1,1,1,1 };
		//�g�p����e�N�X�`���̔ԍ�
		UINT texNumber = 0;
		//�摜�̃T�C�Y(�傫��)
		XMFLOAT2 size = { 100,100 };
		//�A���J�[�|�C���g
		XMFLOAT2 anchorpoint = { 0,0 };
		//���E���]
		bool isFlipX = false;
		//�㉺���]
		bool isFlipY = false;
		//��\��
		bool isInvisible = false;
		//�e�N�X�`��������W
		XMFLOAT2 texLeftTop = { 0,0 };
		//�e�N�X�`���؂�o���T�C�Y
		XMFLOAT2 texSize = { 100,100 };
	};
	//�X�v���C�g���ʃf�[�^
	static const int spriteSRVCount = 512; //�e�N�X�`���̍ő喇��
	struct SpriteCommon
	{
		//�p�C�v���C���Z�b�g
		PipelineSet pipelineSet;
		//�ˉe�s��
		XMMATRIX matProjection{};

		//�e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
		ComPtr<ID3D12DescriptorHeap> descHeap;
		//�e�N�X�`�����\�[�X�i�e�N�X�`���o�b�t�@�j�̐���
		ComPtr<ID3D12Resource> texBuff[spriteSRVCount];
	};

	//���_�\���̃f�[�^
	struct VertexPosUv
	{
		XMFLOAT3 pos; //xyz���W
		XMFLOAT2 uv; //uv���W
	};
	//�萔�o�b�t�@�f�[�^�\���́i���肽���f�[�^���������炱���ɏ����j
	struct ConstBufferData
	{
		XMFLOAT4 color; //�F(RGBA)
		XMMATRIX mat; //3D�ϊ��s��
	};




	////�X�v���C�g�����p�֐�
    //�X�v���C�g���ʃf�[�^����
	static SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);
	//�X�v���C�g���ʃe�N�X�`���ǂݍ���
	static void SpriteCommonLoadTexture(SpriteCommon& spriteCommon, UINT texnumber, const wchar_t* filename, ID3D12Device* dev);
	//�X�v���C�g�p���ʃO���t�B�b�N�X�R�}���h
	static void SpriteCommonBeginDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	//�X�v���C�g�P�̒��_�o�b�t�@�̓]��
	//�ʏ�
	static void SpriteTransferVertexBuffer(const Sprite& sprite);
	//�e�N�X�`���؂�o��
	static void SpriteTransferVertexBuffer(const Sprite& sprite, const SpriteCommon& spriteCommon);

	//�X�v���C�g����������
	static Sprite SpriteCreate(ID3D12Device* dev, int window_width, int window_height, UINT texNumber,const SpriteCommon& spriteCommon, XMFLOAT2 anchorpoint = { 0,0 },bool isFlipX = false, bool isFlipY = false);
	//�X�v���C�g�P�̍X�V����
	static void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);
	//�X�v���C�g�P�̕`��R�}���h
	static void SpriteDraw(const Sprite& sprite, ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon, ID3D12Device* dev);

};

