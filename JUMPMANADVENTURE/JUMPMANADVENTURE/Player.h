#pragma once
#include "Vec2.h"

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


	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// プレイヤーの位置情報を取得する
	Vec2 GetPos() const { return m_pos; }


private:
	void UpdateJump();

private:
	// グラフィックハンドル
	int m_runHandle;
	int m_jumpHandle;

	// 歩き関連
	int m_animFrame;   // フレーム数を数える
	int m_walkFrameCount;

	// true:走っている　false:待機
	bool m_isRun;
	// true:左向き　false:右向き
	bool m_isDirLeft;
	// 地面と接しているかどうか
	bool m_isGround; // true : 接している 

	// プレイヤーの位置
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;
	
	//Dir m_dir;

	// ジャンプ処理
	bool m_isJump;	   // true : ジャンプ中 false : ジャンプしていない
	bool m_isAnimJump; // true :  描画する  false : 描画しない
	float m_jumpSpeed;
	int m_jumpFrame;
};

