#pragma once
#include "Rect.h"
#include "TestRect.h"
#include "Vec2.h"

class Bg;
class Player;
class TestPlayer;
class TestMap;
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
	// TestPlayer* m_pTestPlayer;
	// プレイヤーの現在位置
	Vec2 m_playerPos;

	// 画像
	int m_gameScreenHandle; // ゲーム画面
};

