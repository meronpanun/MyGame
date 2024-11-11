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
	
	// プレイヤーと敵がぶつかった
	void OnDamage();

private:
	// 状態変化する時の処理
	void InitDead(); // 死亡演出の初期化

	void UpdateNormal();
	void UpdateDead();

private:
	// グラフィックハンドル
	int m_handleIdle;
	int m_handleRun;

	// フレーム数を数える
	int m_animFrame;
	// true : 走っている false : 待機
	bool m_isRun;

	// プレイヤーの位置
	Vec2 m_pos;
	// true : 左向き false: 右向き
	bool m_isDirLeft;

	// ジャンプ処理
	bool m_isJump;
	float m_jumpSpeed;

	// 点滅
	int m_blinkFrameCount;

	// プレイヤーのHP
	int m_hp;

	// 死亡演出
	int m_deadFrameCount;
};

