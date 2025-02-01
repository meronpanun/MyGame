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
	m_fontHandle1 = CreateFontToHandle("Super Mario 256", 84, -1);
	m_fontHandle2 = CreateFontToHandle("Super Mario 256", 46, -1);

	// �t�H���g�n���h�����L�����ǂ������`�F�b�N
	if (m_fontHandle == -1 || m_fontHandle1 == -1 || m_fontHandle2 == -1)
	{
		MessageBox(NULL, "�t�H���g�n���h���̍쐬�Ɏ��s���܂���", "", MB_OK);
	}
}

FontManager::~FontManager()
{
	// �t�H���g�̉��
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle1);
	DeleteFontToHandle(m_fontHandle2);
}
