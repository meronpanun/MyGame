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

	// Press A Button�̕������\�������܂ł̃t���[����
	constexpr int kPressAButtonFadeFrame = 60;
}

SceneTitle::SceneTitle():
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameTitleFrameCount(0)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);	
	m_uiHandle = LoadGraph("data/image/ui.png");
	assert(m_titleHandle != -1);

	// �t�H���g�̐���
	m_fontHandle = CreateFontToHandle("Bodoni MT BlaSck", 24, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

SceneTitle::~SceneTitle()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_titleHandle);
	DeleteGraph(m_uiHandle);
	// �t�H���g�̊J��
	DeleteFontToHandle(m_fontHandle);
}


void SceneTitle::Init()
{

}

SceneManager::SceneSelect SceneTitle::Update()
{
	// �t�F�[�h�C������
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	// �Q�[���N���A���o
	m_gameTitleFrameCount++;
	if (m_gameTitleFrameCount > kPressAButtonFadeFrame)
	{
		m_gameTitleFrameCount = kPressAButtonFadeFrame;
	}

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

	// �^�C�g�����S�̕`��
	DrawRotaGraph(Game::kScreenWidth * 0.5, 290,
		1.0f, 0.0f,
		m_titleHandle, true);
	
	//DrawRotaGraph(615, 615,
	//	0.7f, 0.0f,
	//	m_uiHandle, true);

	// �������g�p���ĕϊ����s��
	float progressRate = static_cast<float>(m_gameTitleFrameCount) / kPressAButtonFadeFrame;

	// ���������ۂ̓����x�ɕϊ�����
	int alpha = static_cast<int>(255 * progressRate);

	// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawStringToHandle(520, 600,
			"Press A Button", 0xffffff, m_fontHandle);
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
