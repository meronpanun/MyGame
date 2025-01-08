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

	void Init(Camera* pCamera);
	void Update();
	void Draw();

	// 現在のHPを取得
	int GetHp() const { return m_hp; }
	// 現在の残機数を取得
	int GetLife() const { return m_life; }

	// プレイヤーがダメージを受けた時の処理
	void OnDamage();

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

	void AddMoveY(float DisY);
	void OnCollideY();

	// 現在のプレイヤーの矩形情報を取得
	Rect GetRect();


private:
	// ジャンプ処理
	void UpdateJump();
	// 各状態毎のUpdate処理
	void UpdateNormal();  // ゲーム中のUpdate
	void UpdateDead();    // 死亡後のUpdate

private:
	Camera* m_pCamera;
	SceneMain* m_pMain;

	// プレイヤーの位置
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;
	// 当たり判定用の矩形
//	Rect m_colRect;

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
	float m_jumpSpeed;

	// 右に移動しているかどうかのフラグ
	bool m_isRight; 
	// 左に移動しているかどうかのフラグ
	bool m_isLeft;
	// 歩いているかどうかフラグ
	bool m_isWalk; // true:歩いている false:待機
	// キャラがどちらを向いているかのフラグ
	bool m_isAnimTurn;

	int m_invincibleCount;
	// HP
	int m_hp;
	// 残機
	int m_life;

	// 点滅
	int m_blinkFrameCount;
	// 死亡演出
	int m_deadFrameCount;
};

