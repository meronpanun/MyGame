#pragma once
#include "SceneBase.h"
#include "FontManager.h"
#include "Life.h"
#include "Vec2.h"
#include <vector>
#include <memory>

class ItemHp;
class FontManager;
class Player;
class BgStage;
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

	// アイテムの生成
	void CreateItemHp(float x, float y);

	// スコアとタイマーのフォントサイズの設定
	void SetScoreAndTimerFontSize(int size); 

	// ゲームオーバー用敵の情報
	struct GameOverEnemy
	{
		Vec2 pos;
		float fallSpeed = 0;     // 落下速度
		float rotationSpeed = 0; // 回転速度
		float angle = 0;		 // 回転角度
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
	std::shared_ptr<BgStage> m_pBgStage;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Goal> m_pGoal;
	std::vector<std::shared_ptr<Enemy>> m_pEnemy;
	std::vector<Life> m_life;
	std::vector<std::shared_ptr<ItemHp>> m_pItemHp;
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
	// エフェクトのグラフィックハンドル
	int m_effectHandle;
	// BGM
	int m_bgmHandle;
	int m_noTimeBGMHandle;
	// SE
	int m_seHandle;
	int m_enemyDeadSEHandle;
	int m_gameOverBGMHandle;
	int m_pressAButtonSEHandle;

	// ゲームオーバー演出に使用するフレーム
	int m_gameOverFrameCount;
	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;

	// スコアとタイマーを管理
	int m_score;
	int m_timer;
	// スコアに加算する用のタイマー
	int m_bonusTimer; 

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

	// タイマーをスコアに加算
	bool m_isAddingScore;
	int m_bonusScore;

	// ゴールに当たった時間
	int m_goalHitTime;
	// ゴール後の画面遷移までの待機時間（フレーム数）
	int m_goalTransitionTimer;

	// BGMの音量
	int m_bgmVolume; 
	// BGMがフェードアウト中かどうかを示すフラグ
	bool m_isBgmFadingOut;
	// BGMのフェードアウトのフレームカウント
	int m_bgmFadeOutFrameCount; 
	// ノータイムBGMが再生中かどうかを示すフラグ
	bool m_isHurryUpBGMPlaying;
	//  ノータイムBGMのフェードアウト中かどうかを示すフラグ
	bool m_isNoTimeBgmFadingOut; 
	// ノータイムBGMのフェードアウトのフレームカウント
	int m_noTimeBgmFadeOutFrameCount;

	// タイマーの減算速度
	float m_timerDecrementSpeed;
	// ゴール時のタイマーの値
	int m_goalTimer; 
	// タイマー減算開始を制御
	int m_timerDecrementStartCount; 
	// ゴール時のタイマー減算中フラグ
	bool m_isGoalTimerDecrementing; 

	// プレイヤーがダメージを一回も食らわなかったかどうかのフラグ
	bool m_isNoDamage;

	// アニメーションの進行
	int m_animFrame;
};

