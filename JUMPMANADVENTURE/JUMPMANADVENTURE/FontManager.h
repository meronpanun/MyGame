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
	int GetFont(){ return m_fontHandle; }
	int GetFont1(){ return m_fontHandle1; }
	int GetFont2(){ return m_fontHandle2; }

private:
	int m_fontHandle;
	int m_fontHandle1;
	int m_fontHandle2;

};

