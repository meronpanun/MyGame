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

	// �Q�[���N���A�̕������\�������܂ł̃t���[����
	constexpr int kGameClearFadeFrame = 60;
}

SceneGameClear::SceneGameClear():
	m_blinkFrameCount(0),
	m_fadeFrameCount(0)
{
	// �t�H���g�̐���
	m_fontHandle = CreateFontToHandle("Bodoni MT BlaSck", 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

SceneGameClear::~SceneGameClear()
{
	// �t�H���g�̊J��
	DeleteFontToHandle(m_fontHandle);
}

void SceneGameClear::Init()
{
}

SceneManager::SceneSelect SceneGameClear::Update()
{
	// �t�F�[�h�C������
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	m_gameClearFrameCount++;
	if (m_gameClearFrameCount > kGameClearFadeFrame)
	{
		m_gameClearFrameCount = kGameClearFadeFrame;
	}

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
}

void SceneGameClear::Draw()
{
	DrawString(10, 10, "GameClearScene", 0xffffff);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawString(580, 600, "Press A Button", 0xffffff);
	}

	// �������g�p���ĕϊ����s��
		// m_gameoverFrameCount ��i�s�����ɕϊ�����
	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// ���������ۂ̓����x�ɕϊ�����
	int alpha = static_cast<int>(255 * progressRate);

	// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", strlen("GAMECLEAR"), m_fontHandle);
	DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
		"GAMECLEAR", 0xffffff, m_fontHandle);
	// �ȍ~�̕\�������������Ȃ�Ȃ��悤�Ɍ��̐ݒ�ɖ߂��Ă���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �t�F�[�h����
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}
