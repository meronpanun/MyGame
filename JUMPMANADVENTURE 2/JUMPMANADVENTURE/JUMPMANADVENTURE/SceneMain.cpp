#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"

SceneMain::SceneMain()
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_player.Init(&m_camera);
	m_camera.Init();
	m_map.Init();
}

void SceneMain::End()
{
}

SceneManeger::SceneKind SceneMain::Update()
{
	m_map.Update();
	m_player.Update();
	m_camera.Update(&m_player);

	return SceneManeger::SceneKind::kSceneMain;
}

void SceneMain::Draw()
{
	m_map.Draw(&m_camera);
	m_player.Draw();
}
