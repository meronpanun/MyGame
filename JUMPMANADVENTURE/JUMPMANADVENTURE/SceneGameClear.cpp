#include "SceneGameClear.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include <cassert>

namespace
{
	// �����̓_��
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// �t�F�[�h
	constexpr int kFadeFrame = 8;
	// �ő�t�F�[�h��
	constexpr int kFadeMax = 255;
}

SceneGameClear::SceneGameClear():
	m_blinkFrameCount(0),
	m_fadeAlpha(kFadeMax)
{
}

SceneGameClear::~SceneGameClear()
{
}

void SceneGameClear::Init()
{
}

SceneManager::SceneSelect SceneGameClear::Update()
{
	// 1�b�T�C�N���ŕ\���A��\���؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// ZorA�L�[����������^�C�g����ʂɈڍs
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneTitle;
	}
	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�N���A��ʂ̂܂�)
	return SceneManager::SceneSelect::kSceneGameClear;

	//if (m_isSceneTitle)
	//{
	//	m_fadeAlpha += kFadeFrame;
	//	if (m_fadeAlpha > kFadeFrame) m_fadeAlpha = kFadeMax;
	//}
	//else
	//{
	//	m_fadeAlpha -= kFadeFrame;
	//	if (m_fadeAlpha < 0) m_fadeAlpha = 0;
	//}
}

void SceneGameClear::Draw()
{
	DrawString(10, 10, "GameClearScene", 0xffffff);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawString(580, 600, "Press A Button", 0xffffff);
	}

	// �t�F�[�h����
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha);
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}
