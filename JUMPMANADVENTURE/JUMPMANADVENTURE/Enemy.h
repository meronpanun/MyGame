#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Camera;
class Player;
class BgStage1;
class Enemy
{
public:
	Enemy();
	 ~Enemy();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// 敵の上下左右情報取得
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// 現在の敵の矩形情報
	Rect GetRect();

	// 敵の移動方向を反転
	void ReverseDirection();

	// 敵の生死フラグ
	void SetAlive(bool isAlive);

	// 敵の位置を設定
	void SetPos(float x, float y);

	// 敵が生きているかどうかのフラグ
	bool IsAlive() const;

	// プレイヤーが範囲内にいるかチェックするメソッドを追加
	bool IsPlayerInRange(const Vec2& playerPos, float range); 

	void Activate(); // 敵をアクティブにする
	bool IsActive() const; // 敵がアクティブかどうかをチェックする

private:
	Camera* m_pCamera;

	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;

	// 敵の位置
	Vec2 m_pos;
	// 敵の加速度
	Vec2 m_move;

	bool m_isTurnFlag;

	// エネミーが生きているかどうかのフラグ
	bool m_isAlive;

	// 向いている方向
	bool m_isAnimRight;
	bool m_isAnimLeft;
	bool m_isFacingRight; // 敵が右を向いているかどうか

	// 敵がアクティブかどうかを管理するフラグ
	bool m_isActive; 

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;
	// 敵のグラフィックハンドル
	int m_handle;
};
