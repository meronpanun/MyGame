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

	void SetHandle(int handle) { m_handle = handle; }

	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;

private:
	// グラフィックハンドル
	int m_handle;

	// true : 走っている false : 待機
	bool m_isRun;

	// プレイヤーの位置
	Vec2 m_pos;
	// true : 左向き false: 右向き
	bool m_isDirLeft;

	// ジャンプ処理
	bool m_isJump;
	float m_jumpSpeed;

	int m_walkFrameCount;
};

