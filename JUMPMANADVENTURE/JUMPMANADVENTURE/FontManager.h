#pragma once

/// <summary>
/// �t�H���g�Ǘ��N���X
/// </summary>
class FontManager
{
public:
	FontManager();
	~FontManager();

	// �t�H���g���擾
	int GetFont();
	int GetFont1();
	int GetFont2();

private:
	// �t�H���g�n���h��
	int m_fontHandle;
	int m_fontHandle1;
	int m_fontHandle2;

	static bool fontResourceAdded;

};

