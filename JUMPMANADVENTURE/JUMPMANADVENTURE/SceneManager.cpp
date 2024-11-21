#include "SceneManager.h"
#include "SceneStage1.h"
#include "Pad.h"

SceneManager::SceneManager() :
	m_runScene(kSceneStage1)
{
	m_pStage1 = new SceneStage1;
}

SceneManager::~SceneManager()
{
	delete m_pStage1;
	m_pStage1 = nullptr;
}

void SceneManager::Init()
{
	// 実行するシーンの初期化
	switch (m_runScene)
	{
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
	case kSceneStage1:
		m_runScene = kSceneStage1;
		m_pStage1->Init();
		break;
	default:
		break;
	}

	// 実行するシーンの更新
	switch (m_runScene)
	{
	case kSceneStage1:
		m_pStage1->Update();
		break;
	default:
		break;
	}
}

void SceneManager::Draw()
{
	// 実行するシーンの描画
	switch (m_runScene)
	{
	case kSceneStage1:
		m_pStage1->Draw();
		break;
	default:
		break;
	}
}
