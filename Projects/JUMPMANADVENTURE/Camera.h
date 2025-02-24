#pragma once
#include "Vec2.h"
#include <memory>

class Player;

/// <summary>
/// カメラクラス
/// <summary>
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update(const Player* player);

	// カメラの左端位置を取得
	float GetLeft() const;

	// 線形補間
	static Vec2 Lerp(Vec2 start, Vec2 end, float t);

	// 画面を揺らす
	void Shake(float intensity, int duration);

	// カメラの位置
	Vec2 m_pos;
	// 全てのdrawObjectに足す値
	Vec2 m_drawOffset;

	std::shared_ptr<Player> m_pPlayer;

private:
	// 画面揺れの強度
	float m_shakeIntensity;
	// 画面揺れの時間
	int m_shakeDuration;
};

