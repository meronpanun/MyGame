#pragma once
#include "SceneManager.h"
#include "Life.h"
#include <memory>

class Player;
class BgStage1;
class Camera;
//class Life;
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
	// �t�H���g�n���h��
	int m_fontHandle;
	// �Q�[���I�[�o�[���o�Ɏg�p����t���[��
	int m_gameoverFrameCount;
	// �Q�[���I�[�o�[�ɂȂ�����A1�{�^����������
	bool m_isGameEnd;


	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<SceneMain> m_pSceneMain;
	Life m_life[3];
};

