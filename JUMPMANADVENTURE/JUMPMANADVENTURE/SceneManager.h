#pragma once

class SceneStage1;

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
public:
	SceneManager();
	virtual~SceneManager();

	void Init();
	void Update();
	void Draw();

private:
	// シーン定数の定義
	enum SceneSelect
	{
		kSceneStage1
	};

	// 現在進行中のシーン
	SceneSelect m_runScene;

private:
	SceneStage1* m_pStage1;
};

