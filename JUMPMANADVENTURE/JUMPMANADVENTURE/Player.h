#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Bg;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	 ~Player();

	void Init(Bg* bg, SceneMain* pMain, Vec2 initPos);
	void Update();
	void Draw();


	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// マップチップとの当たり判定
	void CheckHitMap(Rect chipRect);

public:
	void UpdateJump();
	// プレイヤーの位置情報を取得する
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定の取得
	Rect GetColRect() const { return m_colRect; }

private:
	// 背景
	Bg* m_pBg;
	SceneMain* m_pMain;

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
	// 当たり判定用の矩形
	Rect m_colRect;

	//Dir m_dir;

	// ジャンプ処理
	bool m_isJump;	   // true : ジャンプ中 false : ジャンプしていない
	bool m_isAnimJump; // true :  描画する  false : 描画しない
	float m_jumpSpeed;
	int m_jumpFrame;
};

