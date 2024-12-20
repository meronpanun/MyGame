#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include <memory>

SceneMain::SceneMain():
	m_fadeFrameCount(0)
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>();
	m_camera = std::make_shared<Camera>();
	m_pPlayer->Init(m_camera.get());
	m_pBgStage1->Init(m_camera.get());
	m_camera->Init();
}

SceneManager::SceneSelect SceneMain::Update()
{
	// フェードイン処理
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}
	
	m_pPlayer->Update();
	m_camera->Update(m_pPlayer.get());
	Pad::Update();

	return SceneManager::SceneSelect::kSceneStage1;
}

void SceneMain::Draw()
{
	m_pBgStage1->Draw();
	m_pPlayer->Draw();

	// フェード処理
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}
