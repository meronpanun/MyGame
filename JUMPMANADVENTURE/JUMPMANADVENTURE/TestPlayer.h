#pragma once
#include <memory>
#include "TestRect.h"

class BgStage1;
class TestPlayer
{
public:
	TestPlayer();
	virtual ~TestPlayer();

	void SetMap(std::shared_ptr<BgStage1> pBgStage1) { m_pBgStage1 = pBgStage1; }

	void init();
	void Update();
	void Draw();

	float GetX() const { return m_posX; }
	float GetY() const { return m_posY; }

	float GetRadius();

	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	TestRect getRect();

private:
	enum Dir
	{
		kNutral,
		kWalk,
		kNo,
		kFall,
		kDash
	};
	std::shared_ptr<BgStage1> m_pBgStage1;

	int m_playerHandle01;
	int m_playerHandle02;

	int m_jumpCount = 0;

	bool m_isJump;

	bool m_isRight;

	bool m_isLeft;

	bool m_isCommand;

	float m_posX;
	float m_posY;

	float m_moveX;
	float m_moveY;

	Dir m_dir;

	bool m_isAnimTurn;

	bool m_isAnimJump;

	int m_animationFrame;

	int m_animFrame;
	int m_animCount;
};

