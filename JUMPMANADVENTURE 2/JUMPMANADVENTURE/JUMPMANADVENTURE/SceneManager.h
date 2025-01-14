#pragma once

class SceneStage1;
class SceneTitle;
class SceneMain;
class SceneGameClear;
/// <summary>
/// �V�[���Ǘ��N���X
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
	// �V�[���萔�̒�`
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStage1,
		kSceneGameClear
	};

private:
	// ���ݎ��s���̃V�[��
	SceneSelect m_runScene;

	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneMain* m_pSceneMain;
	SceneGameClear* m_pGameClear;
};

