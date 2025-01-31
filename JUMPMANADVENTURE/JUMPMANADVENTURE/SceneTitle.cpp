#include "SceneTitle.h"
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

	// Press A Button�̕������\�������܂ł̃t���[����
	constexpr int kPressAButtonFadeFrame = 60;

	// �t�F�[�h�A�E�g�ɂ�����t���[����
	constexpr int kVideoFadeOutFrame = 120;

	// �t�F�[�h�A�E�g���I��鏭���O�ɓ�����Đ����n�߂�t���[����
	constexpr int kVideoFadeOutStartFrame = 100;

	// ����
	constexpr int kVolumeBGM = 128;
	constexpr int kVolumeSE = 128;
}

SceneTitle::SceneTitle() :
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameTitleFrameCount(0),
	m_isVideoPlaying(false),
	m_videoFadeFrameCount(0),
	m_videoFadeInFrameCount(0)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_titleHandle = LoadGraph("data/image/Title.png");
	assert(m_titleHandle != -1);

	// ����̓ǂݍ���
	m_videoHandle = LoadGraph("data/TitleBackground.mp4");
	assert(m_videoHandle != -1);

	//BGM�̓ǂݍ���
	m_bgmHandle = LoadSoundMem("data/sound/BGM/TitleBGM.mp3");
	assert(m_bgmHandle != -1);

	// SE�̓ǂݍ���
	m_seHandle = LoadSoundMem("data/sound/SE/����{�^��������49.mp3");
	assert(m_seHandle != -1);
}

SceneTitle::~SceneTitle()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_titleHandle);
	// ����̊J��
	DeleteGraph(m_videoHandle);
	//BGM�����
	DeleteSoundMem(m_bgmHandle);
	// SE�����
	DeleteSoundMem(m_seHandle);
}

void SceneTitle::Init()
{
	// ����̍Đ��J�n
	PlayMovieToGraph(m_videoHandle);
	m_isVideoPlaying = true;
	m_videoFadeFrameCount = 0;
	m_videoFadeInFrameCount = 0;
	m_pFont = std::make_shared<FontManager>();

	// BGM�̍Đ��J�n�i���[�v�Đ��j
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

SceneManager::SceneSelect SceneTitle::Update()
{
	//�T�E���h�̑傫���ݒ�
	ChangeVolumeSoundMem(kVolumeBGM, m_bgmHandle);
	ChangeVolumeSoundMem(kVolumeSE, m_seHandle);

	// �t�F�[�h�C������
	m_fadeFrameCount++;
	if (m_fadeFrameCount > 30)
	{
		m_fadeFrameCount = 30;
	}

	// �^�C�g�����o
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

	// ����̍Đ���Ԃ��`�F�b�N
	if (m_isVideoPlaying && GetMovieStateToGraph(m_videoHandle) == 0)
	{
		// ���悪�I��������t�F�[�h�A�E�g���J�n
		m_isVideoPlaying = false;
		m_videoFadeFrameCount = kVideoFadeOutFrame;
	}

	// �t�F�[�h�A�E�g����
	if (!m_isVideoPlaying && m_videoFadeFrameCount > 0)
	{
		m_videoFadeFrameCount--;
		if (m_videoFadeFrameCount == kVideoFadeOutStartFrame)
		{
			// �t�F�[�h�A�E�g���I��鏭���O�ɓ�����Đ����n�߂�
			SeekMovieToGraph(m_videoHandle, 0);
			PlayMovieToGraph(m_videoHandle);
		}
		if (m_videoFadeFrameCount == 0)
		{
			// �t�F�[�h�A�E�g�����������瓮��̍Đ���Ԃ��X�V
			m_isVideoPlaying = true;
		}
	}

	// ZorA�L�[����������X�e�[�W1�Ɉڍs
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// SE���Đ�
		PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
		// BGM���~
		StopSoundMem(m_bgmHandle);
		return SceneManager::SceneSelect::kSceneStage1;
	}
	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�^�C�g����ʂ̂܂�)
	return SceneManager::SceneSelect::kSceneTitle;
}

void SceneTitle::Draw()
{
	// ����̕`��
	DrawGraph(0, 0, m_videoHandle, true);

	// �t�F�[�h�A�E�g����
	if (!m_isVideoPlaying && m_videoFadeFrameCount > 0)
	{
		int alpha = static_cast<int>(255 * (static_cast<float>(m_videoFadeFrameCount) / kVideoFadeOutFrame));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �������Ȕ̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // �������̐ݒ�
	DrawBox(0, 0, 1280, 720, 0x000000, TRUE);  // �������ȍ�����`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); // �u�����h���[�h�����ɖ߂�

	// �^�C�g�����S�̕`��
	DrawRotaGraph(Game::kScreenWidth * 0.5, 200,
		1.0f, 0.0f,
		m_titleHandle, true);

	// �������g�p���ĕϊ����s��
	float progressRate = static_cast<float>(m_gameTitleFrameCount) / kPressAButtonFadeFrame;

	// ���������ۂ̓����x�ɕϊ�����
	int alpha = static_cast<int>(255 * progressRate);

	// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(430, 550, 0xffffff, m_pFont->GetFont2(),"Press A Button");
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