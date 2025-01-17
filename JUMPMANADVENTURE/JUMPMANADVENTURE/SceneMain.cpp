#include "SceneMain.h"
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
#include <memory>
#include <cassert>

namespace
{
	// ゲームオーバーの文字が表示されるまでのフレーム数
	constexpr int kGameoverFadeFrame = 60;

	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// 体力の最大値
	constexpr int kMaxHp = 3;
}

SceneMain::SceneMain():
	m_isGoalHit(false),
	m_fadeFrameCount(0),
	m_lifeHandle(-1)
{
	// フォントの生成
	m_fontHandle = CreateFontToHandle("Bodoni MT Black", 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	// グラフィックの読み込み
	m_lifeHandle = LoadGraph("data/image/life.png");
	assert(m_lifeHandle != -1);
	// ゴールのグラフィックの読み込み
	m_goalHandle = LoadGraph("data/image/GoalFlag.png");
	assert(m_lifeHandle != -1);

	m_pGoal = std::make_shared<Goal>();
	m_pGoal->SetHandle(m_goalHandle);
}

SceneMain::~SceneMain()
{
	DeleteGraph(m_lifeHandle);
	DeleteGraph(m_goalHandle);
	DeleteFontToHandle(m_fontHandle);
}

void SceneMain::Init()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>();
	m_pCamera = std::make_shared<Camera>();
	m_pEnemy = std::make_shared<Enemy>();

	m_pPlayer->Init(m_pCamera.get());
	m_pBgStage1->Init(m_pCamera.get());
	m_pCamera->Init();
	m_pEnemy->Init();
	m_pGoal->Init(m_pCamera.get());

	m_life.resize(kMaxHp);
	for (int i = 0; i < m_life.size(); i++)
	{
		m_life[i].Init();
		m_life[i].SetHandle(m_lifeHandle);
		m_life[i].SetIndex(i);
	}
}

SceneManager::SceneSelect SceneMain::Update()
{
	m_isGoalHit = m_pGoal->GetHitPlayerFlag(m_pPlayer);

	if (m_isGameEnd)
	{
		// ゲームオーバーになった後1ボタンを押したらフェードアウト
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::kSceneTitle;
		}
	}
	// ゴールオブジェクトに当たったら
	else if (m_isGoalHit)
	{
		//  ゴールオブジェクトに当たった後1ボタンを押したらフェードアウト
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			m_isGoalHit = true;
			return SceneManager::kSceneGameClear;
		}
	}
	else
	{
		// フェードイン処理
		m_fadeFrameCount++;
		if (m_fadeFrameCount > 30)
		{
			m_fadeFrameCount = 30;
		}
	}

	m_pPlayer->Update();
	m_pBgStage1->Update(m_pPlayer.get());
	m_pCamera->Update(m_pPlayer.get());
	m_pEnemy->Update();
	m_pGoal->Update();
//	Pad::Update();

	for (int i = 0; i < m_life.size(); i++)
	{
		m_life[i].Update();
	}

	// ゲームオーバー演出
	if (m_pPlayer->GetHp() <= 0)
	{
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
	}

	// 1秒サイクルで表示、非表示切り替えす
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// プレイヤーと敵の当たり判定
	bool isPlayerHit = true;

	if (m_pPlayer->GetLeft() > m_pEnemy->GetRigth())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetTop() > m_pEnemy->GetBottom())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetRigth() < m_pEnemy->GetLeft())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetBottom() < m_pEnemy->GetTop())
	{
		isPlayerHit = false;
	}

	// isPlayerHit = trueなら当たっている、falseなら当たっていない
	if (isPlayerHit)
	{
		m_pPlayer->OnDamage();
	}

	// ゴールオブジェクトに当たったら
	//if (m_isGoalHit)
	//{
	//	return SceneManager::kSceneGameClear;
	//	m_isGoalHit = true;
	//}

	// 何もしなければシーン遷移しない(ステージ1画面のまま)
	return SceneManager::SceneSelect::kSceneStage1;
}

void SceneMain::Draw()
{
	m_pBgStage1->Draw();
	m_pPlayer->Draw();
	m_pEnemy->Draw();
	m_pGoal->Draw();

	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		m_life[i].Draw();
	}

	// ゲームオーバーの表示
	if (m_pPlayer->GetHp() <= 0)
	{
		// 画面全体を黒色で塗り潰す
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

		if (m_blinkFrameCount < kBlinkDispFrame)
		{
			DrawString(580, 600, "Press A Button", 0xffffff);
		}

		// 割合を使用して変換を行う
		// m_gameoverFrameCount を進行割合に変換する
		float progressRate = static_cast<float>(m_gameoverFrameCount) / kGameoverFadeFrame;

		// 割合を実際の透明度に変換する
		int alpha = static_cast<float>(255 * progressRate);

		// ここ以降呼ばれるDraw関数の描画方法を変更する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		int width = GetDrawStringWidthToHandle("GAMEOVER", strlen("GAMEOVER"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
			"GAMEOVER", 0xffffff, m_fontHandle);
		// 以降の表示がおかしくならないように元の設定に戻しておく
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
