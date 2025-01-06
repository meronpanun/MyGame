#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Life.h"
#include <memory>
#include <cassert>

SceneMain::SceneMain():
	m_fadeFrameCount(0),
	m_lifeHandle(-1)
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// グラフィックの読み込み
	m_lifeHandle = LoadGraph("data/image/life.png");
	assert(m_lifeHandle != -1);

	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>();
	m_pCamera = std::make_shared<Camera>();
	m_pEnemy = std::make_shared<Enemy>();
//	m_pLife[3] = std::make_shared<Life>();
	m_pPlayer->Init(m_pCamera.get());
	m_pBgStage1->Init(m_pCamera.get());
	m_pCamera->Init();
	m_pEnemy->Init();
//	m_pLife[3]->Init();

	for (int i = 0; i < 3; i++)
	{
		m_life[i].Init();
		m_life[i].SetHandle(m_lifeHandle);
		m_life[i].SetIndex(i);
	}
}

void SceneMain::End()
{

	for (int i = 0; i < 3; i++)
	{
		m_life[i].End();
	}

	// グラフィックの削除
	DeleteGraph(m_lifeHandle);
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
	m_pCamera->Update(m_pPlayer.get());
	m_pEnemy->Update();
	Pad::Update();

	for (int i = 0; i < 3; i++)
	{
		m_life[i].Update();
	}

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

	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		m_life[i].Draw();
	}

	// フェード処理
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}
