#include "FontManager.h"
#include "DxLib.h"
#include <windows.h>


bool FontManager::fontResourceAdded = false;

FontManager::FontManager() : 
	m_fontHandle(-1),
	m_fontHandle1(-1), 
	m_fontHandle2(-1)
{
	// ファイルのロード
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
			// フォントの読み込みエラー処理
			MessageBox(NULL, "フォント読み込み失敗: フォントファイルが見つかりません", "", MB_OK);
			return;
		}
	}

	// フォントの読み込み
	m_fontHandle = CreateFontToHandle("Super Mario 256", 40, -1, 3);
	m_fontHandle1 = CreateFontToHandle("Super Mario 256", 84, -1, 3);
	m_fontHandle2 = CreateFontToHandle("Super Mario 256", 46, -1, 3);

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

	// フォントリソースの削除
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
