#pragma once
#include "SceneBase.h"
#include "Life.h"
#include <memory>
#include <vector>
#include "Vec2.h"

class FontManager;
class Player;
class BgStage1;
class Camera;
class Goal;
class Enemy;
/// <summary>
/// ゲーム画面クラス
/// </summary>
class SceneMain : public SceneBase
{
public:
	SceneMain();
	~SceneMain();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

private:
	// 敵の生成
	void CreateEnemy(float x, float y);

	// スコアとタイマーのフォントサイズの設定
	void SetScoreAndTimerFontSize(int size); 

	// ゲームオーバー用敵の情報
	struct GameOverEnemy
	{
		Vec2 pos;
		float fallSpeed;     // 落下速度
		float rotationSpeed; // 回転速度
		float angle;		 // 回転角度
	};
	std::vector<GameOverEnemy> m_gameOverEnemies;
	// ゲームオーバー用敵の初期化
	void InitGameOverEnemies();
	// ゲームオーバー用敵の更新
	void UpdateGameOverEnemies();
	// ゲームオーバー用敵の描画
	void DrawGameOverEnemies();

private:
	std::shared_ptr<Camera> m_pCamera;
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<SceneMain> m_pSceneMain;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::vector<Life> m_life;
	// フォント管理
	std::shared_ptr<FontManager> m_pFont;

	// フェード処理
	int m_fadeFrameCount;

	// グラフィックハンドル
	int m_lifeHandle;
	int m_flagHandle;
	int m_poleHandle;
	int m_bgHandle;
	int m_enemyHandle;
	// ゲームシーン用BGMハンドル
	int m_bgmHandle;
	// ゲームシーン用SEハンドル
	int m_seHandle;

	// ゲームオーバー演出に使用するフレーム
	int m_gameOverFrameCount;
	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;

	// スコアとタイマーを管理するメンバ変数を追加
	int m_score;
	int m_timer;

	// スコアとタイマーのフォントサイズを管理するメンバ変数
	int m_scoreAndTimerFontSize;

	// ゲームオーバーになった後、1ボタンを押した
	bool m_isGameEnd;
	// ゴールに当たったかどうかフラグ
	bool m_isGoalHit;

	// 背景のスクロール位置
	int m_bgScrollY;

	// ゲームオーバー用敵の位置と回転角度
	float m_gameOverEnemyPosY;
	float m_gameOverEnemyAngle;

	// タイマーをスコアに加算するためのメンバー変数
	bool m_isAddingScore;
	int m_bonusScore;

	// ゴールに当たった時間
	int m_goalHitTime;
};

