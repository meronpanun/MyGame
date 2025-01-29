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

	// �J�����̍��[�ʒu���擾
	float GetLeft() const;

	// ���`���
	static Vec2 Lerp(Vec2 start, Vec2 end, float t);

	// ��ʂ�h�炷
	void Shake(float intensity, int duration);

	// �J�����̈ʒu
	Vec2 m_pos;
	// �S�Ă�drawObject�ɑ����l
	Vec2 m_drawOffset;

	std::shared_ptr<Player> m_pPlayer;

private:
	float m_shakeIntensity;
	int m_shakeDuration;
};

