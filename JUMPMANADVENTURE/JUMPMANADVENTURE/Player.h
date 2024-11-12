#pragma once
#include "Vec2.h"
#include <memory>

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	// 円の当たり判定
	float GetRadius();

	// プレイヤーの上下左右情報取得
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();



private:
	Vec2 m_pos;

	enum Dir // 向いている方向	
	{
		kNutral, // 通常状態
		kWalk,   // 歩き
		kNo,
		kFall,
		kDash,
	};

	// グラフィックハンドル
	int m_runHandle;
	int m_jumpHandle;

	int m_jumpCount = 0;

	// true : 空中にいる false : 地面に立っている
	bool m_isJump;

	// 右に移動しているかどうかのフラグ
	bool m_isRight;

	// 左に移動しているかどうかのフラグ
	bool m_isLeft;

	// 操作しているかどうかのフラグ
	bool m_isCommand;

	// プレイヤーの足元中央を基準とした座標
	float m_posX;
	float m_posY;

	// プレイヤーの加速度
	float m_moveX;
	float m_moveY;

	// 向いている方向
	Dir m_dir;

	// プレイヤーがどちらを向いているかのフラグ
	bool m_isAnimTrun;
	// プレイヤーがジャンプ描画されてるかどうかのフラグ
	bool m_isAnimJump;

	// アニメーション関連
	int m_animFrame; // アニメーションのフレーム数を数える
	int m_animCount; // アニメーションのカウント

	
};

