#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>

class FontManager
{
public:
    FontManager();
    ~FontManager();

	// �t�H���g���擾
    int GetFont(int size);

	// �t�H���g��S�ĉ��
    void ReleaseAllFonts();

private:
    std::unordered_map<int, int> m_fonts;
	// �t�H���g���\�[�X�̒ǉ��t���O
    static bool fontResourceAdded;
};

