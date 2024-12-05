//#include "SceneManager.h"
//#include "SceneStage1.h"
//#include "Pad.h"
//#include <cassert>
//
//SceneManager::SceneManager():
//	m_runScene(kSceneStage1)
//{
//	m_pStage1 = new SceneStage1;
//}
//
//SceneManager::~SceneManager()
//{
//	delete m_pStage1;
//	m_pStage1 = nullptr;
//}
//
//void SceneManager::Init()
//{
//	switch (m_kind)
//	{
//	case SceneManager::kSceneMain:
//		m_pSceneMain = new SceneMain();
//		m_pSceneMain->Init();
//		break;
//	default:
//		assert(false);
//		break;
//	}
//}
//
//
//void SceneManager::Update()
//{
//	Pad::Update();
//	SceneKind nextKind = m_kind;
//
//	switch (m_kind)
//	{
//	case SceneManager::kSceneMain:
//		nextKind = m_pSceneMain->Update();
//		break;
//	default:
//		assert(false);
//		break;
//	}
//}
//
//void SceneManager::Draw()
//{
//	switch (m_kind)
//	{
//	case SceneManager::kSceneMain:
//		m_pSceneMain->Draw();
//		break;
//	default:
//		assert(false);
//		break;
//	}
//}
