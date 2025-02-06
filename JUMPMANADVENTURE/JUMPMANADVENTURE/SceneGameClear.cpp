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

	// 音量
	constexpr int kVolumeBGM = 128;
	constexpr int kVolumeSE = 128;

	// スコアの表示位置
	constexpr int kScoreTextPosX = 480;
	constexpr int kScoreNumberPosX = 710;
	constexpr int kScorePosY = 300;

	// タイムの表示位置
	constexpr int kTimeTextPosX = 470;
	constexpr int kTimeNumberPosX = 730;
	constexpr int kTimePosY = 400;

	// スコアランクの表示位置
	constexpr int kRankTextPosX = 120;
	constexpr int kRankTextPosY = 400;

	// RANKの表示位置
	constexpr int kRankPosX = 50;
	constexpr int kRankPosY = 300;

	// Press A Buttonの表示位置
	constexpr int kPressAButtonPosX = 380;
	constexpr int kPressAButtonPosY = 600;
}

SceneGameClear::SceneGameClear(int score, int goalHitTime, bool isNoDamage) :
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameClearFrameCount(0),
	m_bgScrollY(0),
	m_gameClearPlayerPosY(kGameClearPlayerStartPosY),
	m_gameClearPlayerAngle(0.0f),
	m_waveFrameCount(0),
	m_score(score),
	m_goalHitTime(goalHitTime),
	m_isNoDamage(isNoDamage)
{
	// グラフィックの読み込み
	m_gameClearBgHandle = LoadGraph("data/image/yellow.png");
	assert(m_gameClearBgHandle != -1);
	m_gameClearPlayerHandle = LoadGraph("data/image/player.png");
	assert(m_gameClearPlayerHandle != -1);

	//BGMの読み込み
	m_bgmHandle = LoadSoundMem("data/sound/BGM/clear.mp3");
	assert(m_bgmHandle != -1);

	// SEの読み込み
	m_seHandle = LoadSoundMem("data/sound/SE/pressAButton.mp3");
	assert(m_seHandle != -1);

	// ゲームクリア用プレイヤーの初期化
	InitGameClearPlayers();
}

SceneGameClear::~SceneGameClear()
{
	// グラフィックの開放
	DeleteGraph(m_gameClearBgHandle);
	DeleteGraph(m_gameClearPlayerHandle);

	//BGMを解放
	DeleteSoundMem(m_bgmHandle);

	// SEを解放
	DeleteSoundMem(m_seHandle);
}

