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
	// �G�̉����x
	Vec2 m_move;

	// �A�j���[�V�����̃t���[��
	int m_animFrame;
	// �A�j���[�V�����̃J�E���g
	int m_animCount;
};

