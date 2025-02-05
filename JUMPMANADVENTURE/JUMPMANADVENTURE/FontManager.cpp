#include "FontManager.h"
#include "DxLib.h"
#include <windows.h>


bool FontManager::fontResourceAdded = false;

FontManager::FontManager() : 
	m_fontHandle(-1),
	m_fontHandle1(-1), 
	m_fontHandle2(-1)
{
	// �t�@�C���̃��[�h
	LPCSTR font_path = "data/SuperMario256.ttf";

	if (!fontResourceAdded)
	{
		int addFontResult = AddFontResourceEx(font_path, FR_PRIVATE, NULL);
		if (addFontResult > 0)
		{
			fontResourceAdded = true;
		}
		else
		{
			// �t�H���g�̓ǂݍ��݃G���[����
			MessageBox(NULL, "�t�H���g�ǂݍ��ݎ��s: �t�H���g�t�@�C����������܂���", "", MB_OK);
			return;
		}
	}

	// �t�H���g�̓ǂݍ���
	m_fontHandle = CreateFontToHandle("Super Mario 256", 40, -1, 3);
	m_fontHandle1 = CreateFontToHandle("Super Mario 256", 84, -1, 3);
	m_fontHandle2 = CreateFontToHandle("Super Mario 256", 46, -1, 3);

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

	// �t�H���g���\�[�X�̍폜
	if (fontResourceAdded)
	{
		LPCSTR font_path = "data/SuperMario256.ttf";
		RemoveFontResourceEx(font_path, FR_PRIVATE, NULL);
		fontResourceAdded = false;
	}
}

int FontManager::GetFont()
{
	return m_fontHandle;
}

int FontManager::GetFont1()
{
	return m_fontHandle1;
}

int FontManager::GetFont2()
{
	return m_fontHandle2;
}
