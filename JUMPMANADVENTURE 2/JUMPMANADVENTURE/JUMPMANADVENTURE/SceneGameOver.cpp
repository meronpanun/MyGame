#include "SceneGameOver.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// Gameoverの文字表示位置
	constexpr int kGameOverPosX = 960;
	constexpr int kGameOverPosY = 280;
	// Gameoverの文字サイズ
	constexpr int kGameOverSizeX = 1592;
	constexpr int kGameOverSizeY = 174;
	// Gameoverの文字拡大率
	constexpr float kGameOverScale = 0.8f;

	// 文字表示位置
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 720;

	//フェード
	constexpr int kFadeFrame = 8;
	// 最大フェード量
	constexpr int kFadeMax = 255;

}
SceneGameOver::SceneGameOver():
	m_isSceneTitle(false),
	m_fadeAlpha(kFadeMax)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

SceneManager::SceneSelect SceneGameOver::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ZorAキーを押したらタイトルシーンに移行
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneTitle;
	}
	// 何もしなければシーン遷移しない(ゲームオーバー画面のまま)
	return SceneManager::SceneSelect::kSceneGameOver;
}

void SceneGameOver::Draw()
{
	DrawString(10, 10, "TitleScene", 0xffffff);
}
