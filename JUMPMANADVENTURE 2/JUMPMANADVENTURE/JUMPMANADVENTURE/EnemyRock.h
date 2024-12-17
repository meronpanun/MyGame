#pragma once
#include "EnemyBase.h"
#include "Vec2.h"

class EnemyRock : public EnemyBase
{
public:
	EnemyRock();
	~EnemyRock();

	void Update();
	void Draw();

private:
	// 敵の加速度
	Vec2 m_move;

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;
};

