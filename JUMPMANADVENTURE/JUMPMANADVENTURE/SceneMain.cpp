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
#include <vector>

namespace
{
	// ゲームオーバーの文字が表示されるまでのフレーム数
	constexpr int kGameoverFadeFrame = 60;

	// ゲームオーバーの文字表示位置
	constexpr int kGameoverPosY = 900;

	// Press A Buttonの表示位置
	constexpr int kPressAButtonPosX = 430;
	constexpr int kPressAButtonPosY = 550;


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
	constexpr int kGraphWidth = 30;
	constexpr int kGraphHeight = 28;

	// ゲームオーバー用敵の初期位置と落下速度
	constexpr float kGameOverEnemyStartPosY = -kGraphHeight * kScale; // 画面外から出現
	constexpr float kGameOverEnemyFallSpeedMin = 1.0f; // 落下速度の最小値
	constexpr float kGameOverEnemyFallSpeedMax = 3.0f; // 落下速度の最大値
	constexpr float kGameOverEnemyRotationSpeedMin = 0.02f; // 回転速度の最小値
	constexpr float kGameOverEnemyRotationSpeedMax = 0.1f;  // 回転速度の最大値
	constexpr int kNumGameOverEnemies = 10; // ゲームオーバー用敵の数
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
	m_gameOverEnemyAngle(0.0f),
	m_gameOverFrameCount(0),
	m_isAddingScore(false),
	m_bonusScore(0)
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
	m_enemyHandle = LoadGraph("data/image/Enemy.png");
	assert(m_enemyHandle != -1);

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

	// ゲームオーバー用敵の初期化
	InitGameOverEnemies();
}

SceneMain::~SceneMain()
{
	// グラフィックの開放
	DeleteGraph(m_lifeHandle);
	DeleteGraph(m_flagHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_poleHandle);
	DeleteGraph(m_enemyHandle);
	//BGMを解放
	DeleteSoundMem(m_bgmHandle);
	// SEを解放
	DeleteGraph(m_seHandle);
}

void SceneMain::Init()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>();
	m_pCamera = std::make_shared<Camera>();
	m_pFont = std::make_shared<FontManager>();

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

	// BGMの再生開始（ループ再生）
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	// スコアとタイマーの初期化
	m_score = 0;
	m_timer = kInitialTimer;
}

