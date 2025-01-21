#pragma once
#include "Vec2.h"
#include <memory>

class Camera;
class Player;
class BgStage1;
class Goal
{
public:
	Goal();
	virtual ~Goal();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// マップのポインタを設定する
//	void SetMap(std::shared_ptr<BgStage1> pStage1) { m_pStage1 = pStage1; }

//	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	// ゴールの位置情報を取得
	Vec2 GetPos() const { return m_pos; }

	// ゴールの半径を取得
	float GetRadius() const;

	// プレイヤーとの当たり判定フラグ
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

private:
	// ゴールの座標
	Vec2 m_pos;

	Camera* m_pCamera;

	std::shared_ptr<BgStage1> m_pStage1;
	std::shared_ptr<Player> m_pPlayer;
		
	// グラフィックハンドル
	int m_handle;
	// アニメーション
	int m_animFrame;

	int m_index;
};

