#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
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
	m_pCamera = std::make_shared<Camera>();
	m_pEnemy = std::make_shared<Enemy>();
	m_pPlayer->Init(m_pCamera.get());
	m_pBgStage1->Init(m_pCamera.get());
	m_pCamera->Init();
	m_pEnemy->Init();
}

SceneManager::SceneSelect SceneMain::Update()
{
	// �t�F�[�h�C������
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}
	
	m_pPlayer->Update();
	m_pCamera->Update(m_pPlayer.get());
	m_pEnemy->Update();
	Pad::Update();

	bool isPlayerHit = true;

	if (m_pPlayer->GetLeft() > m_pEnemy->GetRigth())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetTop() > m_pEnemy->GetBottom())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetRigth() < m_pEnemy->GetLeft())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetBottom() < m_pEnemy->GetTop())
	{
		isPlayerHit = false;
	}

	if (isPlayerHit)
	{
		m_pPlayer->OnDamage();
	}

	return SceneManager::SceneSelect::kSceneStage1;
}

void SceneMain::Draw()
{
	m_pBgStage1->Draw();
	m_pPlayer->Draw();
	m_pEnemy->Draw();

	// �t�F�[�h����
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}
