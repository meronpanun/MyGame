#include "Camera.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include <cmath>

namespace
{
	constexpr float CameraScopeRangeW = 400.0f;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	m_pos = Vec2(0, 0);
}

void Camera::Update()
{
	Vec2 aimCameraPos = m_pos;
	if (m_pPlayer->GetX() > m_pos.x + (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = m_pos.x - (CameraScopeRangeW * 0.5f);
	}
	else if (m_pPlayer->GetX() > m_pos.x - (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = m_pos.x + (CameraScopeRangeW * 0.5f);
	}

	m_drawOffset.x = m_pos.x * -1;

	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth * 0.5f);
}

