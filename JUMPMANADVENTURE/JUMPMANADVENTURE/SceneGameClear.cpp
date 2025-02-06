#include "SceneGameClear.h"
#include "Pad.h"
#include "DxLib.h"
#include "Game.h"
#include "FontManager.h"
#include "SceneTitle.h"
#include <cassert>
#include <vector>
#include <string>

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

	// �Q�[���N���A�p�G�̕`��T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// �g�嗦
    constexpr float kScale = 2.0f; 

	// �Q�[���N���A�p�G�̏����ʒu�Ɨ������x
	constexpr float kGameClearPlayerStartPosY = -kGraphHeight * kScale; // ��ʊO���痎�����Ă���
	constexpr float kGameClearPlayerFallSpeedMin = 1.0f; // �������x�̍ŏ��l
	constexpr float kGameClearPlayerFallSpeedMax = 3.0f; // �������x�̍ő�l
	constexpr float kGameClearPlayerRotationSpeedMin = 0.02f; // ��]���x�̍ŏ��l
	constexpr float kGameClearPlayerRotationSpeedMax = 0.1f;  // ��]���x�̍ő�l
	constexpr int kNumGameClearPlayrers = 10; // �Q�[���N���A�p�G�̐�

	// �E�F�[�u�A�j���[�V�����̃p�����[�^
	constexpr float kWaveAmplitude = 20.0f; // �U��
	constexpr float kWaveFrequency = 0.1f;  // �E�F�[�u�̕p�x

	// ����
	constexpr int kVolumeBGM = 128;
	constexpr int kVolumeSE = 128;

	// �X�R�A�̕\���ʒu
	constexpr int kScoreTextPosX = 480;
	constexpr int kScoreNumberPosX = 710;
	constexpr int kScorePosY = 300;

	// �^�C���̕\���ʒu
	constexpr int kTimeTextPosX = 470;
	constexpr int kTimeNumberPosX = 730;
	constexpr int kTimePosY = 400;

	// �X�R�A�����N�̕\���ʒu
	constexpr int kRankTextPosX = 120;
	constexpr int kRankTextPosY = 400;

	// RANK�̕\���ʒu
	constexpr int kRankPosX = 50;
	constexpr int kRankPosY = 300;

	// Press A Button�̕\���ʒu
	constexpr int kPressAButtonPosX = 380;
	constexpr int kPressAButtonPosY = 600;
}

SceneGameClear::SceneGameClear(int score, int goalHitTime, bool isNoDamage) :
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameClearFrameCount(0),
	m_bgScrollY(0),
	m_gameClearPlayerPosY(kGameClearPlayerStartPosY),
	m_gameClearPlayerAngle(0.0f),
	m_waveFrameCount(0),
	m_score(score),
	m_goalHitTime(goalHitTime),
	m_isNoDamage(isNoDamage)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_gameClearBgHandle = LoadGraph("data/image/yellow.png");
	assert(m_gameClearBgHandle != -1);
	m_gameClearPlayerHandle = LoadGraph("data/image/player.png");
	assert(m_gameClearPlayerHandle != -1);

	//BGM�̓ǂݍ���
	m_bgmHandle = LoadSoundMem("data/sound/BGM/clear.mp3");
	assert(m_bgmHandle != -1);

	// SE�̓ǂݍ���
	m_seHandle = LoadSoundMem("data/sound/SE/pressAButton.mp3");
	assert(m_seHandle != -1);

	// �Q�[���N���A�p�v���C���[�̏�����
	InitGameClearPlayers();
}

SceneGameClear::~SceneGameClear()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_gameClearBgHandle);
	DeleteGraph(m_gameClearPlayerHandle);

	//BGM�����
	DeleteSoundMem(m_bgmHandle);

	// SE�����
	DeleteSoundMem(m_seHandle);
}

void SceneGameClear::Init()
{
	m_pFont = std::make_shared<FontManager>();
	// BGM�̍Đ��J�n�i���[�v�Đ��j
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
}

