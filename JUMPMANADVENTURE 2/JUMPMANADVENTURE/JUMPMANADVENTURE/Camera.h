#pragma once
#include "Vec2.h"
#include <memory>

class Player;
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update(const Player* player);

	// 線形補間
//	static Vec2 Lerp(Vec2 start, Vec2 end, float t);

	// カメラの位置
	Vec2 m_pos;
	// 全てのdrawObjectに足す値
	Vec2 m_drawOffset;

	std::shared_ptr<Player> m_pPlayer;
};

