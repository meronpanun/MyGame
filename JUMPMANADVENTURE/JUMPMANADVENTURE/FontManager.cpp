#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
	// �t�@�C���̃��[�h
	LPCSTR font_path = "data/SuperMario256.ttf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// �t�H���g�̓ǂݍ��݃G���[����
		MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s", "", MB_OK);
	}
	// �t�H���g�̓ǂݍ���
	m_fontHandle = CreateFontToHandle("Super Mario 256", 40, -1);
	m_fontHandle1 = CreateFontToHandle("Super Mario 256", 64, -1);
	m_fontHandle2 = CreateFontToHandle("Super Mario 256", 34, -1);
}

FontManager::~FontManager()
{
	// �t�H���g�̉��
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle1);
	DeleteFontToHandle(m_fontHandle2);
}
