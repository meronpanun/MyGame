#pragma once
#include "SceneBase.h"
#include "FontManager.h"
#include "Life.h"
#include "Vec2.h"
#include <vector>
#include <memory>

class ItemHp;
class FontManager;
class Player;
class BgStage;
class Camera;
class Goal;
class Enemy;

/// <summary>
/// �Q�[����ʃN���X
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	~SceneMain();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

private:
	// �G�̐���
	void CreateEnemy(float x, float y);

	// �A�C�e���̐���
	void CreateItemHp(float x, float y);

	// �X�R�A�ƃ^�C�}�[�̃t�H���g�T�C�Y�̐ݒ�
	void SetScoreAndTimerFontSize(int size); 

	// �Q�[���I�[�o�[�p�G�̏��
	struct GameOverEnemy
	{
		Vec2 pos;
		float fallSpeed = 0;     // �������x
		float rotationSpeed = 0; // ��]���x
		float angle = 0;		 // ��]�p�x
	};
	std::vector<GameOverEnemy> m_gameOverEnemies;
	// �Q�[���I�[�o�[�p�G�̏�����
	void InitGameOverEnemies();
	// �Q�[���I�[�o�[�p�G�̍X�V
	void UpdateGameOverEnemies();
	// �Q�[���I�[�o�[�p�G�̕`��
	void DrawGameOverEnemies();

private:
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage> m_pBgStage;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::vector<Life> m_life;
	std::vector<std::shared_ptr<ItemHp>> m_pItemHp;
	// �t�H���g�Ǘ�
	std::shared_ptr<FontManager> m_pFont;

	// �t�F�[�h����
	int m_fadeFrameCount;

	// �O���t�B�b�N�n���h��
	int m_lifeHandle;
	int m_flagHandle;
	int m_poleHandle;
	int m_bgHandle;
	int m_enemyHandle;
	// �G�t�F�N�g�̃O���t�B�b�N�n���h��
	int m_effectHandle;
	// BGM
	int m_bgmHandle;
	int m_noTimeBGMHandle;
	// SE
	int m_seHandle;
	int m_enemyDeadSEHandle;
	int m_gameOverBGMHandle;
	int m_pressAButtonSEHandle;

	// �Q�[���I�[�o�[���o�Ɏg�p����t���[��
	int m_gameOverFrameCount;
	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;

	// �X�R�A�ƃ^�C�}�[���Ǘ�
	int m_score;
	int m_timer;
	// �X�R�A�ɉ��Z����p�̃^�C�}�[
	int m_bonusTimer; 

	// �X�R�A�ƃ^�C�}�[�̃t�H���g�T�C�Y���Ǘ����郁���o�ϐ�
	int m_scoreAndTimerFontSize;

	// �Q�[���I�[�o�[�ɂȂ�����A1�{�^����������
	bool m_isGameEnd;
	// �S�[���ɓ����������ǂ����t���O
	bool m_isGoalHit; 

	// �w�i�̃X�N���[���ʒu
	int m_bgScrollY;

	// �Q�[���I�[�o�[�p�G�̈ʒu�Ɖ�]�p�x
	float m_gameOverEnemyPosY;
	float m_gameOverEnemyAngle;

	// �^�C�}�[���X�R�A�ɉ��Z
	bool m_isAddingScore;
	int m_bonusScore;

	// �S�[���ɓ�����������
	int m_goalHitTime;
	// �S�[����̉�ʑJ�ڂ܂ł̑ҋ@���ԁi�t���[�����j
	int m_goalTransitionTimer;

	// BGM�̉���
	int m_bgmVolume; 
	// BGM���t�F�[�h�A�E�g�����ǂ����������t���O
	bool m_isBgmFadingOut;
	// BGM�̃t�F�[�h�A�E�g�̃t���[���J�E���g
	int m_bgmFadeOutFrameCount; 
	// �m�[�^�C��BGM���Đ������ǂ����������t���O
	bool m_isHurryUpBGMPlaying;
	//  �m�[�^�C��BGM�̃t�F�[�h�A�E�g�����ǂ����������t���O
	bool m_isNoTimeBgmFadingOut; 
	// �m�[�^�C��BGM�̃t�F�[�h�A�E�g�̃t���[���J�E���g
	int m_noTimeBgmFadeOutFrameCount;

	// �^�C�}�[�̌��Z���x
	float m_timerDecrementSpeed;
	// �S�[�����̃^�C�}�[�̒l
	int m_goalTimer; 
	// �^�C�}�[���Z�J�n�𐧌�
	int m_timerDecrementStartCount; 
	// �S�[�����̃^�C�}�[���Z���t���O
	bool m_isGoalTimerDecrementing; 

	// �v���C���[���_���[�W�������H���Ȃ��������ǂ����̃t���O
	bool m_isNoDamage;

	// �A�j���[�V�����̐i�s
	int m_animFrame;
};

