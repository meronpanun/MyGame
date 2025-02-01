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
	// �����V�[�����^�C�g���V�[���ɐݒ�
	m_pTitle = new SceneTitle();
	m_pTitle->Init();
	m_pCurrentScene = m_pTitle;
}


void SceneManager::Update()
{
	Pad::Update();

	// ���݂̃V�[�����X�V
	if (m_pCurrentScene != nullptr)
	{
		m_pNextScene = m_pCurrentScene->Update();
	}

	// �V�[�����ς�����ꍇ�A�������������s��
	if (m_pNextScene != nullptr && m_pNextScene != m_pCurrentScene)
	{
		m_pCurrentScene = m_pNextScene;
		m_pCurrentScene->Init();
	}
}

void SceneManager::Draw()
{
	// ���݂̃V�[����`��
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
