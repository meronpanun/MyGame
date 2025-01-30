#include "SceneGameClear.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include "FontManager.h"
#include <cassert>

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
}

SceneGameClear::SceneGameClear():
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameClearFrameCount(0),
	m_bgScrollY(0)
{
	m_gameClearHandle = LoadGraph("data/image/Yellow.png");
	assert(m_gameClearHandle != -1);
}

SceneGameClear::~SceneGameClear()
{
	DeleteGraph(m_gameClearHandle);
}

void SceneGameClear::Init()
{
	m_pFont = std::make_shared<FontManager>();
}

SceneManager::SceneSelect SceneGameClear::Update()
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

	// ZorAキーを押したらタイトル画面に移行
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneTitle;
	}
	// 何もしなければシーン遷移しない(クリア画面のまま)
	return SceneManager::SceneSelect::kSceneGameClear;
}

void SceneGameClear::Draw()
{
	// 背景をスクロールして描画
	for (int y = m_bgScrollY - Game::kScreenHeight; y < Game::kScreenHeight; y += kChipHeight)
	{
		for (int x = 0; x < Game::kScreenWidth; x += kChipWidth)
		{
			DrawGraph(x, y, m_gameClearHandle, true);
		}
	}

	// 割合を使用して変換を行う
   	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// 割合を実際の透明度に変換する
	int alpha = static_cast<int>(255 * progressRate);

	// ここ以降呼ばれるDraw関数の描画方法を変更する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", strlen("GAMECLEAR"), m_pFont->GetFont1());
	DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
		"GAMECLEAR", 0xffffff, m_pFont->GetFont1());
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(500, 600, 0xffffff, m_pFont->GetFont2(), "Press A Button");
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
