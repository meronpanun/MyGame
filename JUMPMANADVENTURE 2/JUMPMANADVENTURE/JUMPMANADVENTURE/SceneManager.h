#pragma once

class SceneStage1;
class SceneTitle;
class SceneMain;

/// <summary>
/// �V�[���Ǘ��N���X
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
	// �V�[���萔�̒�`
	enum SceneSelect
	{
		kSceneTitle,
		kSceneStage1,
	};

	// ���ݎ��s���̃V�[��
	SceneSelect m_runScene;

private:
	// SceneManager�ŊǗ�����V�[��
	SceneTitle* m_pTitle;
	SceneStage1* m_pStage1;
};

