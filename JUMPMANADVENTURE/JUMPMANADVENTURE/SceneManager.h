#pragma once
#include "SceneBase.h"

class SceneStage1;
class SceneTitle;
class SceneMain;
class SceneGameClear;
/// <summary>
/// �V�[���Ǘ��N���X
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();

	// �Q�[���N���A��ʂւ̑J�ڂ��J�n
	void StartGameClear();

private:
	SceneBase* m_pCurrentScene;
	SceneBase* m_pNextScene;

	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneMain* m_pSceneMain;
	SceneGameClear* m_pGameClear;
	
	// �Q�[���N���A�������ǂ���
	bool m_isGameClear;

	// �X�R�A�^�C�}�[
	int m_score;
	int m_timer;
	int m_bonusTimer;

	// �v���C���[���_���[�W�������H���Ȃ��������ǂ����̃t���O
	bool m_isNoDamage;
};

