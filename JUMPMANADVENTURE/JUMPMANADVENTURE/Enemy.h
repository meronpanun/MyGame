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
	virtual ~Enemy();

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

	// プレイヤーとの当たり判定
//	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	void SetAlive(bool isAlive);

	bool IsAlive() const;

	enum Dir
	{
		kRunRight,
		kRunLeft
	};

private:
	Camera* m_pCamera;

	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;

	Vec2 m_pos;
	// 敵の加速度
	Vec2 m_move;

	bool m_isturnFlag;

	// エネミーが生きているかどうかのフラグ
	bool m_isAlive;

	// 向いている方向
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;
	// 敵のグラフィックハンドル
	int m_handle;
};

