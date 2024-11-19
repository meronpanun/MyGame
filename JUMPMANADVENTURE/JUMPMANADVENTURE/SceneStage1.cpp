#include "SceneStage1.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"

namespace
{
	// �v���C���[�̏����ʒu
	constexpr float kPlayerInitPosX = 120.0f;
	constexpr float kPlayerInitPosY = 640.0f;
}


SceneStage1::SceneStage1()
{
	// �Q�[����ʕ`���̍쐬
	m_gameScreenhandle = MakeScreen(Stage1::kMapWidth, Stage1::kMapHeight, true);

	// �v���C���[�̃������̊m��
	m_pPlayer = new Player;

	// �w�i�̃������̊m��
	m_pBg = new BgStage1;
	m_pBg->SetPlayer(m_pPlayer);
}

SceneStage1::~SceneStage1()
{
	// �v���C���[�̃��������
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// �w�i�������̊J��
	delete m_pBg;
	m_pBg = nullptr;
}

void SceneStage1::Init()
{
	m_pPlayer->Init(m_pBg, this, { kPlayerInitPosX, kPlayerInitPosY });
	m_pBg->Init();
}

void SceneStage1::Update()
{
	m_pPlayer->Update();
	// �v���C���[�̌��ݒn���擾
	m_playerPos = m_pPlayer->GetPos();
	// �v���C���[�̓����蔻��
	Rect player = m_pPlayer->GetColRect();

	m_pBg->Update();
}

void SceneStage1::Draw()
{
	m_pPlayer->Draw();

	m_pBg->Draw();
}
