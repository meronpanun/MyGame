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
	SceneGameClear(int score, int goalHitTime, int bonusTimer);
	~SceneGameClear();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �Q�[���I�[�o�[�p�G�̏��
	struct GameClearPlayer
	{
		Vec2 pos; 
		float fallSpeed;	 // �������x
		float rotationSpeed; // ��]���x
		float angle;		 // ��]�p�x
	};
	std::vector<GameClearPlayer> m_gameClearPlayers;
	// �Q�[���I�[�o�[�p�G�̏�����
	void InitGameClearPlayers();
	// �Q�[���I�[�o�[�p�G�̍X�V
	void UpdateGameClearPlayers();
	// �Q�[���I�[�o�[�p�G�̕`��
	void DrawGameClearPlayers();

private:
	// �t�H���g�Ǘ�
	std::shared_ptr<FontManager> m_pFont;
	// �N���A�V�[���̃O���t�B�b�N�n���h��
	int m_gameClearBgHandle;
	int m_gameClearPlayerHandle;

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
};

