#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "Bg.h"
#include "Player.h"

SceneMain::SceneMain()
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_player->Init();
	m_bgStage1.Init();
}

SceneManager::SceneSelect SceneMain::Update()
{
	m_player->Update();
	Pad::Update();

	return SceneManager::SceneSelect::kSceneStage1;
}

void SceneMain::Draw()
{
	m_bgStage1.Draw();
	m_player->Draw();
}
