#pragma once
#include "EnemyBase.h"
#include "Vec2.h"

class EnemyRock : public EnemyBase
{
public:
	EnemyRock();
	virtual ~EnemyRock();

	void Update();
	void Draw();

	enum Dir
	{
		kRunRight,
		kRunLeft
	};

private:
	// 敵の加速度
	Vec2 m_move;

	bool m_isturnFlag;

	// 向いている方向
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;
};

