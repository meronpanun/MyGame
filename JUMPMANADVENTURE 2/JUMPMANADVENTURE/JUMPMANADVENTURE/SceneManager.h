#pragma once

class SceneStage1;

/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void Init();
	void Update();
	void Draw();

private:
	// シーン定数の定義
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStage1,
	};

private:
	// 現在実行中のシーン
	SceneSelect m_runScene;

	// SceneManagerで管理するシーン
//	TitleScene* m_pTitleScene;
	SceneStage1* m_pStage1;
};

