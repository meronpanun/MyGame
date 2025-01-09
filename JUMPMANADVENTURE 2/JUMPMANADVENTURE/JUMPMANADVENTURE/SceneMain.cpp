#include "SceneMain.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Life.h"
#include <memory>
#include <cassert>

namespace
{
	// �Q�[���I�[�o�[�̕������\�������܂ł̃t���[����
	constexpr int kGameoverFadeFrame = 60;

	// �����̓_��
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;
}

SceneMain::SceneMain():
	m_fadeFrameCount(0),
	m_lifeHandle(-1)
{

}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// �t�H���g�̐���
	m_fontHandle = CreateFontToHandle("Bodoni MT Black", 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	// �O���t�B�b�N�̓ǂݍ���
	m_lifeHandle = LoadGraph("data/image/life.png");
	assert(m_lifeHandle != -1);

	m_pPlayer = std::make_shared<Player>();
	m_pBgStage1 = std::make_shared<BgStage1>();
	m_pCamera = std::make_shared<Camera>();
	m_pEnemy = std::make_shared<Enemy>();

	m_pPlayer->Init(m_pCamera.get());
	m_pBgStage1->Init(m_pCamera.get());
	m_pCamera->Init();
	m_pEnemy->Init();

	for (int i = 0; i < 3; i++)
	{
		m_life[i].Init();
		m_life[i].SetHandle(m_lifeHandle);
		m_life[i].SetIndex(i);
	}
}

SceneManager::SceneSelect SceneMain::Update()
{
	if (m_isGameEnd)
	{
		// �Q�[���I�[�o�[�ɂȂ�����1�{�^������������t�F�[�h�A�E�g
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::kSceneTitle;
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
	m_pEnemy->Update();
//	Pad::Update();

	for (int i = 0; i < 3; i++)
	{
		m_life[i].Update();
	}

	// �Q�[���I�[�o�[���o
	if (m_pPlayer->GetHp() <= 0)
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
	}

	// 1�b�T�C�N���ŕ\���A��\���؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// �v���C���[�ƓG�̓����蔻��
	bool isPlayerHit = true;

	if (m_pPlayer->GetLeft() > m_pEnemy->GetRigth())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetTop() > m_pEnemy->GetBottom())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetRigth() < m_pEnemy->GetLeft())
	{
		isPlayerHit = false;
	}
	if (m_pPlayer->GetBottom() < m_pEnemy->GetTop())
	{
		isPlayerHit = false;
	}

	// isPlayerHit = true�Ȃ瓖�����Ă���Afalse�Ȃ瓖�����Ă��Ȃ�
	if (isPlayerHit)
	{
		m_pPlayer->OnDamage();
	}

	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�X�e�[�W1��ʂ̂܂�)
	return SceneManager::SceneSelect::kSceneStage1;
}

void SceneMain::Draw()
{
	m_pBgStage1->Draw();
	m_pPlayer->Draw();
	m_pEnemy->Draw();

	for (int i = 0; i < m_pPlayer->GetHp(); i++)
	{
		m_life[i].Draw();
	}

	// �Q�[���I�[�o�[�̕\��
	if (m_pPlayer->GetHp() <= 0)
	{
		// ��ʑS�̂����F�œh��ׂ�
		DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

		if (m_blinkFrameCount < kBlinkDispFrame)
		{
			DrawString(580, 600, "Press A Button", 0xffffff);
		}

		// �������g�p���ĕϊ����s��
		// m_gameoverFrameCount ��i�s�����ɕϊ�����
		float progressRate = static_cast<float>(m_gameoverFrameCount) / kGameoverFadeFrame;

		// ���������ۂ̓����x�ɕϊ�����
		int alpha = static_cast<float>(255 * progressRate);

		// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		int width = GetDrawStringWidthToHandle("GAMEOVER", strlen("GAMEOVER"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth * 0.5 - width * 0.5, Game::kScreenHeight * 0.5 - 64 * 0.5,
			"GAMEOVER", 0xff0000, m_fontHandle);
		// �ȍ~�̕\�������������Ȃ�Ȃ��悤�Ɍ��̐ݒ�ɖ߂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
