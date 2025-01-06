#pragma once
#include "Vec2.h"
#include "SceneManager.h"

/// <summary>
/// �Q�[���I�[�o�[�̃N���X
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	virtual ~SceneGameOver();

	void Init();
	SceneManager::SceneSelect Update();
	void Draw();

	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// �V�[���I���̃t���O true:�V�[���Ɉړ�
	bool m_isSceneTitle;	// �^�C�g�� 

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};

