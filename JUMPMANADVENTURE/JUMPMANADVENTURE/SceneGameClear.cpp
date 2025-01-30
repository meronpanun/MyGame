#include "SceneGameClear.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include "FontManager.h"
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

	// �w�i��1�̃T�C�Y
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;
}

SceneGameClear::SceneGameClear():
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameClearFrameCount(0),
	m_bgScrollY(0)
{
	m_gameClearHandle = LoadGraph("data/image/Yellow.png");
	assert(m_gameClearHandle != -1);
}

SceneGameClear::~SceneGameClear()
{
	DeleteGraph(m_gameClearHandle);
}

void SceneGameClear::Init()
{
	m_pFont = std::make_shared<FontManager>();
}

SceneManager::SceneSelect SceneGameClear::Update()
{
	// �t�F�[�h�C������
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	// �Q�[���N���A���o
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

	// �w�i�̃X�N���[���ʒu���X�V
	m_bgScrollY -= 1; // �X�N���[�����x�𒲐�
	if (m_bgScrollY > Game::kScreenHeight)
	{
		m_bgScrollY = 0;
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
	// �w�i���X�N���[�����ĕ`��
	for (int y = m_bgScrollY - Game::kScreenHeight; y < Game::kScreenHeight; y += kChipHeight)
	{
		for (int x = 0; x < Game::kScreenWidth; x += kChipWidth)
		{
			DrawGraph(x, y, m_gameClearHandle, true);
		}
	}

	// �������g�p���ĕϊ����s��
   	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// ���������ۂ̓����x�ɕϊ�����
	int alpha = static_cast<int>(255 * progressRate);

	// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", strlen("GAMECLEAR"), m_pFont->GetFont1());
	DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
		"GAMECLEAR", 0xffffff, m_pFont->GetFont1());
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(500, 600, 0xffffff, m_pFont->GetFont2(), "Press A Button");
	}

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
