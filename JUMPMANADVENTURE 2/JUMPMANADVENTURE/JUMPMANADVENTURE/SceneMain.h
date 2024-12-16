#pragma once
#include "SceneStage1.h"
#include "SceneManager.h"
#include "Player.h"
#include "BgStage1.h"

/// <summary>
/// ゲーム画面クラス
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
	// フェード処理
	int m_fadeFrameCount;

	BgStage1 m_bgStage1;
	Player m_player;
};

