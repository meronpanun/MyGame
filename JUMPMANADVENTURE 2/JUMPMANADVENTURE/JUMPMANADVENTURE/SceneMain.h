#pragma once
#include "SceneStage1.h"
#include "SceneManager.h"
#include <memory>

class Player;
class BgStage1;
class Camera;
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

	std::shared_ptr<Camera> m_camera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
};

