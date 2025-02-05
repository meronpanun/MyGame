#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>

class FontManager
{
public:
    FontManager();
    ~FontManager();

	// フォントを取得
    int GetFont(int size);

	// フォントを全て解放
    void ReleaseAllFonts();

private:
    std::unordered_map<int, int> m_fonts;
	// フォントリソースの追加フラグ
    static bool fontResourceAdded;
};

