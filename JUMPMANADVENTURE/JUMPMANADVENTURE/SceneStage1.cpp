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
	// プレイヤーの初期位置
	constexpr float kPlayerInitPosX = 120.0f;
	constexpr float kPlayerInitPosY = 690.0f;

	// プレイヤーの画像サイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// マップチップのサイズ
	constexpr int kMapChipWidth = 32;
	constexpr int kMapChipHeight = 32;
}


SceneStage1::SceneStage1()
{
	// ゲーム画面描画先の作成
	m_gameScreenHandle = MakeScreen(Stage1::kMapWidth, Stage1::kMapHeight, true);

	// プレイヤーのメモリの確保
	m_pPlayer = new Player;

	// 背景のメモリの確保
	m_pBg = new BgStage1;
	m_pBg->SetPlayer(m_pPlayer);
}

SceneStage1::~SceneStage1()
{
	// 背景メモリの開放
	delete m_pBg;
	m_pBg = nullptr;

	// プレイヤーのメモリ解放
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void SceneStage1::Init()
{
	m_pPlayer->Init(m_pBg, this, { kPlayerInitPosX, kPlayerInitPosY });
	assert(m_pPlayer);

	// 背景の初期化
	m_pBg->Init();
}

void SceneStage1::Update()
{
	// 背景の更新
	m_pBg->Update();

	// プレイヤーの更新
	m_pPlayer->Update();
	// プレイヤーの現在地を取得
	m_playerPos = m_pPlayer->GetPos();
	// プレイヤーの当たり判定
	Rect playerRect = m_pPlayer->GetColRect();

}

void SceneStage1::Draw()
{
	// 描画先スクリーンをクリアする
	ClearDrawScreen();

	// 背景の描画
	m_pBg->Draw();
	
	// プレイヤーの描画
	m_pPlayer->Draw();
}
