#pragma once
#include "SceneManager.h"

/// <summary>
///�@�Q�[���N���A�V�[���N���X
/// </summary>
class SceneGameClear
{
public:
	SceneGameClear();
	~SceneGameClear();

	void Init();
	// �V�[���̐؂�ւ����߂�l�Ƃ��ĕԂ�
	// �؂�ւ��Ȃ��ꍇ�͌��ݎ��s���̃V�[����Ԃ�
	SceneManager::SceneSelect Update();
	void Draw();
	
private:
	// �N���A�V�[���̃O���t�B�b�N�n���h��
	int m_gameClearHandle;
	// �_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;
};

