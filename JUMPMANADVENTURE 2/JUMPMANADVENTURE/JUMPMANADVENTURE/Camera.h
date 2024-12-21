#pragma once
#include "Vec2.h"

class Player;
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update(const Player* player);

	// カメラの位置
	Vec2 m_pos;
	// 全てのdrawObjectに足す値
	Vec2 m_drawOffset;
};

