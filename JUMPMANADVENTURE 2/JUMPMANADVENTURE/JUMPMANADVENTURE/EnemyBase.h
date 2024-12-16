#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>
#include <memory>

class Player;
class SceneMain;

/// <summary>
/// 敵の基底クラス 
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	void Init();
	void Update();
	void Draw();

	// 円の当たり判定
	float GetRadius();

	// 敵の上下左右情報取得
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// プレイヤーとの当たり判定
	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	// 現在の敵機の矩形情報
	Rect GetRect;

	//指定した矩形と当たっているか判定
	bool IsCollision(Rect rect, Rect& enemyRect);

protected:
	// グラフィックのハンドル
	int m_handle;

	// 表示位置
	Vec2 m_pos;
};

