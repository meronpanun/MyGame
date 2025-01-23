#pragma once
#include "Rect.h"
#include "Vec2.h"


class Camera;
class Player;
class BgStage1
{
public:
	BgStage1();
	virtual ~BgStage1();

	void Init(Camera* camera);
	void Update(Player* player);
	void Draw();

	//指定した矩形と当たっているか判定
	bool IsCollision(Rect rect, Rect& ChipRect);

private:
	Vec2 m_pos;

	Camera* m_pCamera;

	// マップのグラフィックハンドル
    int m_handle001;
    int m_handle002;
    int m_handle003;
    int m_handle004;
    int m_handle005;
};

