#pragma once

/// <summary>
/// フォント管理クラス
/// </summary>
class FontManager
{
public:
	FontManager();
	~FontManager();

	// フォントを取得
	int GetFont();
	int GetFont1();
	int GetFont2();

private:
	// フォントハンドル
	int m_fontHandle;
	int m_fontHandle1;
	int m_fontHandle2;

	static bool fontResourceAdded;

};

