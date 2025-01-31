#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Life.h"
#include "Goal.h"
#include "FontManager.h"
#include <memory>
#include <cassert>

namespace
{
	// ゲームオーバーの文字が表示されるまでのフレーム数
	constexpr int kGameoverFadeFrame = 60;

	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// タイマーの初期値
	constexpr int kInitialTimer = 400;
	// タイマーのカウントダウン間隔（0.4秒）
	constexpr int kTimerCountdownInterval = 24; // 60FPSの場合、0.4秒は24フレーム
	// タイマーとスコアの表示位置
	constexpr int kTimerPosX = 760;
	constexpr int kScorePosX = 480;
	constexpr int kScoreAndTimerPosY = 55;
	constexpr int kTimerPosX2 = 720;
	constexpr int kScorePosX2 = 420;
	constexpr int kScoreAndTimerPosY2 = 20;

	// 1000ピクセルの範囲
	constexpr float kEnemyActivationRange = 1000.0f; 

	// 体力の最大値
	constexpr int kMaxHp = 3;

	// 背景の1つのサイズ
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;

	// 音量
	constexpr int kVolumeBGM = 128;
	constexpr int kVolumeSE = 128;

	// 拡大率
	constexpr float kScale = 2.0f;

	// ゲームオーバー用敵の描画サイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// ゲームオーバー用敵の初期位置と落下速度
	constexpr float kGameOverEnemyStartPosY = -kGraphHeight * kScale;
	constexpr float kGameOverEnemyFallSpeedMin = 1.0f;
	constexpr float kGameOverEnemyFallSpeedMax = 3.0f;
	constexpr float kGameOverEnemyRotationSpeedMin = 0.02f;
	constexpr float kGameOverEnemyRotationSpeedMax = 0.1f;
	constexpr int kNumGameOverEnemies = 5;
}

SceneMain::SceneMain():
	m_isGameEnd(false),
	m_isGoalHit(false),
	m_fadeFrameCount(0),
	m_lifeHandle(-1),
	m_score(0), 
	m_timer(kInitialTimer),
	m_bgScrollY(0),
	m_gameOverEnemyPosY(kGameOverEnemyStartPosY),
	m_gameOverEnemyAngle(0.0f)
{
	// グラフィックの読み込み
	m_lifeHandle = LoadGraph("data/image/heart.png");
	assert(m_lifeHandle != -1);
	m_flagHandle = LoadGraph("data/image/flag.png");
	assert(m_flagHandle != -1);
	m_poleHandle = LoadGraph("data/image/pole.png");
	assert(m_poleHandle != -1);
	m_bgHandle = LoadGraph("data/image/Purple.png");
	assert(m_bgHandle != -1);
	m_playerDaedHandle = LoadGraph("data/image/PlayerDead.png");
	assert(m_playerDaedHandle != -1);

	//BGMの読み込み
//	m_bgmHandle = LoadSoundMem("data/MusMus-BGM-125.mp3");
//	assert(m_bgmHandle != -1);

	// SEの読み込み
//	m_seHandle = LoadSoundMem("data/決定ボタンを押す49.mp3");
//	assert(m_seHandle != -1);


	m_pGoal = std::make_shared<Goal>();
	m_pGoal->SetHandle(m_flagHandle);
	m_pGoal->SetPoleHandle(m_poleHandle);

	// 敵の生成数
	m_pEnemy.resize(20);

	// 各敵の初期位置
	CreateEnemy(1600, 625);
	CreateEnemy(2650, 625);
	CreateEnemy(3100, 625);
	CreateEnemy(3180, 625);
	CreateEnemy(4450, 200);
	CreateEnemy(4550, 200);
	CreateEnemy(5250, 625);
	CreateEnemy(5350, 625);
	CreateEnemy(5600, 625);
	CreateEnemy(5900, 625);
	CreateEnemy(6000, 625);
	CreateEnemy(6450, 625);
	CreateEnemy(6550, 625);
}

SceneMain::~SceneMain()
{
	// グラフィックの開放
	DeleteGraph(m_lifeHandle);
	DeleteGraph(m_flagHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_poleHandle);
	DeleteGraph(m_playerDaedHandle);
	//BGMを解放
	DeleteSoundMem(m_bgmHandle);
	// SEを解放
	DeleteGraph(m_seHandle);
}

void SceneMain::Init()
{
	
}

