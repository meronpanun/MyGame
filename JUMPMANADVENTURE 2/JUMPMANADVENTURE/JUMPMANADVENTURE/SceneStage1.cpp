//#include "SceneStage1.h"
//#include "DxLib.h"
//#include "Rect.h"
//#include "Pad.h"
//#include "Game.h"
//#include "BgStage1.h"
//#include "Player.h"
//
//SceneStage1::SceneStage1()
//{
//	// �Q�[����ʕ`���̐���
//	m_gameScreenHandle = MakeScreen(Stage1::kBgStage1Width, Stage1::kBgStage1Height, true);
//
//	// �v���C���[�̃������m��
//	m_pPlayer = new Player;
//
//	// �w�i�̃������̊m��
//	m_pBg = new BgStage1;
//	m_pBg->SetPlayer(m_pPlayer);
//}
//
//SceneStage1::~SceneStage1()
//{
//	// �w�i�̃������J��
//	delete m_pBg;
//	m_pBg = nullptr;
//
//	// �v���C���[�̃������J��
//	delete m_pPlayer;
//	m_pPlayer = nullptr;
//}
//
//void SceneStage1::Init()
//{
//	// �v���C���[�̏�����
//	m_pPlayer->Init();
//
//	// �w�i�̏�����
//	m_pBg->Init();
//}
//
//void SceneStage1::Update()
//{
//	// �w�i�̍X�V
//	m_pBg->Update();
//
//	// �v���C���[�̍X�V
//	m_pPlayer->Update();
//	// �v���C���[�̌��݈ʒu���擾
//	m_playerPos = m_pPlayer->GetPos();
//	// �v���C���[�̓����蔻����擾
//	Rect playerRect = m_pPlayer->GetColRect();
//}
//
//void SceneStage1::Draw()
//{
//	// �w�i�̕`��
//	m_pBg->Draw();
//
//	// �v���C���[�̕`��
//	m_pPlayer->Draw();
//}
