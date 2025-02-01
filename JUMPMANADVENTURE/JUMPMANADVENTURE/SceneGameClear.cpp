#include "SceneGameClear.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include "FontManager.h"
#include "SceneTitle.h"
#include <cassert>
#include <vector>
#include <string>

namespace
{
	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// フェード
	constexpr int kFadeFrame = 8;
	// 最大フェード量
	constexpr int kFadeMax = 255;

	// ゲームクリアの文字が表示されるまでのフレーム数
	constexpr int kGameClearFadeFrame = 60;

	// 背景の1つのサイズ
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;

	// ゲームクリア用敵の描画サイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// 拡大率
    constexpr float kScale = 2.0f; 

	// ゲームクリア用敵の初期位置と落下速度
	constexpr float kGameClearPlayerStartPosY = -kGraphHeight * kScale; // 画面外から落下してくる
	constexpr float kGameClearPlayerFallSpeedMin = 1.0f; // 落下速度の最小値
	constexpr float kGameClearPlayerFallSpeedMax = 3.0f; // 落下速度の最大値
	constexpr float kGameClearPlayerRotationSpeedMin = 0.02f; // 回転速度の最小値
	constexpr float kGameClearPlayerRotationSpeedMax = 0.1f;  // 回転速度の最大値
	constexpr int kNumGameClearPlayrers = 10; // ゲームクリア用敵の数

	// ウェーブアニメーションのパラメータ
	constexpr float kWaveAmplitude = 20.0f; // 振幅
	constexpr float kWaveFrequency = 0.1f;  // ウェーブの頻度
}

SceneGameClear::SceneGameClear(int score, int goalHitTime) :
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameClearFrameCount(0),
	m_bgScrollY(0),
	m_gameClearPlayerPosY(kGameClearPlayerStartPosY),
	m_gameClearPlayerAngle(0.0f),
	m_waveFrameCount(0),
	m_score(score),
	m_goalHitTime(goalHitTime)
{
	// グラフィックの読み込み
	m_gameClearBgHandle = LoadGraph("data/image/Yellow.png");
	assert(m_gameClearBgHandle != -1);
	m_gameClearPlayerHandle = LoadGraph("data/image/Player.png");
	assert(m_gameClearPlayerHandle != -1);

	// ゲームクリア用プレイヤーの初期化
	InitGameClearPlayers();
}

SceneGameClear::~SceneGameClear()
{
	// グラフィックの開放
	DeleteGraph(m_gameClearBgHandle);
	DeleteGraph(m_gameClearPlayerHandle);
}

void SceneGameClear::Init()
{
	m_pFont = std::make_shared<FontManager>();
}

SceneBase* SceneGameClear::Update()
{
	// フェードイン処理
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	// ゲームクリア演出
	m_gameClearFrameCount++;
	if (m_gameClearFrameCount > kGameClearFadeFrame)
	{
		m_gameClearFrameCount = kGameClearFadeFrame;
	}

	// 1秒サイクルで表示、非表示切り替えす
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// 背景のスクロール位置を更新
	m_bgScrollY -= 1; // スクロール速度を調整
	if (m_bgScrollY > Game::kScreenHeight)
	{
		m_bgScrollY = 0;
	}

	// ゲームクリア用プレイヤーの位置と回転角度を更新
	UpdateGameClearPlayers();

	// ウェーブアニメーションのフレームカウントを更新
	m_waveFrameCount++;

	// ZorAキーを押したらタイトル画面に移行
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return new SceneTitle();
	}
	// 何もしなければシーン遷移しない(クリア画面のまま)
	return this;
}

void SceneGameClear::Draw()
{
	// 背景をスクロールして描画
	for (int y = m_bgScrollY - Game::kScreenHeight; y < Game::kScreenHeight; y += kChipHeight)
	{
		for (int x = 0; x < Game::kScreenWidth; x += kChipWidth)
		{
			DrawGraph(x, y, m_gameClearBgHandle, true);
		}
	}

	// ゲームクリア用プレイヤーの描画
	DrawGameClearPlayers();

	// 割合を使用して変換を行う
   	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// 割合を実際の透明度に変換する
	int alpha = static_cast<int>(255 * progressRate);
	// ここ以降呼ばれるDraw関数の描画方法を変更する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", strlen("GAMECLEAR"), m_pFont->GetFont1());

	// ウェーブアニメーションを適用して文字を描画
	const int charSpacing = 60;     // 文字間隔を広げるためのスペース
	const int specialSpacing = 100; // MとEの間隔を広げるためのスペース
	int xOffset = -50;              // 文字のX座標のオフセット

	for (int i = 0; i < strlen("GAMECLEAR"); ++i)
	{
		float waveOffset = kWaveAmplitude * std::sin((m_waveFrameCount + i * 10) * kWaveFrequency); // ウェーブアニメーションのオフセット
		DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5 + xOffset, 100 + waveOffset,
			std::string(1, "GAMECLEAR"[i]).c_str(), 0xffffff, m_pFont->GetFont1());

		// 次の文字の位置を計算
		if (i == 2) // Mの後
		{
			xOffset += specialSpacing;
		}
		else
		{
			xOffset += charSpacing;
		}
	}

	// スコアの表示
	DrawFormatStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, 300, 0xffffff, m_pFont->GetFont1(), "Score: %d", m_score);

	// タイマーの表示
	DrawFormatStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, 400, 0xffffff, m_pFont->GetFont1(), "Time: %d", m_goalHitTime);

	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(400, 600, 0xffffff, m_pFont->GetFont2(), "Press A Button");
	}

	// 以降の表示がおかしくならないように元の設定に戻しておく
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// フェード処理
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

// ゲームオーバー用敵の初期化
void SceneGameClear::InitGameClearPlayers()
{
	for (int i = 0; i < kNumGameClearPlayrers; ++i)
	{
		GameClearPlayer Player;
		Player.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // 画面内のランダムな位置
		Player.pos.y = kGameClearPlayerStartPosY; // 画面外から出現
		Player.fallSpeed = kGameClearPlayerFallSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameClearPlayerFallSpeedMax - kGameClearPlayerFallSpeedMin))); // 落下速度
		Player.rotationSpeed = kGameClearPlayerRotationSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameClearPlayerRotationSpeedMax - kGameClearPlayerRotationSpeedMin))); // 回転速度
		Player.angle = 0.0f; // 初期角度
		m_gameClearPlayers.push_back(Player);	
	}
}

// ゲームオーバー用敵の更新
void SceneGameClear::UpdateGameClearPlayers()
{
	for (auto& Player : m_gameClearPlayers)
	{
		Player.pos.y += Player.fallSpeed;       // 落下
		Player.angle += Player.rotationSpeed;   // 回転
		if (Player.pos.y > Game::kScreenHeight) // 画面外に出たら再配置
		{
			Player.pos.y = kGameClearPlayerStartPosY; // 画面外から出現
			Player.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // 画面内のランダムな位置
		} 
	}
}

// ゲームオーバー用敵の描画
void SceneGameClear::DrawGameClearPlayers()
{
	for (const auto& enemy : m_gameClearPlayers)
	{
		DrawRotaGraph(enemy.pos.x, enemy.pos.y, kScale, enemy.angle, m_gameClearPlayerHandle, true);
	}
}
