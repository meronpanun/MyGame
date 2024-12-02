#pragma once
#include <memory>
#include "Rect.h"

class Player;
class Map
{
public:
	Map();
	virtual ~Map();

	//メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle001 = handle; }
	//	void SetHandle02(int handle) { m_handle002 = handle; }

		//プレイヤーのポインタを設定する
//	void SetPlayer(std::shared_ptr<TestPlayer>pTestPlayer) { m_pPlayer = pTestPlayer; }

	void Update();
	void Draw();

	//プレイヤーの位置からスクロール量を取得する
//	int GetScrollX();

	//指定した矩形と当たっているか判定
	//参照を使用してぶつかったマップチップの矩形情報を取得する
	bool IsCollision(Rect rect, Rect& testChipRect);

private:
	// スクロール量を決定するためにプレイヤーの位置情報が必要
	std::shared_ptr<Player>m_pPlayer;


	int m_handle001;
	//	int m_handle002;
};

