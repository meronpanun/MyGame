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
//	// ゲーム画面描画先の生成
//	m_gameScreenHandle = MakeScreen(Stage1::kBgStage1Width, Stage1::kBgStage1Height, true);
//
//	// プレイヤーのメモリ確保
//	m_pPlayer = new Player;
//
//	// 背景のメモリの確保
//	m_pBg = new BgStage1;
//	m_pBg->SetPlayer(m_pPlayer);
//}
//
//SceneStage1::~SceneStage1()
//{
//	// 背景のメモリ開放
//	delete m_pBg;
//	m_pBg = nullptr;
//
//	// プレイヤーのメモリ開放
//	delete m_pPlayer;
//	m_pPlayer = nullptr;
//}
//
//void SceneStage1::Init()
//{
//	// プレイヤーの初期化
//	m_pPlayer->Init();
//
//	// 背景の初期化
//	m_pBg->Init();
//}
//
//void SceneStage1::Update()
//{
//	// 背景の更新
//	m_pBg->Update();
//
//	// プレイヤーの更新
//	m_pPlayer->Update();
//	// プレイヤーの現在位置を取得
//	m_playerPos = m_pPlayer->GetPos();
//	// プレイヤーの当たり判定を取得
//	Rect playerRect = m_pPlayer->GetColRect();
//}
//
//void SceneStage1::Draw()
//{
//	// 背景の描画
//	m_pBg->Draw();
//
//	// プレイヤーの描画
//	m_pPlayer->Draw();
//}
