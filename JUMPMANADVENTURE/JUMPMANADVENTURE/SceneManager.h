#pragma once

class SceneStage1;
class SceneTitle;
class SceneMain;
class SceneGameClear;
/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();

public:
	// シーン定数の定義
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStage1,
		kSceneGameClear
	};

private:
	// 現在実行中のシーン
	SceneSelect m_runScene;

	// SceneManagerで管理するシーン
	SceneTitle* m_pTitle;
	SceneMain* m_pSceneMain;
	SceneGameClear* m_pGameClear;
};

