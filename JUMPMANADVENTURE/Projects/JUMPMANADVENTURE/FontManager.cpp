#include "FontManager.h"
#include <windows.h>

bool FontManager::fontResourceAdded = false;

FontManager::FontManager()
{
    // フォントファイルのパス
    LPCSTR font_path = "data/SuperMario256.ttf";

    // フォントリソースを追加
    if (!fontResourceAdded)
    {
        int addFontResult = AddFontResourceEx(font_path, FR_PRIVATE, NULL);
        if (addFontResult > 0)
        {
            fontResourceAdded = true;
        }
        else
        {
            // フォントの読み込みエラー処理
            MessageBox(NULL, "フォント読み込み失敗: フォントファイルが見つかりません", "", MB_OK);
            return;
        }
    }
}

FontManager::~FontManager()
{
    ReleaseAllFonts();

    // フォントリソースの削除
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

    // フォントの上限に達している場合、古いフォントを解放
    if (m_fonts.size() >= kMaxFonts)
    {
        ReleaseOldestFont();
    }

    // "Super Mario 256" フォントを使用してフォントを作成
    int fontHandle = CreateFontToHandle("Super Mario 256", size, -1, DX_FONTTYPE_ANTIALIASING | DX_FONTTYPE_EDGE);
    m_fonts[size] = fontHandle;
    return fontHandle;
}

void FontManager::ReleaseAllFonts()
{
	// 作成したフォントを全て削除
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

