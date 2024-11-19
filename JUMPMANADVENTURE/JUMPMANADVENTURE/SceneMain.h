#pragma once
#include "Rect.h"
#include "Vec2.h"

class Bg;
class Player;

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Player* m_pPlayer;
	// プレイヤーの現在位置
	Vec2 m_playerPos;

	// 画像
	int m_gameScreenhandle; // ゲーム画面
};

