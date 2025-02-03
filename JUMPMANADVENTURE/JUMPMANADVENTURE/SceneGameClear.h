#pragma once
#include "SceneBase.h"
#include <memory>
#include "Vec2.h"
#include <vector>

class FontManager;
/// <summary>
///　ゲームクリアシーンクラス
/// </summary>
class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(int score, int goalHitTime, int bonusTimer);
	~SceneGameClear();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// ゲームオーバー用敵の情報
	struct GameClearPlayer
	{
		Vec2 pos; 
		float fallSpeed;	 // 落下速度
		float rotationSpeed; // 回転速度
		float angle;		 // 回転角度
	};
	std::vector<GameClearPlayer> m_gameClearPlayers;
	// ゲームオーバー用敵の初期化
	void InitGameClearPlayers();
	// ゲームオーバー用敵の更新
	void UpdateGameClearPlayers();
	// ゲームオーバー用敵の描画
	void DrawGameClearPlayers();

private:
	// フォント管理
	std::shared_ptr<FontManager> m_pFont;
	// クリアシーンのグラフィックハンドル
	int m_gameClearBgHandle;
	int m_gameClearPlayerHandle;

	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;

	// ゲームクリア演出に使用するフレーム
	int m_gameClearFrameCount;

	// フェード処理
	int m_fadeFrameCount;
	
	// シーン選択フラグ true:シーン遷移
	bool m_isSceneTitle;// タイトル

	// 背景のスクロール
	int m_bgScrollY;

    // ゲームオーバー用敵の位置と回転角度
	float m_gameClearPlayerPosY;
	float m_gameClearPlayerAngle;

	// ウェーブのフレームカウント
	int m_waveFrameCount;
	
	// スコアとタイマー
	int m_score;
	int m_goalHitTime;
	int m_bonusTimer;
};

