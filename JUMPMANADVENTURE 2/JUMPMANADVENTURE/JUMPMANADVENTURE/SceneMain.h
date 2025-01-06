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
	void End();
	SceneManager::SceneSelect Update();
	void Draw();

	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// �Q�[���I�[�o�[���

private:
	// �t�F�[�h����
	int m_fadeFrameCount;

	// �O���t�B�b�N�n���h��
	int m_lifeHandle;

	// �V�[���ړ����邩 true:�V�[���ړ�����
	bool m_isSceneGameOver;	// �Q�[���I�[�o�[��ʂɈړ�

	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
//	std::shared_ptr<Life> m_pLife[3];
	Life m_life[3];
};

