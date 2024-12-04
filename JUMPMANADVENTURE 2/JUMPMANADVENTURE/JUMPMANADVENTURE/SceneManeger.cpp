#include "SceneManeger.h"
#include "DxLib.h"
#include "Pad.h"
#include "SceneMain.h"
#include <cassert>

SceneManeger::SceneManeger():
	m_kind(kSceneMain),
	m_pSceneMain(nullptr)
{
}

SceneManeger::~SceneManeger()
{
	if (m_pSceneMain != nullptr)
	{
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
	}
}

void SceneManeger::Init()
{
	switch (m_kind)
	{
	case SceneManeger::kSceneMain:
		m_pSceneMain = new SceneMain();
		m_pSceneMain->Init();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManeger::End()
{
	switch (m_kind)
	{
	case SceneManeger::kSceneMain:
		m_pSceneMain->End();
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManeger::Update()
{
	Pad::Update();
	SceneKind nextKind = m_kind;

	switch (m_kind)
	{
	case SceneManeger::kSceneMain:
		nextKind = m_pSceneMain->Update();
		break;
	default:
		assert(false);
		break;
	}
}

void SceneManeger::Draw()
{
	switch (m_kind)
	{
	case SceneManeger::kSceneMain:
		m_pSceneMain->Draw();
		break;
	default:
		assert(false);
		break;
	}
}
