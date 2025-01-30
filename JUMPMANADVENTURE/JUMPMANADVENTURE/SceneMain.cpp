#include "SceneMain.h"
#include "SceneManager.h"
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
	constexpr int kTimerPosX2 = 720;
	constexpr int kScorePosX = 480;
	constexpr int kScorePosX2 = 420;
	constexpr int kScoreAndTimerPosY = 55;
	constexpr int kScoreAndTimerPosY2 = 20;

	// 1000�s�N�Z���͈̔�
	constexpr float kEnemyActivationRange = 1000.0f; 

	// �̗͂̍ő�l
	constexpr int kMaxHp = 3;

	// �w�i��1�̃T�C�Y
	constexpr int kChipWidth = 64;
	constexpr int kChipHeight = 64;
}

SceneMain::SceneMain():
	m_isGameEnd(false),
	m_isGoalHit(false),
	m_fadeFrameCount(0),
	m_lifeHandle(-1),
	m_score(0), 
	m_timer(kInitialTimer),
	m_bgScrollY(0)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_lifeHandle = LoadGraph("data/image/heart.png");
	assert(m_lifeHandle != -1);
	m_goalHandle = LoadGraph("data/image/GoalFlag.png");
	assert(m_lifeHandle != -1);
	m_bgHandle = LoadGraph("data/image/Purple.png");
	assert(m_bgHandle != -1);

	m_pGoal = std::make_shared<Goal>();
	m_pGoal->SetHandle(m_goalHandle);

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
	DeleteGraph(m_goalHandle);
	DeleteGraph(m_bgHandle);
}

void SceneMain::Init()
{
	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>(); 
	m_pCamera = std::make_shared<Camera>(); 
	m_pFont = std::make_shared<FontManager>();

	m_pPlayer->Init(m_pCamera.get());
	m_pBgStage1->Init(m_pCamera.get());
	m_pCamera->Init();
	m_pGoal->Init(m_pCamera.get());

	// �G�̏�����
	for (auto& enemy : m_pEnemy)
	{
		if (enemy)
		{
			enemy->Init(m_pCamera.get());
		}
	}

	// �̗͂̏�����
	m_life.resize(kMaxHp);
	for (int i = 0; i < m_life.size(); i++)
	{
		m_life[i].Init();
		m_life[i].SetHandle(m_lifeHandle);
		m_life[i].SetIndex(i);
	}

	// �X�R�A�ƃ^�C�}�[�̏�����
	m_score = 0;
	m_timer = kInitialTimer;
}

SceneManager::SceneSelect SceneMain::Update()
{
	// �S�[���ɓ����������ǂ���
	m_isGoalHit = m_pGoal->GetHitPlayerFlag(m_pPlayer);

	if (m_isGameEnd)
	{
		// �Q�[���I�[�o�[�ɂȂ�����1�{�^������������t�F�[�h�A�E�g
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::SceneSelect::kSceneTitle;
		}
	}
	else
	{
		// �t�F�[�h�C������
		m_fadeFrameCount++;
		if (m_fadeFrameCount > 30)
		{
			m_fadeFrameCount = 30;
		}
	}

	m_pPlayer->Update();
	m_pBgStage1->Update(m_pPlayer.get());
	m_pCamera->Update(m_pPlayer.get());
	m_pGoal->Update();

	// �v���C���[�����S��ԂłȂ��ꍇ�̂ݓG�̍X�V�ƃ^�C�}�[�̍X�V���s��
	if (m_pPlayer->GetHp() > 0)
	{
		// �G�̍X�V
		Vec2 playerPos = m_pPlayer->GetPos();
		for (auto& enemy : m_pEnemy)
		{
			if (enemy && enemy->IsAlive())
			{
				if (enemy->IsPlayerInRange(playerPos, kEnemyActivationRange))
				{
					enemy->Activate(); // �G���A�N�e�B�u�ɂ���
				}
				if (enemy->IsActive())
				{
					enemy->Update();   // �A�N�e�B�u�ȓG���X�V
				}
			}
		}

		// �^�C�}�[�̃J�E���g�_�E��
		static int timerFrameCount = 0;
		timerFrameCount++;
		if (timerFrameCount >= kTimerCountdownInterval)
		{
			timerFrameCount = 0;
			if (m_timer > 0)
			{
				m_timer--;
			}
		}

		// �̗͂̍X�V
		for (int i = 0; i < m_life.size(); i++)
		{
			m_life[i].Update();
		}

		// �v���C���[�ƓG�̓����蔻��
		for (auto& enemy : m_pEnemy)
		{
			if (enemy && enemy->IsAlive())
			{
				bool isPlayerHit = true;
				// ��΂ɓ�����Ȃ��p�^�[��
				if (m_pPlayer->GetLeft() > enemy->GetRigth())
				{
					isPlayerHit = false;
				}
				if (m_pPlayer->GetTop() > enemy->GetBottom())
				{
					isPlayerHit = false;
				}
				if (m_pPlayer->GetRigth() < enemy->GetLeft())
				{
					isPlayerHit = false;
				}
				if (m_pPlayer->GetBottom() < enemy->GetTop())
				{
					isPlayerHit = false;
				}

				// isPlayerHit = true�Ȃ瓖�����Ă���Afalse�Ȃ瓖�����Ă��Ȃ�
				if (isPlayerHit)
				{
					if (m_pPlayer->GetBottom() < enemy->GetTop() + 50 && m_pPlayer->GetMoveY() > 0) // �v���C���[���G�̏�ɓ��������ꍇ
					{
						enemy->SetAlive(false);    // �G������
						m_pPlayer->JumpOnEnemy();  // �v���C���[�������W�����v
						m_score += 100;            // �G��|���ƃX�R�A��100�|�C���g����
					}
					else
					{
						m_pPlayer->OnDamage();	   // �v���C���[���_���[�W���󂯂�
					}
				}
			}
		}
	}

	// 1�b�T�C�N���ŕ\���A��\���؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// �Q�[���I�[�o�[���o
	if (m_pPlayer->GetHp() <= 0 || m_timer <= 0)  // �v���C���[��HP��0�܂��͐������Ԃ�0�ɂȂ����ꍇ
	{
		// �v���C���[�̃Q�[���I�[�o�[�t���O���m�F���^�C�}�[��0�ɂȂ����ꍇ
		if (m_pPlayer->IsGameOver() || m_timer <= 0)
		{
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
		}
	}

	// �S�[���I�u�W�F�N�g�ɓ���������
	if (m_isGoalHit)
	{
		return SceneManager::SceneSelect::kSceneGameClear;
		m_isGoalHit = true;
	}

	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�X�e�[�W1��ʂ̂܂�)
	return SceneManager::SceneSelect::kSceneStage1;
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
					DrawGraph(x, y, m_bgHandle, true);
				}
			}

			if (m_blinkFrameCount < kBlinkDispFrame)
			{
				DrawFormatStringToHandle(500, 600, 0xffffff, m_pFont->GetFont2(),"Press A Button");
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
