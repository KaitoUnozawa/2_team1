#pragma once
#include<Windows.h>
#include<xaudio2.h>
#include<wrl.h>

//オーディオコールバック
class XAudio2VoiceCallback : public IXAudio2VoiceCallback
{
public:
	//ボイス処理パスの開始時
	void OnVoiceProcessingPassStart(UINT32 Byte)
};

//オーディオ
class Audio
{
private:
	//Microsoft::WRL::を省略する
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

private: //変数
	ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;


public: //構造体
	//チャンクヘッダ
	struct ChunkHeader
	{
		char id[4]; //チャンク毎のID
		int size; //チャンクサイズ
	};
	//RIFFヘッダチャンク
	struct RiffHeader
	{
		ChunkHeader chunk; //"RIFF"
		char type[4]; //"WAVE"
	};
	//FMTチャンク
	struct FormatChunk
	{
		ChunkHeader chunk; //"fmt"
		WAVEFORMATEX fmt; //波形フォーマット
	};
	//音声データ
	struct SoundData
	{
		//波形フォーマット
		WAVEFORMATEX wfex;
		//バッファの先頭アドレス
		BYTE* pBuffer;
		//バッファのサイズ
		unsigned int bufferSize;
	};

public: //関数
	//音声関係初期化
	void Init();
	//音声データ読み込み
	SoundData SoundLoadWave(const char* filename);
	//音声再生
	void SoundPlayWave(IXAudio2* xAudio2, const SoundData& soundData);
	//ループ再生
	void SoundLoopPlayWave(IXAudio2* xAudio2, const SoundData& soundData);
	//音声データ解放
	void SoundUnLoad(SoundData* soundData);


};