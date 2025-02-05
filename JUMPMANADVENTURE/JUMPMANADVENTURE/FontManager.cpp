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
	// フォントが存在しない場合は作成
    if (m_fonts.find(size) == m_fonts.end())
    {
        int fontHandle = CreateFontToHandle("Super Mario 256", size, -1, DX_FONTTYPE_ANTIALIASING | DX_FONTTYPE_EDGE);
        m_fonts[size] = fontHandle;
    }
    return m_fonts[size];
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