SceneBase* SceneMain::Update()
{


	// ゲームオーバー演出
	if (m_pPlayer->GetHp() <= 0 || m_timer <= 0)  // プレイヤーのHPが0または制限時間が0になった場合
	{
		// プレイヤーのゲームオーバーフラグを確認しタイマーが0になった場合
		if (m_pPlayer->IsGameOver() || m_timer <= 0)
		{
			// BGMを停止
		//	StopSoundMem(m_bgmHandle);
			m_gameoverFrameCount++;
			if (m_gameoverFrameCount > kGameoverFadeFrame)
			{
				m_gameoverFrameCount = kGameoverFadeFrame;

				// ゲームオーバーの文字が表示されきった後、
				// 1ボタンを押したらタイトルに戻る
				if (Pad::IsTrigger(PAD_INPUT_1))
				{
					m_isGameEnd = true;
				}
			}
			// 背景のスクロール位置を更新
			m_bgScrollY += 1; // スクロール速度を調整
			if (m_bgScrollY > Game::kScreenHeight)
			{
				m_bgScrollY = 0;
			}

			// ゲームオーバー用敵の位置と回転角度を更新
			UpdateGameOverEnemies();
		}
	}

	// ゴールオブジェクトに当たったら
	if (m_isGoalHit)
	{
		return new SceneGameClear(); 
		m_isGoalHit = true;
	}

	// 何もしなければシーン遷移しない(ステージ1画面のまま)
	return this;
}
	

void SceneMain::Draw()
{
	m_pBgStage1->Draw(); 
	m_pPlayer->Draw();
	m_pGoal->Draw();

	// 敵の描画
	for (auto& enemy : m_pEnemy)
	{
		if (enemy)
		{
			enemy->Draw();
		}
	}
	 
	// 体力の描画
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		m_life[i].Draw();
	}

	// スコアの表示
	DrawFormatStringToHandle(kScorePosX2, kScoreAndTimerPosY2, 0xffffff, m_pFont->GetFont(), "Score");
	DrawFormatStringToHandle(kScorePosX, kScoreAndTimerPosY, 0xffffff, m_pFont->GetFont(), "%d", m_score);

	// タイマーの表示
	DrawFormatStringToHandle(kTimerPosX2, kScoreAndTimerPosY2, 0xffffff, m_pFont->GetFont(), "Time");
	DrawFormatStringToHandle(kTimerPosX, kScoreAndTimerPosY, 0xffffff, m_pFont->GetFont(), "%d" , m_timer);

	// ゲームオーバーの演出の表示
	if (m_pPlayer->GetHp() <= 0 || m_timer <= 0) // プレイヤーのHPが0または制限時間が0になった場合
	{
		// プレイヤーのゲームオーバーフラグを確認しタイマーが0になった場合
		if (m_pPlayer->IsGameOver() || m_timer <= 0)
		{
			
			// 背景をスクロールして描画
			for (int y = m_bgScrollY - Game::kScreenHeight; y < Game::kScreenHeight; y += kChipHeight)
			{
				for (int x = 0; x < Game::kScreenWidth; x += kChipWidth)
				{
					DrawGraph(x, y,  m_bgHandle, true);
				}
			}

			// ゲームオーバー用敵の描画
			DrawGameOverEnemies();

			if (m_blinkFrameCount < kBlinkDispFrame)
			{
				DrawFormatStringToHandle(430, 600, 0xffffff, m_pFont->GetFont2(),"Press A Button");
			}

			// 割合を使用して変換を行う
			// m_gameoverFrameCount を進行割合に変換する
			float progressRate = static_cast<float>(m_gameoverFrameCount) / kGameoverFadeFrame;

			// 割合を実際の透明度に変換する
			int alpha = static_cast<int>(255 * progressRate);

			// ここ以降呼ばれるDraw関数の描画方法を変更する
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			int width = GetDrawStringWidthToHandle("GAMEOVER", strlen("GAMEOVER"), m_pFont->GetFont1());
			DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
				"GAMEOVER", 0xffffff, m_pFont->GetFont1());
			// 以降の表示がおかしくならないように元の設定に戻しておく
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	
	}

	// フェード処理
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

void SceneMain::CreateEnemy(float x, float y)
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])
		{
			m_pEnemy[i] = std::make_shared<Enemy>();
			m_pEnemy[i]->SetPos(x, y);
			break;
		}
	}
}

void SceneMain::SetScoreAndTimerFontSize(int size)
{
	m_scoreAndTimerFontSize = size;
}

void SceneMain::InitGameOverEnemies()
{
}

void SceneMain::UpdateGameOverEnemies()
{
}

void SceneMain::DrawGameOverEnemies()
{
}
