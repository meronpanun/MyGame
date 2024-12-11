#pragma once

class SceneStage1;

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

private:
	// ���ݎ��s���̃V�[��
	SceneSelect m_runScene;

	// SceneManager�ŊǗ�����V�[��
//	TitleScene* m_pTitleScene;
	SceneStage1* m_pStage1;
};

