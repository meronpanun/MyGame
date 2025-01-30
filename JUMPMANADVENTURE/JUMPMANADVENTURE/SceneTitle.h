#pragma once
#include "SceneManager.h"
#include <memory>

class FontManager;
/// <summary>
/// �^�C���V�[���N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	// �V�[���̐؂�ւ����߂�l�Ƃ��ĕԂ�
	// �؂�ւ��Ȃ��ꍇ�͌��ݎ��s���̃V�[����Ԃ�
	SceneManager::SceneSelect Update();
	void Draw();

private:
	// �t�H���g�Ǘ�
	std::shared_ptr<FontManager> m_pFont;
	// �^�C�g���̃O���t�B�b�N�n���h��
	int m_titleHandle;
	int m_uiHandle;

	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;

	// �^�C�g�����o�Ɏg�p����t���[��
	int m_gameTitleFrameCount;

	// �t�F�[�h����
	int m_fadeFrameCount;

	// ����n���h��
	int m_videoHandle;
	// ����̍Đ����
	bool m_isVideoPlaying;
	// �t�F�[�h�A�E�g�t���[���J�E���g
	int m_videoFadeFrameCount;
	// �t�F�[�h�C���t���[���J�E���g
	int m_videoFadeInFrameCount;
};

