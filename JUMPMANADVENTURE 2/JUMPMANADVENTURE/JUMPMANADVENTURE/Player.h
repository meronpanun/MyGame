#pragma once
#include <memory>
#include "Rect.h"
#include "Vec2.h"

class Map;
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

	// プレイヤーの位置情報を取得
//	Vec2 GetPos() const { return m_pos; }

	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// マップチップとの当たり判定
	void CheckHitMap(Rect chipRect);

	// 現在のプレイヤーの矩形情報を取得
	Rect getRect();


private:
	// ジャンプ処理
	void UpdateJump();

private:
	//  スクロール量を取得するためにMapクラス情報の取得
	std::shared_ptr<Map> m_pMap;

	// プレイヤーの位置
	Vec2 m_pos;

	// 移動量
	Vec2 m_move;

	// キャラクターのグラフィックハンドル
	int m_walkHandle;
	int m_jumpHandle;

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;

	// ジャンプ処理
	int m_jumpCount; 
	int m_jumpFrame;
	bool m_isJump;     // ジャンプしているかどうかフラグ
	bool m_isAnimJump; // プレイヤーがジャンプ描画しているかどうかのフラグ

	// 右に移動しているかどうかのフラグ
	bool m_isRight; 
	// 左に移動しているかどうかのフラグ
	bool m_isLeft;
	// 地面についているかどうかフラグ
	bool m_isGround;
	// 歩いているかどうかフラグ
	bool m_isWalk; // true:歩いている false:待機
	// キャラがどちらを向いているかのフラグ
	bool m_isAnimTurn;
};

