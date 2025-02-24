#pragma once
#include "Vec2.h"

/// <summary>
/// 矩形のデータ管理
/// </summary>
class Rect
{
public:
	Rect();
	Rect(Vec2 posTL, Vec2 size);
	virtual ~Rect();

public:
	float m_left;   // 左上のX座標
	float m_top;    // 左上のY座標
	float m_right;  // 右下のX座標
	float m_bottom; // 右下のY座標

	float GetWidth() const { return m_right - m_left; }
	float GetHeight() const { return m_bottom - m_top; }

	// 各座標取得
	Vec2 GetCenter();

	// 当たり(重なり)判定
	bool IsCollision(const Rect& rect);

	// 左上座標とサイズからRestデータを設定
	void SetTopLeftSize(Vec2 posTL, Vec2 size);
};


