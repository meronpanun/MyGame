#pragma once

class SceneStage1;

/// <summary>
/// �V�[���Ǘ��N���X
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
	// �V�[���萔�̒�`
	enum SceneSelect
	{
		kSceneStage1
	};

	// ���ݐi�s���̃V�[��
	SceneSelect m_runScene;

private:
	SceneStage1* m_pStage1;
};

