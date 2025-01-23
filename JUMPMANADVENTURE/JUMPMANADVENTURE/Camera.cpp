#include "Camera.h"
#include "Player.h"
#include "Game.h"


namespace
{
	// カメラ範囲
	constexpr float kCameraScopeRangeW = 400.0f;
	// カメラのLerp率
	constexpr float kCameraLerpRate = 0.15f;  
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
	if (player->GetPos().x > m_pos.x + (kCameraScopeRangeW * 0.5f))	// 右スクロール
	{
		aimCameraPos.x = player->GetPos().x - (kCameraScopeRangeW * 0.5f);
	}
	if (player->GetPos().x < m_pos.x)
	{
		m_pos.x = player->GetPos().x;
	}

	// 目標ポジションに、Lerpを使ってカメラポジションを近づける
	m_pos = Lerp(m_pos, aimCameraPos, kCameraLerpRate);

	// Draw側に足しているcamera.pos.xは反転させる
	m_drawOffset.x = m_pos.x * -1;

	// その時、画面左側にプレイヤーが来るようにする
	// (camera.pos画面中央になるようにする)
	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth - 1155);
}

Vec2 Camera::Lerp(Vec2 start, Vec2 end, float t) 
{
	Vec2 ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t); 
	return ret;
}