SceneBase* SceneMain::Update()
{
	ChangeVolumeSoundMem(kVolumeBGM, m_bgmHandle);
	ChangeVolumeSoundMem(kVolumeSE, m_seHandle);


	// ゴールに当たったかどうかをチェック
	if (m_pGoal->GetHitPlayerFlag(m_pPlayer))
	{
		m_isGoalHit = true;
		m_pPlayer->DisableControl(); // プレイヤーの操作を無効化
	}

	// ゴールに当たっていない場合のみプレイヤーのUpdateを呼び出す
	if (!m_isGoalHit)
	{
		m_pPlayer->Update();
	}

	if (m_isGameEnd)
	{
		// ゲームオーバーになった後1ボタンを押したらフェードアウト
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return new SceneTitle();
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

	m_pBgStage1->Update(m_pPlayer.get());
	m_pCamera->Update(m_pPlayer.get());
	m_pGoal->Update();

	// プレイヤーが死亡状態でない場合のみ敵の更新とタイマーの更新を行う
	if (m_pPlayer->GetHp() > 0)
	{
		// 敵の更新
		Vec2 playerPos = m_pPlayer->GetPos();
		for (auto& enemy : m_pEnemy)
		{
			if (enemy && enemy->IsAlive())
			{
				if (enemy->IsPlayerInRange(playerPos, kEnemyActivationRange))
				{
					enemy->Activate(); // 敵をアクティブにする
				}
				if (enemy->IsActive())
				{
					enemy->Update();   // アクティブな敵を更新
				}
			}
		}

		// タイマーのカウントダウン
		static int timerFrameCount = 0;
		timerFrameCount++;
		if (timerFrameCount >= kTimerCountdownInterval)
		{
			timerFrameCount = 0;
			if (m_timer > 0)
			{
				m_timer--;
			}
		}

		// 体力の更新
		for (int i = 0; i < m_life.size(); i++)
		{
			m_life[i].Update();
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
						enemy->SetAlive(false);    // 敵を消す
						m_pPlayer->JumpOnEnemy();  // プレイヤーが少しジャンプ
						m_score += 100;            // 敵を倒すとスコアを100ポイント増加
						// SEを再生
					//	PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
					}
					else
					{
						m_pPlayer->OnDamage();	   // プレイヤーがダメージを受ける
					}
				}
			}
		}
		
	}

	// 1秒サイクルで表示、非表示切り替えす
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// ゲームオーバー演出
	if (m_pPlayer->GetHp() <= 0 || m_timer <= 0)  // プレイヤーのHPが0または制限時間が0になった場合
	{
		// プレイヤーのゲームオーバーフラグを確認しタイマーが0になった場合
		if (m_pPlayer->IsGameOver() || m_timer <= 0)
		{
			// BGMを停止
		//	StopSoundMem(m_bgmHandle);
			m_gameOverFrameCount++;
			if (m_gameOverFrameCount > kGameoverFadeFrame)
			{
				m_gameOverFrameCount = kGameoverFadeFrame;

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
		if (!m_isAddingScore)
		{
			m_score += m_timer * 10; // タイマーの値をそのままスコアに加算
			m_isAddingScore = true;
		}

		// スコアとタイマーを渡してシーン遷移
		return new SceneGameClear(m_score, m_timer);
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
				DrawFormatStringToHandle(kPressAButtonPosX, kPressAButtonPosY, 0xffffff, m_pFont->GetFont2(),"Press A Button");
			}

			// 割合を使用して変換を行う
			float progressRate = static_cast<float>(m_gameOverFrameCount) / (kGameoverFadeFrame * 4);

			// 割合を実際の透明度に変換する
			int alpha = static_cast<int>(255 * (static_cast<float>(m_gameOverFrameCount) / kGameoverFadeFrame));

			// ここ以降呼ばれるDraw関数の描画方法を変更する
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

			// ゲームオーバーの文字の位置を計算
			int width = GetDrawStringWidthToHandle("GAMEOVER", strlen("GAMEOVER"), m_pFont->GetFont1());
			int targetY = kGameoverPosY; // ゲームオーバーの文字の位置
			int startY = -4; // 画面外から出現
			int gameOverY = static_cast<int>(startY + (targetY - startY) * progressRate); // 途中の位置を計算

			// 文字が画面中央に来るように調整
			if (gameOverY > targetY) {
				gameOverY = targetY;
			}

			// ゲームオーバーの文字を描画
			DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, gameOverY,
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

// 敵の生成
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

// スコアとタイマーのフォントサイズの設定
void SceneMain::SetScoreAndTimerFontSize(int size)
{
	m_scoreAndTimerFontSize = size;
}

// ゲームオーバー用敵の初期化
void SceneMain::InitGameOverEnemies()
{
	for (int i = 0; i < kNumGameOverEnemies; ++i) 
	{
		GameOverEnemy enemy; 
		enemy.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // x座標をランダムに設定
		enemy.pos.y = kGameOverEnemyStartPosY; // y座標を初期位置に設定
		enemy.fallSpeed = kGameOverEnemyFallSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameOverEnemyFallSpeedMax - kGameOverEnemyFallSpeedMin)));                 // 落下速度をランダムに設定
		enemy.rotationSpeed = kGameOverEnemyRotationSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameOverEnemyRotationSpeedMax - kGameOverEnemyRotationSpeedMin))); // 回転速度をランダムに設定
		enemy.angle = 0.0f; // 回転角度を初期化
		m_gameOverEnemies.push_back(enemy); 
	}
}

// ゲームオーバー用敵の更新
void SceneMain::UpdateGameOverEnemies()
{
	for (auto& enemy : m_gameOverEnemies)
	{
		enemy.pos.y += enemy.fallSpeed;        // 落下速度分下に移動
		enemy.angle += enemy.rotationSpeed;    // 回転角度を更新
		if (enemy.pos.y > Game::kScreenHeight) // 画面外に出たら
		{
			enemy.pos.y = kGameOverEnemyStartPosY; // 初期位置に戻す
			enemy.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // x座標をランダムに設定
		}
	}
}

// ゲームオーバー用敵の描画
void SceneMain::DrawGameOverEnemies()
{
	for (const auto& enemy : m_gameOverEnemies)
	{
		DrawRotaGraph(enemy.pos.x, enemy.pos.y, kScale, enemy.angle, m_enemyHandle, true);
	}
}
