#include "SceneStage1.h"
#include "DxLib.h"
#include "Pad.h"
#include "Rect.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"

namespace
{
	// プレイヤーの初期位置
	constexpr float kPlayerInitPosX = 120.0f;
	constexpr float kPlayerInitPosY = 640.0f;
}


SceneStage1::SceneStage1()
{
	// ゲーム画面描画先の作成
	m_gameScreenhandle = MakeScreen(Stage1::kMapWidth, Stage1::kMapHeight, true);

	// プレイヤーのメモリの確保
	m_pPlayer = new Player;

	// 背景のメモリの確保
	m_pBg = new BgStage1;
	m_pBg->SetPlayer(m_pPlayer);
}

SceneStage1::~SceneStage1()
{
	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;

	// 背景メモリの開放
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
	// プレイヤーの現在地を取得
	m_playerPos = m_pPlayer->GetPos();
	// プレイヤーの当たり判定
	Rect player = m_pPlayer->GetColRect();

	m_pBg->Update();
}

void SceneStage1::Draw()
{
	m_pPlayer->Draw();

	m_pBg->Draw();
}
