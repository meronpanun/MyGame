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

	// 敵の生成
	void CreateEnemy(float x, float y);

	// スコアのフォントサイズの設定
	void SetScoreFontSize(int size); 
	// タイマーのフォントサイズの設定
	void SetTimerFontSize(int size); 

private:
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<SceneMain> m_pSceneMain;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::vector<Life> m_life;

	// フェード処理
	int m_fadeFrameCount;
	// グラフィックハンドル
	int m_lifeHandle;
	int m_goalHandle;
	// フォントハンドル
	int m_fontHandle;
	// ゲームオーバー演出に使用するフレーム
	int m_gameoverFrameCount;
	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;

	// スコアとタイマーを管理するメンバ変数を追加
	int m_score;
	int m_timer;

	// スコアとタイマーのフォントサイズを管理するメンバ変数
	int m_scoreFontSize;
	int m_timerFontSize;

	// ゲームオーバーになった後、1ボタンを押した
	bool m_isGameEnd;
	// ゴールに当たったかどうかフラグ
	bool m_isGoalHit;
};

