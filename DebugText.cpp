#include "DebugText.h"

void DebugText::Init(ID3D12Device * dev, int window_wigth, int window_height, UINT texnumber, const Object2D::SpriteCommon & spriteCommon)
{
	//�S�Ẵf�o�b�O�e�L�X�g�f�[�^�ɑ΂���
	for (int i = 0; i < _countof(textSprites); i++)
	{
		//�f�o�b�O�e�L�X�g�p�����摜�𐶐�����
		textSprites[i] = Object2D::SpriteCreate(dev, window_wigth, window_height, texnumber, spriteCommon, { 0,0 });
	}
}

void DebugText::PrintDebugText(const Object2D::SpriteCommon & spriteCommon, const std::string & text, float x, float y, float scale)
{
	//�S�Ă̕����ɂ���
	for (int i = 0; i < text.size(); i++)
	{
		//�ő啶��������
		if (textIndex >= maxCharCount) {
			break;
		}

		//1�������o��(ASCII�R�[�h)
		const unsigned char& character = text[i];

		//ASCII�R�[�h��2�i����΂����ԍ����v�Z
		int fontIndex = character - 32;
		if (character >= 0x7f) {
			fontIndex = 0;
		}

		int fontIndexY = fontIndex / fontLineCount;
		int fontIndexX = fontIndex % fontLineCount;

		//���W�v�Z
		textSprites[textIndex].position = { x + fontWidth * scale * i,y,0 };
		textSprites[textIndex].texLeftTop = { (float)fontIndexX * fontWidth,(float)fontIndexY * fontHeight };
		textSprites[textIndex].texSize = { fontWidth , fontHeight };
		textSprites[textIndex].size = { fontWidth * scale,fontHeight * scale };
		//���_�o�b�t�@�]��
		Object2D::SpriteTransferVertexBuffer(textSprites[textIndex], spriteCommon);
		//�X�V
		Object2D::SpriteUpdate(textSprites[textIndex], spriteCommon);
		//��������i�߂�
		textIndex += 1;
	}
}

void DebugText::DrawAll(ID3D12GraphicsCommandList * cmdList, const Object2D::SpriteCommon & spriteCommon, ID3D12Device * dev)
{
	//�S�Ă̕����̃X�v���C�g�ɑ΂���
	for (int i = 0; i < textIndex; i++)
	{
		//�X�v���C�g�`��
		Object2D::SpriteDraw(textSprites[i], cmdList,spriteCommon,dev);
	}

	//�z�񏉊���
	textIndex = 0;
}
