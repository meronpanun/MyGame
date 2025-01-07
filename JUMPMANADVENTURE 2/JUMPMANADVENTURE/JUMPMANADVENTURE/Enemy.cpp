#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"

Enemy::Enemy():
	m_animFrameCount(0),
	m_handle(-1),
	m_speed(2.0f),
	m_pos(800.0f,630.0f)
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
	m_velocity.x = m_speed;
	m_pos -= m_velocity;
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
