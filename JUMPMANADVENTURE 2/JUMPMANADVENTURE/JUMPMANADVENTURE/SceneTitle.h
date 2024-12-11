#pragma once
#include "Vec2.h"

/// <summary>
/// �^�C���V�[���N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void Update();
	void Draw();

	bool IsSceneStart() const { return m_isSceneStart; }

private:
	enum Select
	{
		kStart,    // �Q�[���X�^�[�g
		kOption,   // �I�v�V����
		kExit,	   //	�Q�[���I��
		kSelectNum // ���ڐ�
	};

	// ���݂̏��
	int m_select;

private:
	// �V�[���I���t���O�@true:�V�[���ړ�
	bool m_isSceneStart;

	// �I���J�[�\���̕\���ʒu
	Vec2 m_selectPos;

	// �t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	// �摜
	int m_logoHandle;   // �^�C�g�����S
	int m_selectHandle; // �I���J�[�\�� 
	int m_charHandle;   // ����
};

