#pragma once
#include <cmath>

class Player;
class Map;
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();



	
private:
	// ���ۂ̃J�����̃|�W�V����
	Vec2 m_pos;
	Vec2 m_drawOffset;

	// �v���C���[�|�C���^
	Player* m_pPlayer;
};

