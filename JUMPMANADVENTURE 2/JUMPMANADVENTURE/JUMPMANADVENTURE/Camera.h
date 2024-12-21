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

	// �J�����̈ʒu
	Vec2 m_pos;
	// �S�Ă�drawObject�ɑ����l
	Vec2 m_drawOffset;
};

