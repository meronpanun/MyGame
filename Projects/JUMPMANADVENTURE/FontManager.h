#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>

/// <summary>
/// フォント管理クラス
/// </summary>
class FontManager
{
public:
    FontManager();
    ~FontManager();

	// フォントを取得
    int GetFont(int size);

	// フォントを全て解放
    void ReleaseAllFonts();
    std::unordered_map<int, int> m_fonts;

	// フォントリソースの追加フラグ
    static bool fontResourceAdded;

private:
    // フォントの上限
    static constexpr int kMaxFonts = 10;
    // 古いフォントを解放
    void ReleaseOldestFont();
};

