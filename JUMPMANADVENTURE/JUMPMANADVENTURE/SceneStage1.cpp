#include "SceneStage1.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include <cassert>

namespace
{
	// �v���C���[�̏����ʒu
	constexpr float kPlayerInitPosX = 120.0f;
	constexpr float kPlayerInitPosY = 690.0f;

	// �v���C���[�̉摜�T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// �}�b�v�`�b�v�̃T�C�Y
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;
}


SceneStage1::SceneStage1()
{
	// �Q�[����ʕ`���̍쐬
	m_gameScreenHandle = MakeScreen(Stage1::kMapWidth, Stage1::kMapHeight, true);

	// �v���C���[�̃������̊m��
	m_pPlayer = new Player;

	// �w�i�̃������̊m��
	m_pBg = new BgStage1;
	m_pBg->SetPlayer(m_pPlayer);
}

SceneStage1::~SceneStage1()
{
	// �w�i�������̊J��
	delete m_pBg;
	m_pBg = nullptr;

	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneStage1::Init()
{
	m_pPlayer->Init(m_pBg, this, { kPlayerInitPosX, kPlayerInitPosY });
	assert(m_pPlayer);

	// �w�i�̏�����
	m_pBg->Init();
}

void SceneStage1::Update()
{
	// �w�i�̍X�V
	m_pBg->Update();

	// �v���C���[�̍X�V
	m_pPlayer->Update();
	// �v���C���[�̌��ݒn���擾
	m_playerPos = m_pPlayer->GetPos();
	// �v���C���[�̓����蔻��
	Rect playerRect = m_pPlayer->GetColRect();

}

void SceneStage1::Draw()
{
	// �`���X�N���[�����N���A����
	ClearDrawScreen();

	// �w�i�̕`��
	m_pBg->Draw();
	
	// �v���C���[�̕`��
	m_pPlayer->Draw();
}
