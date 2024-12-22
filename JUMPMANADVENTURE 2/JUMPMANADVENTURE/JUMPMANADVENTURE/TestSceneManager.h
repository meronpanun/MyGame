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
	// �񋓌^���g�p���Č��ݎ��s���̃V�[�����Ǘ�����
	enum SceneKind
	{
		kTitleScene,
		kSceneMain,

		kSceneNum
	};
private:

	// ���ݎ��s���̃V�[��
	SceneKind m_kind;

	TestTitleScene* m_pTitleScene;
	SceneMain* m_pSceneMain;
};

