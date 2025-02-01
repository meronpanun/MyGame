#pragma once
#include "SceneBase.h"
#include "Life.h"
#include <memory>
#include <vector>
#include "Vec2.h"

class FontManager;
class Player;
class BgStage1;
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

	// �X�R�A�ƃ^�C�}�[�̃t�H���g�T�C�Y�̐ݒ�
	void SetScoreAndTimerFontSize(int size); 

	// �Q�[���I�[�o�[�p�G�̏��
	struct GameOverEnemy
	{
		Vec2 pos;
		float fallSpeed;     // �������x
		float rotationSpeed; // ��]���x
		float angle;		 // ��]�p�x
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
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<SceneMain> m_pSceneMain;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::vector<Life> m_life;
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
	// �Q�[���V�[���pBGM�n���h��
	int m_bgmHandle;
	// �Q�[���V�[���pSE�n���h��
	int m_seHandle;

	// �Q�[���I�[�o�[���o�Ɏg�p����t���[��
	int m_gameOverFrameCount;
	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;

	// �X�R�A�ƃ^�C�}�[���Ǘ����郁���o�ϐ���ǉ�
	int m_score;
	int m_timer;

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

	// �^�C�}�[���X�R�A�ɉ��Z���邽�߂̃����o�[�ϐ�
	bool m_isAddingScore;
	int m_bonusScore;

	// �S�[���ɓ�����������
	int m_goalHitTime;
};

