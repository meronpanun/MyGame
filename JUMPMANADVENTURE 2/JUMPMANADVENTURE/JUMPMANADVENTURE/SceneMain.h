#pragma once
#include "Camera.h"
#include "Player.h"
#include "Map.h"
#include "SceneManeger.h"


class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	SceneManeger::SceneKind Update();
	void Draw();

private:
	Map m_map;
	Player m_player;
	Camera m_camera;
};

