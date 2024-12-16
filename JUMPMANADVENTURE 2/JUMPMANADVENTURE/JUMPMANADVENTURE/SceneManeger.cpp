#include "SceneManager.h"
#include "SceneStage1.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "Pad.h"

SceneManager::SceneManager():
	m_runScene(kSceneTitle),
	m_pTitle(nullptr),
	m_pSceneMain(nullptr)
{
}

SceneManager::~SceneManager()
{
	if (m_pTitle != nullptr)
	{
		delete m_pTitle;
		m_pTitle = nullptr;
	}
	if (m_pSceneMain != nullptr)
	{
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
	}
}

void SceneManager::Init()
{
	// 実行するシーンの初期化を行う
	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		m_pTitle = new SceneTitle();
		m_pTitle->Init();
		break;
		// ステージ1
	case kSceneStage1:
		m_pSceneMain = new SceneMain();
		m_pSceneMain->Init();
	default:
		break;
	}
}


void SceneManager::Update()
{
	Pad::Update();
	SceneSelect nextSelect = m_runScene;

	switch (m_runScene)
	{
		// タイトルシーン
	case kSceneTitle:
		nextSelect = m_pTitle->Update();
		break;
		// ステージ1
	case kSceneStage1:
		nextSelect = m_pSceneMain->Update();
		break;
	default:
		break;
	}
	if (nextSelect != m_runScene)
	{
		m_runScene = nextSelect;

		Init();
	}
}

void SceneManager::Draw()
{
	switch (m_runScene)
	{
	case kSceneStage1:
		m_pSceneMain->Draw();
		break;
	case kSceneTitle:
		m_pTitle->Draw();
		break;
	default:
		break;
	}
}
