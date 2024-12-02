#include "SceneManager.h"
#include "SceneStage1.h"
#include "Pad.h"
#include "TestMap.h"

SceneManager::SceneManager() :
	m_runScene(kSceneStage1)
//	m_runScene(kMap)
{
	m_pStage1 = new SceneStage1;
//	m_pTestMap = new TestMap;
}

SceneManager::~SceneManager()
{
	delete m_pStage1;
	m_pStage1 = nullptr;

//	delete m_pTestMap;
//	m_pTestMap = nullptr;
}

void SceneManager::Init()
{
	// 実行するシーンの初期化
	/*switch (m_runScene)
	{
	case kSceneStage1:
		m_pStage1->Init();
	default:
		break;
	}*/
//	m_pStage1->Init();
}

void SceneManager::Update()
{
	Pad::Update();
	m_pStage1->Update();
//	m_pTestMap->Update();

	//switch (m_runScene)
	//{
	//case kSceneStage1:
	//	m_runScene = kSceneStage1;
	//	m_pStage1->Init();
	//	break;
	//default:
	//	break;
	//}

	// 実行するシーンの更新
	/*switch (m_runScene)
	{
	case kSceneStage1:
		m_pStage1->Update();
		break;
	default:
		break;
	}*/
}

void SceneManager::Draw()
{
	// 実行するシーンの描画
	//switch (m_runScene)
	//{
	//case kSceneStage1:
	//	m_pStage1->Draw();
	//	break;
	//default:
	//	break;
	//}
	m_pStage1->Draw();
//	m_pTestMap->Draw();
}
