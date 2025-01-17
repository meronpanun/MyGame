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

private:
	// �t�F�[�h����
	int m_fadeFrameCount;
	// �O���t�B�b�N�n���h��
	int m_lifeHandle;
	int m_goalHandle;
	// �t�H���g�n���h��
	int m_fontHandle;
	// �Q�[���I�[�o�[���o�Ɏg�p����t���[��
	int m_gameoverFrameCount;
	// �Q�[���I�[�o�[�ɂȂ�����A1�{�^����������
	bool m_isGameEnd;
	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;
	// �S�[���ɓ����������ǂ����t���O
	bool m_isGoalHit;

	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<SceneMain> m_pSceneMain;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<Life> m_life;
};

