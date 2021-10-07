#pragma once
#include<Windows.h>

//インクルード関係
#define DIRECTINPUT_VERSION 0x0800 //DirectInputバージョン指定
#include<dinput.h>

class KeyboardInput
{
public:
	
	//初期化
	static void Init(HWND hwnd);

	//毎フレーム更新
	static void Update();

	//情報の利用
	static bool PressKeyTrigger(int key);
	static bool ReleaseKeyTrigger(int key);
	static bool PressKey(int key);
	static bool ReleaseKey(int key);


private:
	static int pressKey[256];
	static int releaseKey[256];
};