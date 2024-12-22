#pragma once

class TestTitleScene;
class TestSceneMain;
class TestSceneManager
{
public:
	TestSceneManager();
	~TestSceneManager();

	void Init();
	void End();

	void Update();
	void Draw();

public:
	// 列挙型を使用して現在実行中のシーンを管理する
	enum SceneKind
	{
		kTitleScene,
		kSceneMain,

		kSceneNum
	};
private:

	// 現在実行中のシーン
	SceneKind m_kind;

	TestTitleScene* m_pTitleScene;
	SceneMain* m_pSceneMain;
};