SceneBase* SceneGameClear::Update()
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

	// �Q�[���N���A�p�v���C���[�̈ʒu�Ɖ�]�p�x���X�V
	UpdateGameClearPlayers();

	// �E�F�[�u�A�j���[�V�����̃t���[���J�E���g���X�V
	m_waveFrameCount++;

	// ZorA�L�[����������^�C�g����ʂɈڍs
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		// SE���Đ�
		PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
		// BGM���~
		StopSoundMem(m_bgmHandle);
		return new SceneTitle();
	}
	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�N���A��ʂ̂܂�)
	return this;
}

void SceneGameClear::Draw()
{
	// �w�i���X�N���[�����ĕ`��
	for (int y = m_bgScrollY - Game::kScreenHeight; y < Game::kScreenHeight; y += kChipHeight)
	{
		for (int x = 0; x < Game::kScreenWidth; x += kChipWidth)
		{
			DrawGraph(x, y, m_gameClearBgHandle, true);
		}
	}

	// �Q�[���N���A�p�v���C���[�̕`��
	DrawGameClearPlayers();

	// �X�R�A�����N�̕\��
	DrawStringToHandle(kRankPosX, kRankPosY, "RANK", 0xffffff, m_pFont->GetFont(64));
	if (m_isNoDamage && m_score >= 6000)
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "S", 0xFFD700, m_pFont->GetFont(64));
	}
	else if (m_score >= 6000)
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "A", 0xcccccc, m_pFont->GetFont(64));
	}
	else if (m_score >= 5000)
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "B", 0xB87333, m_pFont->GetFont(64));
	}
	else
	{
		DrawStringToHandle(kRankTextPosX, kRankTextPosY, "C", 0x008b8b, m_pFont->GetFont(64));
	}

	// �������g�p���ĕϊ����s��
   	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// ���������ۂ̓����x�ɕϊ�����
	int alpha = static_cast<int>(255 * progressRate);
	// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", static_cast<int>(strlen("GAMECLEAR")), m_pFont->GetFont(84));

	// �E�F�[�u�A�j���[�V������K�p���ĕ�����`��
	const int charSpacing = 60;     // �����Ԋu���L���邽�߂̃X�y�[�X
	const int specialSpacing = 100; // M��E�̊Ԋu���L���邽�߂̃X�y�[�X
	int xOffset = -50;              // ������X���W�̃I�t�Z�b�g

	for (int i = 0; i < strlen("GAMECLEAR"); ++i)
	{
		float waveOffset = kWaveAmplitude * std::sin((m_waveFrameCount + i * 10) * kWaveFrequency); // �E�F�[�u�A�j���[�V�����̃I�t�Z�b�g
		DrawStringToHandle(static_cast<int>(Game::kScreenWidth * 0.5 - width * 0.5 + xOffset), static_cast<int>(100 + waveOffset),
			std::string(1, "GAMECLEAR"[i]).c_str(), 0xffd700, m_pFont->GetFont(84));

		// ���̕����̈ʒu���v�Z
		if (i == 2) // M�̌�
		{
			xOffset += specialSpacing;
		}
		else
		{
			xOffset += charSpacing;
		}
	}

	/*�X�R�A�ƃ^�C�}�[�̕�����1�����ڂ����킹�A������1�̈ʂ����킹��*/
	// �X�R�A�̕\��
	std::string scoreText = "Score: " + std::to_string(m_score); // �X�R�A�̕�����
	int scoreTextWidth = GetDrawStringWidthToHandle("Score: ", static_cast<int>(strlen("Score: ")), m_pFont->GetFont(64)); // �X�R�A�̕����̕�
	int scoreNumberWidth = GetDrawStringWidthToHandle(std::to_string(m_score).c_str(), static_cast<int>(std::to_string(m_score).length()), m_pFont->GetFont(64)); // �X�R�A�̐����̕�
	DrawStringToHandle(static_cast<int>(kScoreTextPosX - scoreTextWidth * 0.5), kScorePosY, "Score: ", 0xffffff, m_pFont->GetFont(64)); // �X�R�A�̕�����`��
	DrawStringToHandle(static_cast<int>(kScoreNumberPosX + scoreTextWidth * 0.5 - scoreNumberWidth), kScorePosY, std::to_string(m_score).c_str(), 0xffffff, m_pFont->GetFont(64)); // �X�R�A�̐�����`��

	// �^�C�}�[�̕\��
	std::string timeText = "Time: " + std::to_string(m_goalHitTime); // �^�C�}�[�̕�����
	int timeTextWidth = GetDrawStringWidthToHandle("Time: ", static_cast<int>(strlen("Time: ")), m_pFont->GetFont(64)); // �^�C�}�[�̕����̕�
	int timeNumberWidth = GetDrawStringWidthToHandle(std::to_string(m_goalHitTime).c_str(), static_cast<int>(std::to_string(m_goalHitTime).length()), m_pFont->GetFont(64)); // �^�C�}�[�̐����̕�
	DrawStringToHandle(static_cast<int>(kTimeTextPosX - timeTextWidth * 0.5), kTimePosY, "Time: ", 0xffffff, m_pFont->GetFont(64)); // �^�C�}�[�̕�����`��
	DrawStringToHandle(static_cast<int>(kTimeNumberPosX + timeTextWidth * 0.5 - timeNumberWidth), kTimePosY, std::to_string(m_goalHitTime).c_str(), 0xffffff, m_pFont->GetFont(64)); // �^�C�}�[�̐�����`��

	// Press A Button�̓_�ŕ\��
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(kPressAButtonPosX, kPressAButtonPosY, 0xffffff, m_pFont->GetFont(40), "Press A Button");
	}

	// �ȍ~�̕\�������������Ȃ�Ȃ��悤�Ɍ��̐ݒ�ɖ߂��Ă���
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// �t�F�[�h����
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = static_cast<int>(255 * fadeRate);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

