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
	// �G�̉����x
	Vec2 m_move;

	bool m_isturnFlag;

	// �����Ă������
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	// �A�j���[�V�����̃t���[��
	int m_animFrame;
	// �A�j���[�V�����̃J�E���g
	int m_animCount;
};

