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
    auto it = m_fonts.find(size);
    if (it != m_fonts.end())
    {
        return it->second;
    }

    // �t�H���g�̏���ɒB���Ă���ꍇ�A�Â��t�H���g�����
    if (m_fonts.size() >= kMaxFonts)
    {
        ReleaseOldestFont();
    }

    // "Super Mario 256" �t�H���g���g�p���ăt�H���g���쐬
    int fontHandle = CreateFontToHandle("Super Mario 256", size, -1, DX_FONTTYPE_ANTIALIASING | DX_FONTTYPE_EDGE);
    m_fonts[size] = fontHandle;
    return fontHandle;
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

void FontManager::ReleaseOldestFont()
{
    if (!m_fonts.empty()) 
    {
        auto it = m_fonts.begin();
        DeleteFontToHandle(it->second);
        m_fonts.erase(it);
    }
}

