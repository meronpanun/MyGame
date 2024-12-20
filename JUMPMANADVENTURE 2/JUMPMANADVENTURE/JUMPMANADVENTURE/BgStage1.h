#pragma once
#include "Bg.h"
#include "Rect.h"
#include "Player.h"

class Camera;
class Player;
class BgStage1
{
public:
	BgStage1();
	virtual ~BgStage1();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// プレイヤーの位置からスクロール量を決定する
//	int GetScrollX();

	//指定した矩形と当たっているか判定
	bool IsCollision(Rect rect, Rect& ChipRect);

private:
	Camera* m_pCamera;

	Player m_pPlayer;

	// マップのグラフィックハンドル
    int m_handle001;
};

