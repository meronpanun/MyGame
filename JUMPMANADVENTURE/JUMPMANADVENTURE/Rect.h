#pragma once
#include "Vec2.h"

/// <summary>
/// 矩形管理クラス
/// </summary>
class Rect
{
public:
	Rect();
	float GetWidth() const { return right - left; }
	float GetHeigth() const { return bottom - top; }

	// 各座標取得
	Vec2 GetCenter();

	// 当たり判定
	bool isCol(const Rect& rect);
	/// <summary>
	/// 左上座標とサイズからRectデータを設定
	/// </summary>
	/// <param name="posTL">左上座標</param>
	/// <param name="size">サイズ</param>
	void set_TL_Size(Vec2 posTL, Vec2 size);
public:
	float top;
	float bottom;
	float left;
	float right;



};

