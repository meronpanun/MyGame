#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>
#include <memory>

class Player;
class BgStage1;
/// <summary>
/// 敵の基底クラス 
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

 	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// 敵の位置情報を取得
	Vec2 GetPos() const { return m_pos; }

	// 円の当たり判定
	float GetRadius();

	// 敵の上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// プレイヤーとの当たり判定
	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	// 現在の敵の矩形情報
	Rect GetRect();

	//指定した矩形と当たっているか判定
	bool IsCollision(Rect rect, Rect& enemyRect);

protected:
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;

	// 表示位置
	Vec2 m_pos;

	// グラフィックのハンドル
	int m_handle;
};

