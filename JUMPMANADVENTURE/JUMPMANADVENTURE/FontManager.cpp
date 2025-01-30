#include "FontManager.h"
#include "DxLib.h"

FontManager::FontManager()
{
	// ファイルのロード
	LPCSTR font_path = "data/SuperMario256.ttf";

	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0)
	{
	}
	else
	{
		// フォントの読み込みエラー処理
		MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
	}
	// フォントの読み込み
	m_fontHandle = CreateFontToHandle("Super Mario 256", 40, -1);
	m_fontHandle1 = CreateFontToHandle("Super Mario 256", 64, -1);
	m_fontHandle2 = CreateFontToHandle("Super Mario 256", 34, -1);
}

FontManager::~FontManager()
{
	// フォントの解放
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle1);
	DeleteFontToHandle(m_fontHandle2);
}
