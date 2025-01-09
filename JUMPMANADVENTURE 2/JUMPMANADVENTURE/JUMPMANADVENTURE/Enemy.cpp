#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"
#include "BgStage1.h"

namespace
{
	// 敵のサイズ	
	constexpr int kWidth = 30;
	constexpr int kHeight = 30;

	// 敵の描画サイズ
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 28;

	// 速度
	constexpr float kSpeed = 2.5f;

	// 重力
	constexpr float kGravaity = 0.5f;

	// キャラクターのアニメーション
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;
}

Enemy::Enemy():
	m_move(0.0f, 0.0f),
	m_animFrame(0),
	m_animCount(0)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	DrawBox(m_pos.x, m_pos.y, m_pos.x + 33, m_pos.y + 33, 0x000000, true);
	if (m_pos.x > Game::kScreenWidth)
	{
		m_pos.x = 0 - 33;
	}
}

float Enemy::GetLeft() const
{
	return m_pos.x;
}

float Enemy::GetTop() const
{
	return m_pos.y;
}

float Enemy::GetRigth() const
{
	return m_pos.x + 38;
}

float Enemy::GetBottom() const
{
	return m_pos.y + 33;
}
