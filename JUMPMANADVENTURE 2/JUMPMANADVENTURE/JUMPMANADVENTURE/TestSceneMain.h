#pragma once
#include "Camera.h"
#include "TestPlayer.h"
#include "TestSceneManager.h"
#include "TestMap.h"

class TestSceneMain
{
public:
	TestSceneMain();
	~TestSceneMain();

	void Init();
	void End();
	TestSceneManager::SceneKind Update();
	void Draw();

private:
	TestMap m_testMap;
	TestPlayer m_testPlayer;
	Camera m_camera;
};

