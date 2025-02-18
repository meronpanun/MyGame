#pragma once
#include "DxLib.h"
#include <unordered_map>
#include <string>

/// <summary>
/// �t�H���g�Ǘ��N���X
/// </summary>
class FontManager
{
public:
    FontManager();
    ~FontManager();

	// �t�H���g���擾
    int GetFont(int size);

	// �t�H���g��S�ĉ��
    void ReleaseAllFonts();
    std::unordered_map<int, int> m_fonts;

	// �t�H���g���\�[�X�̒ǉ��t���O
    static bool fontResourceAdded;

private:
    // �t�H���g�̏��
    static constexpr int kMaxFonts = 10;
    // �Â��t�H���g�����
    void ReleaseOldestFont();
};

