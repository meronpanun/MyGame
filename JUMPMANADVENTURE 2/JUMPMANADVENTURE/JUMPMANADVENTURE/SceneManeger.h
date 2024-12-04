#pragma once

class SceneMain;
class SceneManeger
{
public:
	SceneManeger();
	~SceneManeger();

	void Init();
	void End();
	void Update();
	void Draw();

public:
	enum SceneKind
	{
		kTitleScene,
		kSceneMain,
	};

private:
	// ���ݎ��s���̃V�[��
	SceneKind m_kind;

//	TitleScene* m_pTitleScene;
	SceneMain* m_pSceneMain;
};

