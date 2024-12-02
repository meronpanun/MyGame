#pragma once

class SceneStage1;
class TestMap;

 ///<summary>
 /// �V�[���Ǘ��N���X
 ///</summary>
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
		kSceneStage1,
		kMap
	};

	// ���ݐi�s���̃V�[��
	SceneSelect m_runScene;

private:
	SceneStage1* m_pStage1;
//	TestMap* m_pTestMap;
};

