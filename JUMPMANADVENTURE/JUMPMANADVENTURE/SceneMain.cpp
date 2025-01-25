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
	m_goalHandle = LoadGraph("data/image/GoalFlag.png");
	assert(m_lifeHandle != -1);

	m_pGoal = std::make_shared<Goal>();
	m_pGoal->SetHandle(m_goalHandle);

	// 敵の生成数
	m_pEnemy.resize(12);

	// 各敵の初期位置
	CreateEnemy(750, 650);
	CreateEnemy(1450, 650);
	CreateEnemy(1650, 650);
	CreateEnemy(1680, 650);
	CreateEnemy(2880, 350);
	CreateEnemy(2890, 350);
}

SceneMain::~SceneMain()
{
	// グラフィックの開放
	DeleteGraph(m_lifeHandle);
	DeleteGraph(m_goalHandle);
	// フォントの開放
	DeleteFontToHandle(m_fontHandle);
}

void SceneMain::Init()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>(); 
	m_pCamera = std::make_shared<Camera>(); 

	m_pPlayer->Init(m_pCamera.get()); 
	m_pBgStage1->Init(m_pCamera.get());
	m_pCamera->Init();
	m_pGoal->Init(m_pCamera.get());

	// 敵の初期化
	for (auto& enemy : m_pEnemy)
	{
		if (enemy)
		{
			enemy->Init(m_pCamera.get());
		}
	}

	// 体力の初期化
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
	m_pGoal->Update();

	// 敵の更新
	for (auto& enemy : m_pEnemy)
	{
		if (enemy)
		{
			enemy->Update();
		}
	}

	// 体力の更新
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
	for (auto& enemy : m_pEnemy)
	{
		if (enemy && enemy->IsAlive())
		{
			bool isPlayerHit = true;
			// 絶対に当たらないパターン
			if (m_pPlayer->GetLeft() > enemy->GetRigth())
			{
				isPlayerHit = false;
			}
			if (m_pPlayer->GetTop() > enemy->GetBottom())
			{
				isPlayerHit = false;
			}
			if (m_pPlayer->GetRigth() < enemy->GetLeft())
			{
				isPlayerHit = false;
			}
			if (m_pPlayer->GetBottom() < enemy->GetTop())
			{
				isPlayerHit = false;
			}

			// isPlayerHit = trueなら当たっている、falseなら当たっていない
			if (isPlayerHit)
			{
				if (m_pPlayer->GetBottom() < enemy->GetTop() + 50 && m_pPlayer->GetMoveY() > 0) // プレイヤーが敵の上に当たった場合
				{
					enemy->SetAlive(false); // 敵を消す
					m_pPlayer->JumpOnEnemy();  // プレイヤーが少しジャンプ
				}
				else
				{
					m_pPlayer->OnDamage(); // プレイヤーがダメージを受ける
				}
			}
		}
	}
	
	// ゴールオブジェクトに当たったら
	if (m_isGoalHit)
	{
		return SceneManager::kSceneGameClear; 
		m_isGoalHit = true; 
	}

	// 何もしなければシーン遷移しない(ステージ1画面のまま)
	return SceneManager::SceneSelect::kSceneStage1;
}

void SceneMain::Draw()
{
	m_pBgStage1->Draw(); 
	m_pPlayer->Draw();
	m_pGoal->Draw();

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
		int alpha = static_cast<int>(255 * progressRate);

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

void SceneMain::CreateEnemy(float x, float y)
{
	constexpr float enemySpawnRange = 10.0f; // 例として200ピクセルの範囲

	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])
		{
			m_pEnemy[i] = std::make_shared<Enemy>(); 
			m_pEnemy[i]->SetPos(x, y);
			break;
		}

		if (IsPlayerInRange(x, y, enemySpawnRange))
		{
			m_pEnemy[i] = std::make_shared<Enemy>();
			m_pEnemy[i]->SetPos(x, y);
			break;
		}
	}
}

bool SceneMain::IsPlayerInRange(float x, float y, float range)
{
	Vec2 playerPos = m_pPlayer->GetPos();
	Vec2 enemyPos(x, y);
	return (playerPos - enemyPos).Length() <= range;
}
