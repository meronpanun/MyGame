#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Camera;
class BgStage1;
class SceneMain;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	 ~Player();

	void Init(Camera* camera);
	void Update();
	void Draw();



	// プレイヤーの位置情報を取得
	Vec2 GetPos() const { return m_pos; }
	// プレイヤーの当たり判定を取得
//	Rect GetColRect() const { return m_colRect; }
	
    // 円の当たり判定
	float GetRadius();

	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// マップチップとの当たり判定
	void CheckHitBgStage1(Rect chipRect);

	// 現在のプレイヤーの矩形情報を取得
	Rect GetRect();


private:
	// ジャンプ処理
	void UpdateJump();

private:
	Camera* m_pCamera;

	// プレイヤーの位置
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;
	// 当たり判定用の矩形
//	Rect m_colRect;

//	BgStage1* m_pBgStage1;
	std::shared_ptr<BgStage1> m_pBgStage1;

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
	// 歩いているかどうかフラグ
	bool m_isWalk; // true:歩いている false:待機
	// キャラがどちらを向いているかのフラグ
	bool m_isAnimTurn;
};

