#include "SceneManager.h"
#include "SceneStage1.h"
#include "SceneTitle.h"
#include "Pad.h"

SceneManager::SceneManager():
	m_runScene(kSceneTitle)
{
	m_pStage1 = new SceneStage1;
}

SceneManager::~SceneManager()
{
	delete m_pTitle;
	m_pTitle = nullptr;

	delete m_pStage1;
	m_pStage1 = nullptr;
}

void SceneManager::Init()
{
	// 実行するシーンの初期化を行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle->Init();
		break;
		// ステージ1
	case kSceneStage1:
		m_pStage1->Init();
	default:
		break;
	}
}


void SceneManager::Update()
{
	Pad::Update();

	switch (m_runScene)
	{
	case kSceneTitle:
		m_pTitle->Update();
		break;
	case kSceneStage1:
		m_pStage1->Update();
		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	switch (m_runScene)
	{
	case kSceneTitle:
		m_pTitle->Draw();
		break;
	case kSceneStage1:
		m_pStage1->Draw();
		break;
	default:
		break;
	}
}
