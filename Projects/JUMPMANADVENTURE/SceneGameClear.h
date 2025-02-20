#pragma once
#include "SceneBase.h"
#include <memory>
#include "Vec2.h"
#include <vector>

class FontManager;

/// <summary>
///�@�Q�[���N���A�V�[���N���X
/// </summary>
class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(int score, int goalHitTime, bool isNoDamage);
	~SceneGameClear();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

	// �V�[���I���t���O�̎擾
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �Q�[���N���A�p�v���C���[�̏�����
	void InitGameClearPlayers();
	// �Q�[���N���A�p�v���C���[�̍X�V
	void UpdateGameClearPlayers();
	// �Q�[���I�N���A�p�v���C���[�̕`��
	void DrawGameClearPlayers();

private:
	// �Q�[���N���A�p�v���C���[�̏��
	struct GameClearPlayer
	{
		Vec2 pos;
		float fallSpeed = 0.0f;     // �������x
		float rotationSpeed = 0.0f; // ��]���x
		float angle = 0.0f;         // ��]�p�x
	};

	std::vector<GameClearPlayer> m_gameClearPlayers;
	// �t�H���g�Ǘ�
	std::shared_ptr<FontManager> m_pFont;

	// �N���A�V�[���̃O���t�B�b�N�n���h��
	int m_gameClearBgHandle;
	int m_gameClearPlayerHandle;
	// �G�t�F�N�g�̃O���t�B�b�N�n���h��
	int m_effectHandle;
	// BGM
	int m_bgmHandle;
	// SE
	int m_seHandle;

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

    // �Q�[���I�[�o�[�p�G�̈ʒu�Ɖ�]�p�x
	float m_gameClearPlayerPosY;
	float m_gameClearPlayerAngle;

	// �E�F�[�u�̃t���[���J�E���g
	int m_waveFrameCount;
	
	// �X�R�A�ƃ^�C�}�[
	int m_score;
	int m_goalHitTime;
	int m_bonusTimer;

	// �v���C���[���_���[�W�������H���Ȃ��������ǂ����̃t���O
	bool m_isNoDamage;
};

