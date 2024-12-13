#include "SceneTitle.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{

}

SceneTitle::SceneTitle()
{
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_titleHandle);
}


void SceneTitle::Init()
{

}

SceneManager::SceneSelect SceneTitle::Update()
{
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneStage1;
	}
	return SceneManager::SceneSelect::kSceneTitle;
}

void SceneTitle::Draw()
{
	DrawString(10, 10, "TitleScene", 0xffffff);
	DrawString(580, 600, "Press A Button", 0xffffff);
	DrawRotaGraph(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
		1.0f, 0.0f,
		m_titleHandle, true);
}
