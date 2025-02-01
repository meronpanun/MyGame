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
	m_fontHandle1 = CreateFontToHandle("Super Mario 256", 84, -1);
	m_fontHandle2 = CreateFontToHandle("Super Mario 256", 46, -1);

	// フォントハンドルが有効かどうかをチェック
	if (m_fontHandle == -1 || m_fontHandle1 == -1 || m_fontHandle2 == -1)
	{
		MessageBox(NULL, "フォントハンドルの作成に失敗しました", "", MB_OK);
	}
}

FontManager::~FontManager()
{
	// フォントの解放
	DeleteFontToHandle(m_fontHandle);
	DeleteFontToHandle(m_fontHandle1);
	DeleteFontToHandle(m_fontHandle2);
}
