#pragma once
#include "Vec2.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBotton() const;

	int GetHp() const { return m_hp; }


private:
	// プレイヤーのHP
	int m_hp;
};

