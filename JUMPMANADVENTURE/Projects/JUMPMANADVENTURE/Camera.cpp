#include "Camera.h"
#include "Player.h"
#include "Game.h"
#include <cmath> 

namespace
{
	// カメラ範囲
	constexpr float kCameraScopeRangeW = 400.0f;
	// カメラのLerp率
	constexpr float kCameraLerpRate = 0.15f;  
}

Camera::Camera():
	m_shakeDuration(0), 
	m_shakeIntensity(0.0f)
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

	// 目標ポジションに、Lerpを使ってカメラポジションを近づける
	m_pos = Lerp(m_pos, aimCameraPos, kCameraLerpRate);

	// Draw側に足しているcamera.pos.xは反転させる
	m_drawOffset.x = m_pos.x * -1;

	// 画面左側にプレイヤーが来るようにする
	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth - 1155);

	// 画面揺れの処理
	if (m_shakeDuration > 0) 
	{
		m_shakeDuration--; // 揺れの時間を減らす
		float shakeOffsetX = (rand() % 100 - 50) / 50.0f * m_shakeIntensity; // X軸の揺れを計算
		float shakeOffsetY = (rand() % 100 - 50) / 50.0f * m_shakeIntensity; // Y軸の揺れを計算
		m_drawOffset.x += shakeOffsetX; // X軸に揺れを適用
		m_drawOffset.y += shakeOffsetY; // Y軸に揺れを適用
	}
}

// カメラの左端位置を取得
float Camera::GetLeft() const
{
	return m_pos.x - 100;
}

// 線形補間
Vec2 Camera::Lerp(Vec2 start, Vec2 end, float t)
{
	Vec2 ret;
	ret.x = std::lerp(start.x, end.x, t);
	ret.y = std::lerp(start.y, end.y, t);
	return ret;
}

// 画面を揺らす
void Camera::Shake(float intensity, int duration)
{
	m_shakeIntensity = intensity; // 揺れの強度を設定
	m_shakeDuration = duration;   // 揺れの時間を設定
}

