#pragma once
#include "SceneBase.h"
#include <memory>

class FontManager;
/// <summary>
///�@�Q�[���N���A�V�[���N���X
/// </summary>
class SceneGameClear : public SceneBase
{
public:
	SceneGameClear();
	~SceneGameClear();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �t�H���g�Ǘ�
	std::shared_ptr<FontManager> m_pFont;
	// �N���A�V�[���̃O���t�B�b�N�n���h��
	int m_gameClearHandle;

	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;

	// �Q�[���N���A���o�Ɏg�p����t���[��
	int m_gameClearFrameCount;

	// �t�F�[�h����
	int m_fadeFrameCount;
	
	// �V�[���I���t���O true:�V�[���J��
	bool m_isSceneTitle;// �^�C�g��

	// �w�i�̃X�N���[��
	int m_bgScrollY;
};

