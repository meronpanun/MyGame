#include "TestSceneMain.h"
#include "DxLib.h"
#include"Pad.h"

TestSceneMain::TestSceneMain()
{
}

TestSceneMain::~TestSceneMain()
{
}

void TestSceneMain::Init()
{
	m_testPlayer.Init(&m_camera);
	m_camera.Init();
	m_testMap.Init();
}

void TestSceneMain::End()
{
}

TestSceneManager::SceneKind TestSceneMain::Update()
{
    return TestSceneManager::SceneKind();
}

void TestSceneMain::Draw()
{
}
