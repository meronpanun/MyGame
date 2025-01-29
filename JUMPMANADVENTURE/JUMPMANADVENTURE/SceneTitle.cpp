#include "SceneTitle.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// Press A Buttonの文字が表示されるまでのフレーム数
	constexpr int kPressAButtonFadeFrame = 60;

	// フェードアウトにかかるフレーム数
	constexpr int kVideoFadeOutFrame = 120;

	// フェードアウトが終わる少し前に動画を再生し始めるフレーム数
	constexpr int kVideoFadeOutStartFrame = 100;
}

SceneTitle::SceneTitle() :
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameTitleFrameCount(0),
	m_isVideoPlaying(false),
	m_videoFadeFrameCount(0),
	m_videoFadeInFrameCount(0)
{
	// グラフィックの読み込み
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);
	m_uiHandle = LoadGraph("data/image/ui.png");
	assert(m_titleHandle != -1);

	// フォントの生成
	m_fontHandle = CreateFontToHandle("Bodoni MT BlaSck", 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	// 動画の読み込み
	m_videoHandle = LoadGraph("data/TitleBackground.mp4");
	assert(m_videoHandle != -1);
}

SceneTitle::~SceneTitle()
{
	// グラフィックの開放
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_uiHandle);
	// フォントの開放
	DeleteFontToHandle(m_fontHandle);
	// 動画の開放
	DeleteGraph(m_videoHandle);
}

void SceneTitle::Init()
{
	// 動画の再生開始
	PlayMovieToGraph(m_videoHandle);
	m_isVideoPlaying = true;
	m_videoFadeFrameCount = 0;
	m_videoFadeInFrameCount = 0;
}

SceneManager::SceneSelect SceneTitle::Update()
{
	// フェードイン処理
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	// タイトル演出
	m_gameTitleFrameCount++;
	if (m_gameTitleFrameCount > kPressAButtonFadeFrame)
	{
		m_gameTitleFrameCount = kPressAButtonFadeFrame;
	}

	// 1秒サイクルで表示、非表示切り替えす
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// 動画の再生状態をチェック
	if (m_isVideoPlaying && GetMovieStateToGraph(m_videoHandle) == 0)
	{
		// 動画が終了したらフェードアウトを開始
		m_isVideoPlaying = false;
		m_videoFadeFrameCount = kVideoFadeOutFrame;
	}

	// フェードアウト処理
	if (!m_isVideoPlaying && m_videoFadeFrameCount > 0)
	{
		m_videoFadeFrameCount--;
		if (m_videoFadeFrameCount == kVideoFadeOutStartFrame)
		{
			// フェードアウトが終わる少し前に動画を再生し始める
			SeekMovieToGraph(m_videoHandle, 0);
			PlayMovieToGraph(m_videoHandle);
		}
		if (m_videoFadeFrameCount == 0)
		{
			// フェードアウトが完了したら動画の再生状態を更新
			m_isVideoPlaying = true;
		}
	}

	// ZorAキーを押したらステージ1に移行
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneStage1;
	}
	// 何もしなければシーン遷移しない(タイトル画面のまま)
	return SceneManager::SceneSelect::kSceneTitle;
}

void SceneTitle::Draw()
{
	DrawString(10, 10, "TitleScene", 0xffffff);

	// 動画の描画
	DrawGraph(0, 0, m_videoHandle, true);

	// フェードアウト処理
	if (!m_isVideoPlaying && m_videoFadeFrameCount > 0)
	{
		int alpha = static_cast<int>(255 * (static_cast<float>(m_videoFadeFrameCount) / kVideoFadeOutFrame));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// タイトルロゴの描画
	DrawRotaGraph(Game::kScreenWidth * 0.5, 290,
		1.0f, 0.0f,
		m_titleHandle, true);

	//DrawRotaGraph(615, 615,
	//	0.7f, 0.0f,
	//	m_uiHandle, true);

	// 割合を使用して変換を行う
	float progressRate = static_cast<float>(m_gameTitleFrameCount) / kPressAButtonFadeFrame;

	// 割合を実際の透明度に変換する
	int alpha = static_cast<int>(255 * progressRate);

	// ここ以降呼ばれるDraw関数の描画方法を変更する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawStringToHandle(520, 600,
			"Press A Button", 0xffffff, m_fontHandle);
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