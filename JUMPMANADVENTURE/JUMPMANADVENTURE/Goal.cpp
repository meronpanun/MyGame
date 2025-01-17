#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "BgStage1.h"
#include "Camera.h"

namespace
{
	// 半径
	constexpr int kRadius = 64;
	
	// ゴールの描画サイズ
	constexpr int kGraphWidth = 64;
	constexpr int kGraphHeight = 64;

	// ゴールのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 6;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// アニメーションのコマ数
	constexpr int kLoopAnimNum = 10;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 4;

	// 表示座標
	constexpr int kPosX = 5050;
	constexpr int kPosY = 595;

	// 拡大率
	constexpr double kScale = 2.0f;
}

Goal::Goal():
	m_pos(5050.0f,590.0f),
	m_animFrame(0),
	m_handle(0),
	m_index(0)
{
}

Goal::~Goal()
{
}

void Goal::Init(Camera* camera)
{
	m_pCamera = camera;
}

void Goal::Update()
{
	// アニメーションの進行
	m_animFrame++;
	if (m_animFrame >= kLoopAnimNum * kSingleAnimFrame)
	{
		m_animFrame = 0;
	}
}

void Goal::Draw()
{
	// グラフィックの切り出し位置(X座標)を計算で求める
	int animNo = m_animFrame / kSingleAnimFrame;

	// indexから表示位置を決定する
	int posX = kPosX + m_index;

	DrawRectRotaGraph(kPosX + m_pCamera->m_drawOffset.x, kPosY, 
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, 
		kScale, 0.0, 
		m_handle, true);
}

float Goal::GetRadius() const
{
	return kRadius;
}

bool Goal::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	// プレイヤーとゴールの半径の合計
	float Rlength = kRadius + pPlayer->GetRadius(); 
	// X成分の距離
	float delX = pPlayer->GetPos().x - m_pos.x; 
	// Y成分の距離
	float delY = pPlayer->GetPos().y - m_pos.y;

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{
		return true;
	}

	return false;
}
