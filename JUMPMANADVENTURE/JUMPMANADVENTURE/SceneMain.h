#pragma once
#include "SceneManager.h"
#include "Life.h"
#include <memory>
#include <vector>

class Player;
class BgStage1;
class Camera;
class Goal;
class Enemy;
/// <summary>
/// �Q�[����ʃN���X
/// </summary>
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	SceneManager::SceneSelect Update();
	void Draw();

	// �G�̐���
	void CreateEnemy(float x, float y);

	// �X�R�A�̃t�H���g�T�C�Y�̐ݒ�
	void SetScoreFontSize(int size); 
	// �^�C�}�[�̃t�H���g�T�C�Y�̐ݒ�
	void SetTimerFontSize(int size); 

private:
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<SceneMain> m_pSceneMain;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::vector<Life> m_life;

	// �t�F�[�h����
	int m_fadeFrameCount;
	// �O���t�B�b�N�n���h��
	int m_lifeHandle;
	int m_goalHandle;
	// �t�H���g�n���h��
	int m_fontHandle;
	// �Q�[���I�[�o�[���o�Ɏg�p����t���[��
	int m_gameoverFrameCount;
	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;

	// �X�R�A�ƃ^�C�}�[���Ǘ����郁���o�ϐ���ǉ�
	int m_score;
	int m_timer;

	// �X�R�A�ƃ^�C�}�[�̃t�H���g�T�C�Y���Ǘ����郁���o�ϐ�
	int m_scoreFontSize;
	int m_timerFontSize;

	// �Q�[���I�[�o�[�ɂȂ�����A1�{�^����������
	bool m_isGameEnd;
	// �S�[���ɓ����������ǂ����t���O
	bool m_isGoalHit;
};

