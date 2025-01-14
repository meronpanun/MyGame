#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "BgStage1.h"
#include "Camera.h"

namespace
{
	// 半径
	constexpr int kRadius = 32;
	
	// ゴールの描画サイズ
	constexpr int kGraphWidth = 64;
	constexpr int kGraphHeight = 64;

	// ゴールのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 6;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Goal::Goal():
	m_pos(5000.0f,610.0f),
	m_animFrame(0),
	m_handle(0)
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
	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle)
	{
		m_animFrame = 0;
	}
}

void Goal::Draw()
{
	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kGraphWidth;
	int srcY = kGraphHeight * 0;

	DrawRectRotaGraph(32 + m_pCamera->m_drawOffset.x, 32, srcX, srcY, kGraphWidth, kGraphHeight, 1.0, 0.0, m_handle, true, false);
}

float Goal::GetRadius()
{
	return kRadius;
}

bool Goal::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	float Rlength = kRadius + pPlayer->GetRadius(); // プレイヤーとゴールの半径の合計
	float delX = pPlayer->GetPos().x - m_pos.x; // X成分の距離
	float delY = pPlayer->GetPos().y - m_pos.y; // Y成分の距離

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{
		return true;
	}

	return false;
}
