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
#include <vector>

namespace
{
	// �Q�[���I�[�o�[�̕������\�������܂ł̃t���[����
	constexpr int kGameoverFadeFrame = 60;

	// �Q�[���I�[�o�[�̕����\���ʒu
	constexpr int kGameoverPosY = 900;

	// Press A Button�̕\���ʒu
	constexpr int kPressAButtonPosX = 430;
	constexpr int kPressAButtonPosY = 550;


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
	constexpr int kGraphWidth = 30;
	constexpr int kGraphHeight = 28;

	// �Q�[���I�[�o�[�p�G�̏����ʒu�Ɨ������x
	constexpr float kGameOverEnemyStartPosY = -kGraphHeight * kScale; // ��ʊO����o��
	constexpr float kGameOverEnemyFallSpeedMin = 1.0f; // �������x�̍ŏ��l
	constexpr float kGameOverEnemyFallSpeedMax = 3.0f; // �������x�̍ő�l
	constexpr float kGameOverEnemyRotationSpeedMin = 0.02f; // ��]���x�̍ŏ��l
	constexpr float kGameOverEnemyRotationSpeedMax = 0.1f;  // ��]���x�̍ő�l
	constexpr int kNumGameOverEnemies = 10; // �Q�[���I�[�o�[�p�G�̐�
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
	m_gameOverEnemyAngle(0.0f),
	m_gameOverFrameCount(0),
	m_isAddingScore(false),
	m_bonusScore(0)
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
	m_enemyHandle = LoadGraph("data/image/Enemy.png");
	assert(m_enemyHandle != -1);

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

	// �Q�[���I�[�o�[�p�G�̏�����
	InitGameOverEnemies();
}

SceneMain::~SceneMain()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_lifeHandle);
	DeleteGraph(m_flagHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_poleHandle);
	DeleteGraph(m_enemyHandle);
	//BGM�����
	DeleteSoundMem(m_bgmHandle);
	// SE�����
	DeleteGraph(m_seHandle);
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

	// BGM�̍Đ��J�n�i���[�v�Đ��j
	PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);

	// �X�R�A�ƃ^�C�}�[�̏�����
	m_score = 0;
	m_timer = kInitialTimer;
}

SceneBase* SceneMain::Update()
{
	ChangeVolumeSoundMem(kVolumeBGM, m_bgmHandle);
	ChangeVolumeSoundMem(kVolumeSE, m_seHandle);


	// �S�[���ɓ����������ǂ������`�F�b�N
	if (m_pGoal->GetHitPlayerFlag(m_pPlayer))
	{
		m_isGoalHit = true;
		m_pPlayer->DisableControl(); // �v���C���[�̑���𖳌���
	}

	// �S�[���ɓ������Ă��Ȃ��ꍇ�̂݃v���C���[��Update���Ăяo��
	if (!m_isGoalHit)
	{
		m_pPlayer->Update();
	}

	if (m_isGameEnd)
	{
		// �Q�[���I�[�o�[�ɂȂ�����1�{�^������������t�F�[�h�A�E�g
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return new SceneTitle();
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
						// SE���Đ�
					//	PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
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
			// BGM���~
		//	StopSoundMem(m_bgmHandle);
			m_gameOverFrameCount++;
			if (m_gameOverFrameCount > kGameoverFadeFrame)
			{
				m_gameOverFrameCount = kGameoverFadeFrame;

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
		if (!m_isAddingScore)
		{
			m_score += m_timer * 10; // �^�C�}�[�̒l�����̂܂܃X�R�A�ɉ��Z
			m_isAddingScore = true;
		}

		// �X�R�A�ƃ^�C�}�[��n���ăV�[���J��
		return new SceneGameClear(m_score, m_timer);
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
				DrawFormatStringToHandle(kPressAButtonPosX, kPressAButtonPosY, 0xffffff, m_pFont->GetFont2(),"Press A Button");
			}

			// �������g�p���ĕϊ����s��
			float progressRate = static_cast<float>(m_gameOverFrameCount) / (kGameoverFadeFrame * 4);

			// ���������ۂ̓����x�ɕϊ�����
			int alpha = static_cast<int>(255 * (static_cast<float>(m_gameOverFrameCount) / kGameoverFadeFrame));

			// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

			// �Q�[���I�[�o�[�̕����̈ʒu���v�Z
			int width = GetDrawStringWidthToHandle("GAMEOVER", strlen("GAMEOVER"), m_pFont->GetFont1());
			int targetY = kGameoverPosY; // �Q�[���I�[�o�[�̕����̈ʒu
			int startY = -4; // ��ʊO����o��
			int gameOverY = static_cast<int>(startY + (targetY - startY) * progressRate); // �r���̈ʒu���v�Z

			// ��������ʒ����ɗ���悤�ɒ���
			if (gameOverY > targetY) {
				gameOverY = targetY;
			}

			// �Q�[���I�[�o�[�̕�����`��
			DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, gameOverY,
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

// �G�̐���
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

// �X�R�A�ƃ^�C�}�[�̃t�H���g�T�C�Y�̐ݒ�
void SceneMain::SetScoreAndTimerFontSize(int size)
{
	m_scoreAndTimerFontSize = size;
}

// �Q�[���I�[�o�[�p�G�̏�����
void SceneMain::InitGameOverEnemies()
{
	for (int i = 0; i < kNumGameOverEnemies; ++i) 
	{
		GameOverEnemy enemy; 
		enemy.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // x���W�������_���ɐݒ�
		enemy.pos.y = kGameOverEnemyStartPosY; // y���W�������ʒu�ɐݒ�
		enemy.fallSpeed = kGameOverEnemyFallSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameOverEnemyFallSpeedMax - kGameOverEnemyFallSpeedMin)));                 // �������x�������_���ɐݒ�
		enemy.rotationSpeed = kGameOverEnemyRotationSpeedMin + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (kGameOverEnemyRotationSpeedMax - kGameOverEnemyRotationSpeedMin))); // ��]���x�������_���ɐݒ�
		enemy.angle = 0.0f; // ��]�p�x��������
		m_gameOverEnemies.push_back(enemy); 
	}
}

// �Q�[���I�[�o�[�p�G�̍X�V
void SceneMain::UpdateGameOverEnemies()
{
	for (auto& enemy : m_gameOverEnemies)
	{
		enemy.pos.y += enemy.fallSpeed;        // �������x�����Ɉړ�
		enemy.angle += enemy.rotationSpeed;    // ��]�p�x���X�V
		if (enemy.pos.y > Game::kScreenHeight) // ��ʊO�ɏo����
		{
			enemy.pos.y = kGameOverEnemyStartPosY; // �����ʒu�ɖ߂�
			enemy.pos.x = static_cast<float>(rand() % Game::kScreenWidth); // x���W�������_���ɐݒ�
		}
	}
}

// �Q�[���I�[�o�[�p�G�̕`��
void SceneMain::DrawGameOverEnemies()
{
	for (const auto& enemy : m_gameOverEnemies)
	{
		DrawRotaGraph(enemy.pos.x, enemy.pos.y, kScale, enemy.angle, m_enemyHandle, true);
	}
}