// �Q�[���I�[�o�[�p�v���C���[�̏�����
void SceneGameClear::InitGameClearPlayers()
{
	for (int i = 0; i < kNumGameClearPlayrers; ++i)
	{
		GameClearPlayer player;
		player.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // x���W�������_���ɐݒ�
		player.pos.y = kGameClearPlayerStartPosY;  // y���W�������ʒu�ɐݒ�
		player.fallSpeed = kGameClearPlayerFallSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameClearPlayerFallSpeedMax - kGameClearPlayerFallSpeedMin))); // �������x�������_���ɐݒ�
		player.rotationSpeed = kGameClearPlayerRotationSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameClearPlayerRotationSpeedMax - kGameClearPlayerRotationSpeedMin))); // ��]���x�������_���ɐݒ�
		player.angle = 0.0f; // ��]�p�x��������
		m_gameClearPlayers.push_back(player);	
	}
}

// �Q�[���I�[�o�[�p�v���C���[�̍X�V
void SceneGameClear::UpdateGameClearPlayers()
{
	for (auto& player : m_gameClearPlayers)
	{
		player.pos.y += player.fallSpeed;       // ����
		player.angle += player.rotationSpeed;   // ��]
		if (player.pos.y > Game::kScreenHeight) // ��ʊO�ɏo����Ĕz�u
		{
			player.pos.y = kGameClearPlayerStartPosY; // ��ʊO����o��
			player.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // ��ʓ��̃����_���Ȉʒu
		} 
	}
}

// �Q�[���I�[�o�[�p�v���C���[�̕`��
void SceneGameClear::DrawGameClearPlayers()
{
	for (const auto& player : m_gameClearPlayers)
	{
		DrawRotaGraph(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y), kScale, player.angle, m_gameClearPlayerHandle, true);
	}
}
