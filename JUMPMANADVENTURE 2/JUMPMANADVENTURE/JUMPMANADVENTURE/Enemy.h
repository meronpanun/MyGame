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

	// �G�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;


private:
	Vec2 m_pos;
	Vec2 m_velocity;
	
	// �G�̃O���t�B�b�N�n���h��
	int m_handle;

	int m_animFrameCount;

	int m_speed;
};

