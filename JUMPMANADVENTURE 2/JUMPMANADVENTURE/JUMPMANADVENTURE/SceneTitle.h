#pragma once
#include "SceneManager.h"

/// <summary>
/// �^�C���V�[���N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	 SceneManager::SceneSelect Update();
	void Draw();

private:
	int m_titleHandle;
};

