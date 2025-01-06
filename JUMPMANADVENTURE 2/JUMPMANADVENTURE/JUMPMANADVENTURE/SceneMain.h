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
/// ゲーム画面クラス
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

	bool IsSceneGameOver() const { return m_isSceneGameOver; }	// ゲームオーバー画面

private:
	// フェード処理
	int m_fadeFrameCount;

	// グラフィックハンドル
	int m_lifeHandle;

	// シーン移動するか true:シーン移動する
	bool m_isSceneGameOver;	// ゲームオーバー画面に移動

	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
//	std::shared_ptr<Life> m_pLife[3];
	Life m_life[3];
};

