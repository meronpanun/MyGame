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
	// 実際のカメラのポジション
	Vec2 m_pos;
	Vec2 m_drawOffset;

	// プレイヤーポインタ
	Player* m_pPlayer;
};

