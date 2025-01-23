#include "SceneTitle.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �����̓_��
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;
}

SceneTitle::SceneTitle():
	m_blinkFrameCount(0)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);
}

SceneTitle::~SceneTitle()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_titleHandle);
}


void SceneTitle::Init()
{

}

SceneManager::SceneSelect SceneTitle::Update()
{
	// 1�b�T�C�N���ŕ\���A��\���؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// ZorA�L�[����������X�e�[�W1�Ɉڍs
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneStage1;
	}
	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�^�C�g����ʂ̂܂�)
	return SceneManager::SceneSelect::kSceneTitle;
}

void SceneTitle::Draw()
{
	DrawString(10, 10, "TitleScene", 0xffffff);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawString(580, 600, "Press A Button", 0xffffff);
	}
	// �^�C�g�����S�̕`��
	DrawRotaGraph(Game::kScreenWidth * 0.5, Game::kScreenHeight * 0.5,
		1.0f, 0.0f,
		m_titleHandle, true);
}
