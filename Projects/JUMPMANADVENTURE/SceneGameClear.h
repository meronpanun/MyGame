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
	SceneGameClear(int score, int goalHitTime, bool isNoDamage);
	~SceneGameClear();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

	// シーン選択フラグの取得
	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// ゲームクリア用プレイヤーの初期化
	void InitGameClearPlayers();
	// ゲームクリア用プレイヤーの更新
	void UpdateGameClearPlayers();
	// ゲームオクリア用プレイヤーの描画
	void DrawGameClearPlayers();

private:
	// ゲームクリア用プレイヤーの情報
	struct GameClearPlayer
	{
		Vec2 pos;
		float fallSpeed = 0.0f;     // 落下速度
		float rotationSpeed = 0.0f; // 回転速度
		float angle = 0.0f;         // 回転角度
	};

	std::vector<GameClearPlayer> m_gameClearPlayers;
	// フォント管理
	std::shared_ptr<FontManager> m_pFont;

	// クリアシーンのグラフィックハンドル
	int m_gameClearBgHandle;
	int m_gameClearPlayerHandle;
	// エフェクトのグラフィックハンドル
	int m_effectHandle;
	// BGM
	int m_bgmHandle;
	// SE
	int m_seHandle;

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

	// プレイヤーがダメージを一回も食らわなかったかどうかのフラグ
	bool m_isNoDamage;
};

