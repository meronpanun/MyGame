#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "SceneGameClear.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Life.h"
#include "Goal.h"
#include "FontManager.h"
#include <memory>
#include <cassert>

namespace
{
	// �Q�[���I�[�o�[�̕������\�������܂ł̃t���[����
	constexpr int kGameoverFadeFrame = 60;

	// �����̓_��
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// �^�C�}�[�̏����l
	constexpr int kInitialTimer = 400;
	// �^�C�}�[�̃J�E���g�_�E���Ԋu�i0.4�b�j
	constexpr int kTimerCountdownInterval = 24; // 60FPS�̏ꍇ�A0.4�b��24�t���[��
	// �^�C�}�[�ƃX�R�A�̕\���ʒu
	constexpr int kTimerPosX = 760;
	constexpr int kScorePosX = 480;
	constexpr int kScoreAndTimerPosY = 55;
	constexpr int kTimerPosX2 = 720;
	constexpr int kScorePosX2 = 420;
	constexpr int kScoreAndTimerPosY2 = 20;

	// 1000�s�N�Z���͈̔�
	constexpr float kEnemyActivationRange = 1000.0f; 

	// �̗͂̍ő�l
	constexpr int kMaxHp = 3;

	// �w�i��1�̃T�C�Y
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;

	// ����
	constexpr int kVolumeBGM = 128;
	constexpr int kVolumeSE = 128;

	// �g�嗦
	constexpr float kScale = 2.0f;

	// �Q�[���I�[�o�[�p�G�̕`��T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// �Q�[���I�[�o�[�p�G�̏����ʒu�Ɨ������x
	constexpr float kGameOverEnemyStartPosY = -kGraphHeight * kScale;
	constexpr float kGameOverEnemyFallSpeedMin = 1.0f;
	constexpr float kGameOverEnemyFallSpeedMax = 3.0f;
	constexpr float kGameOverEnemyRotationSpeedMin = 0.02f;
	constexpr float kGameOverEnemyRotationSpeedMax = 0.1f;
	constexpr int kNumGameOverEnemies = 5;
}

SceneMain::SceneMain():
	m_isGameEnd(false),
	m_isGoalHit(false),
	m_fadeFrameCount(0),
	m_lifeHandle(-1),
	m_score(0), 
	m_timer(kInitialTimer),
	m_bgScrollY(0),
	m_gameOverEnemyPosY(kGameOverEnemyStartPosY),
	m_gameOverEnemyAngle(0.0f)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_lifeHandle = LoadGraph("data/image/heart.png");
	assert(m_lifeHandle != -1);
	m_flagHandle = LoadGraph("data/image/flag.png");
	assert(m_flagHandle != -1);
	m_poleHandle = LoadGraph("data/image/pole.png");
	assert(m_poleHandle != -1);
	m_bgHandle = LoadGraph("data/image/Purple.png");
	assert(m_bgHandle != -1);
	m_playerDaedHandle = LoadGraph("data/image/PlayerDead.png");
	assert(m_playerDaedHandle != -1);

	//BGM�̓ǂݍ���
//	m_bgmHandle = LoadSoundMem("data/MusMus-BGM-125.mp3");
//	assert(m_bgmHandle != -1);

	// SE�̓ǂݍ���
//	m_seHandle = LoadSoundMem("data/����{�^��������49.mp3");
//	assert(m_seHandle != -1);


	m_pGoal = std::make_shared<Goal>();
	m_pGoal->SetHandle(m_flagHandle);
	m_pGoal->SetPoleHandle(m_poleHandle);

	// �G�̐�����
	m_pEnemy.resize(20);

	// �e�G�̏����ʒu
	CreateEnemy(1600, 625);
	CreateEnemy(2650, 625);
	CreateEnemy(3100, 625);
	CreateEnemy(3180, 625);
	CreateEnemy(4450, 200);
	CreateEnemy(4550, 200);
	CreateEnemy(5250, 625);
	CreateEnemy(5350, 625);
	CreateEnemy(5600, 625);
	CreateEnemy(5900, 625);
	CreateEnemy(6000, 625);
	CreateEnemy(6450, 625);
	CreateEnemy(6550, 625);
}

SceneMain::~SceneMain()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_lifeHandle);
	DeleteGraph(m_flagHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_poleHandle);
	DeleteGraph(m_playerDaedHandle);
	//BGM�����
	DeleteSoundMem(m_bgmHandle);
	// SE�����
	DeleteGraph(m_seHandle);
}

void SceneMain::Init()
{
	
}

