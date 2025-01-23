#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneGameClear.h"
#include "Pad.h"

SceneManager::SceneManager():
	m_runScene(kSceneTitle),
	m_pTitle(nullptr),
	m_pSceneMain(nullptr),
	m_pGameClear(nullptr)
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
	// ���s����V�[���̏��������s��
	switch (m_runScene)
	{
	case kSceneTitle:     // �^�C�g���V�[��
		m_pTitle = new SceneTitle();
		m_pTitle->Init();
		break;
	case kSceneStage1:    // �X�e�[�W1
		m_pSceneMain = new SceneMain();
		m_pSceneMain->Init();
		break;
	case kSceneGameClear: // �N���A�V�[��
		m_pGameClear = new SceneGameClear();
		m_pGameClear->Init();
		break;
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
	case kSceneTitle: 	  // �^�C�g���V�[��
		nextSelect = m_pTitle->Update();
		break;
	case kSceneStage1: 	  // �X�e�[�W1
		nextSelect = m_pSceneMain->Update();
		break;
	case kSceneGameClear: // �N���A�V�[��
		nextSelect = m_pGameClear->Update();
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
	case kSceneTitle:     // �^�C�g���V�[��
		m_pTitle->Draw();
		break;
	case kSceneStage1:    // �X�e�[�W1
		m_pSceneMain->Draw();
		break;
	case kSceneGameClear: // �N���A�V�[��
		m_pGameClear->Draw();
		break;
	default:
		break;
	}
}
