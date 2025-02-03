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
}

SceneGameClear::SceneGameClear(int score, int goalHitTime, int bonusTimer) :
	m_blinkFrameCount(0),
	m_fadeFrameCount(0),
	m_gameClearFrameCount(0),
	m_bgScrollY(0),
	m_gameClearPlayerPosY(kGameClearPlayerStartPosY),
	m_gameClearPlayerAngle(0.0f),
	m_waveFrameCount(0),
	m_score(score),
	m_goalHitTime(goalHitTime),
	m_bonusTimer(bonusTimer)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_gameClearBgHandle = LoadGraph("data/image/Yellow.png");
	assert(m_gameClearBgHandle != -1);
	m_gameClearPlayerHandle = LoadGraph("data/image/Player.png");
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

	// �������g�p���ĕϊ����s��
   	float progressRate = static_cast<float>(m_gameClearFrameCount) / kGameClearFadeFrame;

	// ���������ۂ̓����x�ɕϊ�����
	int alpha = static_cast<int>(255 * progressRate);
	// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int width = GetDrawStringWidthToHandle("GAMECLEAR", strlen("GAMECLEAR"), m_pFont->GetFont1());

	// �E�F�[�u�A�j���[�V������K�p���ĕ�����`��
	const int charSpacing = 60;     // �����Ԋu���L���邽�߂̃X�y�[�X
	const int specialSpacing = 100; // M��E�̊Ԋu���L���邽�߂̃X�y�[�X
	int xOffset = -50;              // ������X���W�̃I�t�Z�b�g

	for (int i = 0; i < strlen("GAMECLEAR"); ++i)
	{
		float waveOffset = kWaveAmplitude * std::sin((m_waveFrameCount + i * 10) * kWaveFrequency); // �E�F�[�u�A�j���[�V�����̃I�t�Z�b�g
		DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5 + xOffset, 100 + waveOffset,
			std::string(1, "GAMECLEAR"[i]).c_str(), 0xffffff, m_pFont->GetFont1());

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

	// �X�R�A�̕\��
	DrawFormatStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, 300, 0xffffff, m_pFont->GetFont1(), "Score: %d", m_score);

	// �^�C�}�[�̕\��
	DrawFormatStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, 400, 0xffffff, m_pFont->GetFont1(), "Time: %d", m_goalHitTime);

	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		DrawFormatStringToHandle(400, 600, 0xffffff, m_pFont->GetFont2(), "Press A Button");
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

// �Q�[���I�[�o�[�p�G�̏�����
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

// �Q�[���I�[�o�[�p�G�̍X�V
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

// �Q�[���I�[�o�[�p�G�̕`��
void SceneGameClear::DrawGameClearPlayers()
{
	for (const auto& enemy : m_gameClearPlayers)
	{
		DrawRotaGraph(enemy.pos.x, enemy.pos.y, kScale, enemy.angle, m_gameClearPlayerHandle, true);
	}
}