void SceneGameClear::Init()
{
	m_pFont = std::make_shared<FontManager>();
	// BGMの再生開始（ループ再生）
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

SceneBase* SceneGameClear::Update()
{
	//サウンドの大きさ設定
	ChangeVolumeSoundMem(kVolumeBGM, m_bgmHandle);
	ChangeVolumeSoundMem(kVolumeSE, m_seHandle);

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
		// SEを再生
		PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
		// BGMを停止
		StopSoundMem(m_bgmHandle);
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

	// スコアランクの表示
	DrawStringToHandle(kRankPosX, kRankPosY, "RANK", 0xffffff, m_pFont->GetFont(64));
	if (m_isNoDamage && m_score >= 6000)
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "S", 0xFFD700, m_pFont->GetFont(64));
	}
	else if (m_score >= 6000)
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "A", 0xcccccc, m_pFont->GetFont(64));
	}
	else if (m_score >= 5000)
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "B", 0xB87333, m_pFont->GetFont(64));
	}
	else
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "C", 0x008b8b, m_pFont->GetFont(64));
	}

	// 割合を使用して変換を行う
   	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// 割合を実際の透明度に変換する
	int alpha = static_cast<int>(255 * progressRate);
	// ここ以降呼ばれるDraw関数の描画方法を変更する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", static_cast<int>(strlen("GAMECLEAR")), m_pFont->GetFont(84));

	// ウェーブアニメーションを適用して文字を描画
	const int charSpacing = 60;     // 文字間隔を広げるためのスペース
	const int specialSpacing = 100; // MとEの間隔を広げるためのスペース
	int xOffset = -50;              // 文字のX座標のオフセット

	for (int i = 0; i < strlen("GAMECLEAR"); ++i)
	{
		float waveOffset = kWaveAmplitude * std::sin((m_waveFrameCount + i * 10) * kWaveFrequency); // ウェーブアニメーションのオフセット
		DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - width * 0.5 + xOffset), static_cast<int>(100 + waveOffset),
			std::string(1, "GAMECLEAR"[i]).c_str(), 0xffd700, m_pFont->GetFont(84));

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

	/*スコアとタイマーの文字の1文字目を合わせ、数字は1の位を合わせる*/
	// スコアの表示
	std::string scoreText = "Score: " + std::to_string(m_score); // スコアの文字列
	int scoreTextWidth = GetDrawStringWidthToHandle("Score: ", static_cast<int>(strlen("Score: ")), m_pFont->GetFont(64)); // スコアの文字の幅
	int scoreNumberWidth = GetDrawStringWidthToHandle(std::to_string(m_score).c_str(), static_cast<int>(std::to_string(m_score).length()), m_pFont->GetFont(64)); // スコアの数字の幅
	DrawStringToHandle(static_cast<int>(kScoreTextPosX - scoreTextWidth * 0.5), kScorePosY, "Score: ", 0xffffff, m_pFont->GetFont(64)); // スコアの文字を描画
	DrawStringToHandle(static_cast<int>(kScoreNumberPosX + scoreTextWidth * 0.5 - scoreNumberWidth), kScorePosY, std::to_string(m_score).c_str(), 0xffffff, m_pFont->GetFont(64)); // スコアの数字を描画

	// タイマーの表示
	std::string timeText = "Time: " + std::to_string(m_goalHitTime); // タイマーの文字列
	int timeTextWidth = GetDrawStringWidthToHandle("Time: ", static_cast<int>(strlen("Time: ")), m_pFont->GetFont(64)); // タイマーの文字の幅
	int timeNumberWidth = GetDrawStringWidthToHandle(std::to_string(m_goalHitTime).c_str(), static_cast<int>(std::to_string(m_goalHitTime).length()), m_pFont->GetFont(64)); // タイマーの数字の幅
	DrawStringToHandle(static_cast<int>(kTimeTextPosX - timeTextWidth * 0.5), kTimePosY, "Time: ", 0xffffff, m_pFont->GetFont(64)); // タイマーの文字を描画
	DrawStringToHandle(static_cast<int>(kTimeNumberPosX + timeTextWidth * 0.5 - timeNumberWidth), kTimePosY, std::to_string(m_goalHitTime).c_str(), 0xffffff, m_pFont->GetFont(64)); // タイマーの数字を描画

	// Press A Buttonの点滅表示
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(kPressAButtonPosX, kPressAButtonPosY, 0xffffff, m_pFont->GetFont(40), "Press A Button");
	}

	// 以降の表示がおかしくならないように元の設定に戻しておく
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// フェード処理
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = static_cast<int>(255 * fadeRate);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

// ゲームオーバー用プレイヤーの初期化
void SceneGameClear::InitGameClearPlayers()
{
	for (int i = 0; i < kNumGameClearPlayrers; ++i)
	{
		GameClearPlayer player;
		player.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // x座標をランダムに設定
		player.pos.y = kGameClearPlayerStartPosY;  // y座標を初期位置に設定
		player.fallSpeed = kGameClearPlayerFallSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameClearPlayerFallSpeedMax - kGameClearPlayerFallSpeedMin))); // 落下速度をランダムに設定
		player.rotationSpeed = kGameClearPlayerRotationSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameClearPlayerRotationSpeedMax - kGameClearPlayerRotationSpeedMin))); // 回転速度をランダムに設定
		player.angle = 0.0f; // 回転角度を初期化
		m_gameClearPlayers.push_back(player);	
	}
}

// ゲームオーバー用プレイヤーの更新
void SceneGameClear::UpdateGameClearPlayers()
{
	for (auto& player : m_gameClearPlayers)
	{
		player.pos.y += player.fallSpeed;       // 落下
		player.angle += player.rotationSpeed;   // 回転
		if (player.pos.y > Game::kScreenHeight) // 画面外に出たら再配置
		{
			player.pos.y = kGameClearPlayerStartPosY; // 画面外から出現
			player.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // 画面内のランダムな位置
		} 
	}
}

// ゲームオーバー用プレイヤーの描画
void SceneGameClear::DrawGameClearPlayers()
{
	for (const auto& player : m_gameClearPlayers)
	{
		DrawRotaGraph(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), kScale, player.angle, m_gameClearPlayerHandle, true);
	}
}
