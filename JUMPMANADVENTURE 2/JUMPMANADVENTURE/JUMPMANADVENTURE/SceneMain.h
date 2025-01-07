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
	SceneManager::SceneSelect Update();
	void Draw();

private:
	// フェード処理
	int m_fadeFrameCount;
	// グラフィックハンドル
	int m_lifeHandle;
	// フォントハンドル
	int m_fontHandle;
	// ゲームオーバー演出に使用するフレーム
	int m_gameoverFrameCount;
	// ゲームオーバーになった後、1ボタンを押した
	bool m_isGameEnd;


	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Enemy> m_pEnemy;
	std::shared_ptr<SceneMain> m_pSceneMain;
	Life m_life[3];
};

