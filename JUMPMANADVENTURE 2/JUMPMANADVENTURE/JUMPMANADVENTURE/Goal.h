#pragma once
#include "Vec2.h"
#include <memory>

class Player;
class BgStage1;
class Goal
{
public:
	Goal();
	virtual ~Goal();

	void Init();
	void Update();
	void Draw();

	// マップのポインタを設定する
	void SetMap(std::shared_ptr<BgStage1> pStage1) { m_pStage1 = pStage1; }

	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }

	// ゴールの位置情報を取得
	Vec2 GetPos() const { return m_pos; }

private:
	// ゴールの座標
	Vec2 m_pos;

	std::shared_ptr<BgStage1> m_pStage1;
	std::shared_ptr<Player> m_pPlayer;
		
	// グラフィックハンドル
	int m_handle;

	int m_animFrame;
};

