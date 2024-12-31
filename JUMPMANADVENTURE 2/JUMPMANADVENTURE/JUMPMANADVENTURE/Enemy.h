#pragma once
#include "Vec2.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void Update();
	void Draw();

private:
	Vec2 m_pos;
	Vec2 veloctiy;
	
	// 敵のグラフィックハンドル
	int m_handle;

	int m_animFrameCount;

	int m_speed;
};

