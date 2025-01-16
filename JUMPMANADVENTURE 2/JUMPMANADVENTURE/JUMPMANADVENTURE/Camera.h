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

	// ���`���
//	static Vec2 Lerp(Vec2 start, Vec2 end, float t);

	// �J�����̈ʒu
	Vec2 m_pos;
	// �S�Ă�drawObject�ɑ����l
	Vec2 m_drawOffset;

	std::shared_ptr<Player> m_pPlayer;
};

