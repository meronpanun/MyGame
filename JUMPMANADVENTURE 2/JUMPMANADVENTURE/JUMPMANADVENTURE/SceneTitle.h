#pragma once
#include "SceneManager.h"

/// <summary>
/// �^�C���V�[���N���X
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	// �V�[���̐؂�ւ����߂�l�Ƃ��ĕԂ�
	// �؂�ւ��Ȃ��ꍇ�͌��ݎ��s���̃V�[����Ԃ�
	 SceneManager::SceneSelect Update();
	void Draw();

private:
	// �^�C�g���̃O���t�B�b�N�n���h��
	int m_titleHandle;
	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;
};

