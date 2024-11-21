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
	// ���s����V�[���̏�����
	/*switch (m_runScene)
	{
	case kSceneStage1:
		m_pStage1->Init();
	default:
		break;
	}*/
	m_pStage1->Init();
}

void SceneManager::Update()
{
	Pad::Update();
	m_pStage1->Update();

	//switch (m_runScene)
	//{
	//case kSceneStage1:
	//	m_runScene = kSceneStage1;
	//	m_pStage1->Init();
	//	break;
	//default:
	//	break;
	//}

	// ���s����V�[���̍X�V
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
	// ���s����V�[���̕`��
	//switch (m_runScene)
	//{
	//case kSceneStage1:
	//	m_pStage1->Draw();
	//	break;
	//default:
	//	break;
	//}
	m_pStage1->Draw();
}
