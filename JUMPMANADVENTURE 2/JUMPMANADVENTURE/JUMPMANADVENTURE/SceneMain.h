#pragma once
#include "SceneStage1.h"
#include "SceneManager.h"
#include "Player.h"
#include "BgStage1.h"

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

protected:
	BgStage1 m_bgStage1;
	Player* m_player;
};

