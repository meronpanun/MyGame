#pragma once
#include "SceneBase.h"
#include "Life.h"
#include <memory>
#include <vector>

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
		float posY;
		float angle;
		float fallSpeed;
		float rotationSpeed;
	};
	std::vector<GameOverEnemy> m_gameOverEnemies;
	void InitGameOverEnemies();
	void UpdateGameOverEnemies();
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
	int m_playerDaedHandle;
	// �Q�[���V�[���pBGM�n���h��
	int m_bgmHandle;
	// �Q�[���V�[���pSE�n���h��
	int m_seHandle;

	// �Q�[���I�[�o�[���o�Ɏg�p����t���[��
	int m_gameoverFrameCount;
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
};

