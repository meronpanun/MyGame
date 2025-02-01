#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameClear.h"
#include "Pad.h"

SceneManager::SceneManager():
	m_pTitle(nullptr),
	m_pSceneMain(nullptr),
	m_pGameClear(nullptr),
	m_pCurrentScene(nullptr),
	m_pNextScene(nullptr),
	m_isGameClear(false)
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
	if (m_pGameClear != nullptr)
	{
		delete m_pGameClear;
		m_pGameClear = nullptr;
	}
}

void SceneManager::Init()
{
	// 初期シーンをタイトルシーンに設定
	m_pTitle = new SceneTitle();
	m_pTitle->Init();
	m_pCurrentScene = m_pTitle;
}


void SceneManager::Update()
{
	Pad::Update();

	// 現在のシーンを更新
	if (m_pCurrentScene != nullptr)
	{
		m_pNextScene = m_pCurrentScene->Update();
	}

	// シーンが変わった場合、初期化処理を行う
	if (m_pNextScene != nullptr && m_pNextScene != m_pCurrentScene)
	{
		m_pCurrentScene = m_pNextScene;
		m_pCurrentScene->Init();
	}
}

void SceneManager::Draw()
{
	// 現在のシーンを描画
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Draw();
	}
}

void SceneManager::StartGameClear()
{
	m_isGameClear = true;
	m_pNextScene = new SceneGameClear(m_score, m_timer);
}