SceneBase* SceneMain::Update()
{


	// �Q�[���I�[�o�[���o
	if (m_pPlayer->GetHp() <= 0 || m_timer <= 0)  // �v���C���[��HP��0�܂��͐������Ԃ�0�ɂȂ����ꍇ
	{
		// �v���C���[�̃Q�[���I�[�o�[�t���O���m�F���^�C�}�[��0�ɂȂ����ꍇ
		if (m_pPlayer->IsGameOver() || m_timer <= 0)
		{
			// BGM���~
		//	StopSoundMem(m_bgmHandle);
			m_gameoverFrameCount++;
			if (m_gameoverFrameCount > kGameoverFadeFrame)
			{
				m_gameoverFrameCount = kGameoverFadeFrame;

				// �Q�[���I�[�o�[�̕������\�����ꂫ������A
				// 1�{�^������������^�C�g���ɖ߂�
				if (Pad::IsTrigger(PAD_INPUT_1))
				{
					m_isGameEnd = true;
				}
			}
			// �w�i�̃X�N���[���ʒu���X�V
			m_bgScrollY += 1; // �X�N���[�����x�𒲐�
			if (m_bgScrollY > Game::kScreenHeight)
			{
				m_bgScrollY = 0;
			}

			// �Q�[���I�[�o�[�p�G�̈ʒu�Ɖ�]�p�x���X�V
			UpdateGameOverEnemies();
		}
	}

	// �S�[���I�u�W�F�N�g�ɓ���������
	if (m_isGoalHit)
	{
		return new SceneGameClear(); 
		m_isGoalHit = true;
	}

	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�X�e�[�W1��ʂ̂܂�)
	return this;
}
	

void SceneMain::Draw()
{
	m_pBgStage1->Draw(); 
	m_pPlayer->Draw();
	m_pGoal->Draw();

	// �G�̕`��
	for (auto& enemy : m_pEnemy)
	{
		if (enemy)
		{
			enemy->Draw();
		}
	}
	 
	// �̗͂̕`��
	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		m_life[i].Draw();
	}

	// �X�R�A�̕\��
	DrawFormatStringToHandle(kScorePosX2, kScoreAndTimerPosY2, 0xffffff, m_pFont->GetFont(), "Score");
	DrawFormatStringToHandle(kScorePosX, kScoreAndTimerPosY, 0xffffff, m_pFont->GetFont(), "%d", m_score);

	// �^�C�}�[�̕\��
	DrawFormatStringToHandle(kTimerPosX2, kScoreAndTimerPosY2, 0xffffff, m_pFont->GetFont(), "Time");
	DrawFormatStringToHandle(kTimerPosX, kScoreAndTimerPosY, 0xffffff, m_pFont->GetFont(), "%d" , m_timer);

	// �Q�[���I�[�o�[�̉��o�̕\��
	if (m_pPlayer->GetHp() <= 0 || m_timer <= 0) // �v���C���[��HP��0�܂��͐������Ԃ�0�ɂȂ����ꍇ
	{
		// �v���C���[�̃Q�[���I�[�o�[�t���O���m�F���^�C�}�[��0�ɂȂ����ꍇ
		if (m_pPlayer->IsGameOver() || m_timer <= 0)
		{
			
			// �w�i���X�N���[�����ĕ`��
			for (int y = m_bgScrollY - Game::kScreenHeight; y < Game::kScreenHeight; y += kChipHeight)
			{
				for (int x = 0; x < Game::kScreenWidth; x += kChipWidth)
				{
					DrawGraph(x, y,  m_bgHandle, true);
				}
			}

			// �Q�[���I�[�o�[�p�G�̕`��
			DrawGameOverEnemies();

			if (m_blinkFrameCount < kBlinkDispFrame)
			{
				DrawFormatStringToHandle(430, 600, 0xffffff, m_pFont->GetFont2(),"Press A Button");
			}

			// �������g�p���ĕϊ����s��
			// m_gameoverFrameCount ��i�s�����ɕϊ�����
			float progressRate = static_cast<float>(m_gameoverFrameCount) / kGameoverFadeFrame;

			// ���������ۂ̓����x�ɕϊ�����
			int alpha = static_cast<int>(255 * progressRate);

			// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			int width = GetDrawStringWidthToHandle("GAMEOVER", strlen("GAMEOVER"), m_pFont->GetFont1());
			DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
				"GAMEOVER", 0xffffff, m_pFont->GetFont1());
			// �ȍ~�̕\�������������Ȃ�Ȃ��悤�Ɍ��̐ݒ�ɖ߂��Ă���
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	
	}

	// �t�F�[�h����
	int fadeAlpha = 0;

	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
}

void SceneMain::CreateEnemy(float x, float y)
{
	for (int i = 0; i < m_pEnemy.size(); i++)
	{
		if (!m_pEnemy[i])
		{
			m_pEnemy[i] = std::make_shared<Enemy>();
			m_pEnemy[i]->SetPos(x, y);
			break;
		}
	}
}

void SceneMain::SetScoreAndTimerFontSize(int size)
{
	m_scoreAndTimerFontSize = size;
}

void SceneMain::InitGameOverEnemies()
{
}

void SceneMain::UpdateGameOverEnemies()
{
}

void SceneMain::DrawGameOverEnemies()
{
}
