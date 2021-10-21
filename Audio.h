#pragma once
#include<Windows.h>
#include<xaudio2.h>
#include<wrl.h>

//�I�[�f�B�I�R�[���o�b�N
class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:
	//�{�C�X�����p�X�̊J�n��
	void OnVoiceProcessingPassStart(UINT32 ByteRequired) {};
	//�{�C�X�����p�X�̏I����
	void OnVoiceProcessingPassEnd() {};
	//�o�b�t�@�X�g���[���̍Đ����I��������
	void OnStreamEnd() {};
	//�o�b�t�@�̎g�p�J�n��
	void OnBufferStart(void* pBufferContext) {};
	//�o�b�t�@�̖����ɒB�����Ƃ�
	void OnBufferEnd(void* pBufferContext) { delete[] pBufferContext; };
	//�Đ������[�v�ʒu�ɒB�����Ƃ�
	void OnLoopEnd(void* pBufferContext) {};
	//�{�C�X�̎��s�G���[��
	void OnVoiceError(void* pBufferContext, HRESULT Error) {};
};

//�I�[�f�B�I
class Audio
{
private:
	//Microsoft::WRL::���ȗ�����
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: //�ϐ�
	
	IXAudio2MasteringVoice* masterVoice;
	XAudio2VoiceCallback voiceCallback;


public: //�\����
	ComPtr<IXAudio2> xAudio2;
	//�`�����N�w�b�_
	struct ChunkHeader
	{
		char id[4]; //�`�����N����ID
		int size; //�`�����N�T�C�Y
	};
	//RIFF�w�b�_�`�����N
	struct RiffHeader
	{
		ChunkHeader chunk; //"RIFF"
		char type[4]; //"WAVE"
	};
	//FMT�`�����N
	struct FormatChunk
	{
		ChunkHeader chunk; //"fmt"
		WAVEFORMATEX fmt; //�g�`�t�H�[�}�b�g
	};
	//�����f�[�^
	struct SoundData
	{
		//�g�`�t�H�[�}�b�g
		WAVEFORMATEX wfex;
		//�o�b�t�@�̐擪�A�h���X
		BYTE* pBuffer;
		//�o�b�t�@�̃T�C�Y
		unsigned int bufferSize;
	};

public: //�֐�
	//�����֌W������
	void Init();
	//�����f�[�^�ǂݍ���
	SoundData SoundLoadWave(const char* filename);
	//�����Đ�
	void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData);
	//���[�v�Đ�
	void SoundLoopPlayWave(IXAudio2* xAudio2, const SoundData& soundData);
	//�Đ���~
	void SoundStop(IXAudio2* xAudio2, const SoundData& soundData);
	//�����f�[�^���
	void SoundUnLoad(SoundData* soundData);


};