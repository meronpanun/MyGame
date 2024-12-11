#pragma once
#include "SceneManager.h"

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	SceneManager::SceneKind Update();
	void Draw();
};

