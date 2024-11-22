#pragma once
#include <memory>
#include "Rect.h"

class BgStage1;
/// <summary>
/// テストプレイヤークラス
/// </summary>
class TestPlayer
{
public:
	TestPlayer();
	virtual ~TestPlayer();

	void Init();
	void Update();
	void Draw();

	// プレイヤーの位置情報を取得
	float GetX() const { return m_posX; }
	float GetY() const { return m_posY; }
	
	// 円の当たり判定
	float GetRadius();

	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// 現在のプレイヤーの矩形情報を取得
	Rect getRect();

private:
	// プレイヤーハンドル
	int m_playerHandle01;
	int m_playerHandle02;

	// プレイヤーの足元中央を基準とした座標
	float m_posX;
	float m_posY;

};

