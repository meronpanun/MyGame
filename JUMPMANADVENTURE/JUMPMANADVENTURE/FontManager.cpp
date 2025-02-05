#include "FontManager.h"
#include <windows.h>

bool FontManager::fontResourceAdded = false;

FontManager::FontManager()
{
    // �t�H���g�t�@�C���̃p�X
    LPCSTR font_path = "data/SuperMario256.ttf";

    // �t�H���g���\�[�X��ǉ�
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
}

FontManager::~FontManager()
{
    ReleaseAllFonts();

    // �t�H���g���\�[�X�̍폜
    if (fontResourceAdded)
    {
        LPCSTR font_path = "data/SuperMario256.ttf";
        RemoveFontResourceEx(font_path, FR_PRIVATE, NULL);
        fontResourceAdded = false;
    }
}

int FontManager::GetFont(int size)
{
	// �t�H���g�����݂��Ȃ��ꍇ�͍쐬
    if (m_fonts.find(size) == m_fonts.end())
    {
        int fontHandle = CreateFontToHandle("Super Mario 256", size, -1, DX_FONTTYPE_ANTIALIASING | DX_FONTTYPE_EDGE);
        m_fonts[size] = fontHandle;
    }
    return m_fonts[size];
}

void FontManager::ReleaseAllFonts()
{
	// �쐬�����t�H���g��S�č폜
    for (auto& font : m_fonts)
    {
        DeleteFontToHandle(font.second);
    }
    m_fonts.clear();
}

