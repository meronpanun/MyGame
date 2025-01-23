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
}

SceneTitle::SceneTitle():
	m_blinkFrameCount(0)
{
	// グラフィックの読み込み
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);
}

SceneTitle::~SceneTitle()
{
	// グラフィックの開放
	DeleteGraph(m_titleHandle);
}


void SceneTitle::Init()
{

}

SceneManager::SceneSelect SceneTitle::Update()
{
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
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawString(580, 600, "Press A Button", 0xffffff);
	}
	// タイトルロゴの描画
	DrawRotaGraph(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
		1.0f, 0.0f,
		m_titleHandle, true);
}
