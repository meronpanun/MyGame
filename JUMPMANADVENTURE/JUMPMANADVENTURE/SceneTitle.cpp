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
}

SceneTitle::SceneTitle():
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameTitleFrameCount(0)
{
	// グラフィックの読み込み
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);	
	m_uiHandle = LoadGraph("data/image/ui.png");
	assert(m_titleHandle != -1);

	// フォントの生成
	m_fontHandle = CreateFontToHandle("Bodoni MT BlaSck", 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

SceneTitle::~SceneTitle()
{
	// グラフィックの開放
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_uiHandle);
	// フォントの開放
	DeleteFontToHandle(m_fontHandle);
}


void SceneTitle::Init()
{

}

SceneManager::SceneSelect SceneTitle::Update()
{
	// フェードイン処理
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	// ゲームクリア演出
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
