#include "DebugText.h"

void DebugText::Init(ID3D12Device * dev, int window_wigth, int window_height, UINT texnumber, const Object2D::SpriteCommon & spriteCommon)
{
	//全てのデバッグテキストデータに対して
	for (int i = 0; i < _countof(textSprites); i++)
	{
		//デバッグテキスト用文字画像を生成する
		textSprites[i] = Object2D::SpriteCreate(dev, window_wigth, window_height, texnumber, spriteCommon, { 0,0 });
	}
}

void DebugText::PrintDebugText(const Object2D::SpriteCommon & spriteCommon, const std::string & text, float x, float y, float scale)
{
	//全ての文字について
	for (int i = 0; i < text.size(); i++)
	{
		//最大文字数超過
		if (textIndex >= maxCharCount) {
			break;
		}

		//1文字取り出す(ASCIIコード)
		const unsigned char& character = text[i];

		//ASCIIコードを2段分飛ばした番号を計算
		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		//座標計算
		textSprites[textIndex].position = { x + fontWidth * scale * i,y,0 };
		textSprites[textIndex].texLeftTop = { (float)fontIndexX * fontWidth,(float)fontIndexY * fontHeight };
		textSprites[textIndex].texSize = { fontWidth , fontHeight };
		textSprites[textIndex].size = { fontWidth * scale,fontHeight * scale };
		//頂点バッファ転送
		Object2D::SpriteTransferVertexBuffer(textSprites[textIndex], spriteCommon);
		//更新
		Object2D::SpriteUpdate(textSprites[textIndex], spriteCommon);
		//文字を一つ進める
		textIndex += 1;
	}
}

void DebugText::DrawAll(ID3D12GraphicsCommandList * cmdList, const Object2D::SpriteCommon & spriteCommon, ID3D12Device * dev)
{
	//全ての文字のスプライトに対して
	for (int i = 0; i < textIndex; i++)
	{
		//スプライト描画
		Object2D::SpriteDraw(&textSprites)
	}
}
