#include "Camera.h"
#include "Player.h"
#include "Game.h"


namespace
{
	constexpr float CameraScopeRangeW = 400.0f;
	constexpr float CameraLerpRate = 0.15f;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update(const Player* player)
{
	// プレイヤーの位置がカメラの中央から一定以上離れたら
	// カメラの「目標」ポジションをその範囲に留める
	Vec2 aimCameraPos = m_pos;
	// x座標
	if (player->GetPos().x > m_pos.x + (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = player->GetPos().x - (CameraScopeRangeW * 0.5f);
	}
	else if (player->GetPos().x < m_pos.x - (CameraScopeRangeW * 0.5f))
	{
		aimCameraPos.x = player->GetPos().x + (CameraScopeRangeW * 0.5f);
	}

	// 目標ポジションに、Lerpを使ってカメラポジションを近づける
	m_pos = Lerp(m_pos, aimCameraPos, CameraLerpRate);

	// Draw側に足しているcamera.pos.xは反転させる
	m_drawOffset.x = m_pos.x * -1;

	// その時、画面中央にプレイヤーが来るようにする
	// (camera.pos画面中央になるようにする)
	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth * 0.5f);

}

Vec2 Camera::Lerp(Vec2 start, Vec2 end, float t)
{
	Vec2 ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	return ret;
}

