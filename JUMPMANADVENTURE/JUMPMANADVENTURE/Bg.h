//#pragma once
//#include "Vec2.h"
//#include "Rect.h"
//#include "Game.h"
//
//class Player;
///// <summary>
///// 背景クラス
///// </summary>
//class Bg
//{
//public:
//	Bg();
//	virtual ~Bg();
//
//	virtual void Init() = 0;
//	virtual void Update() = 0;
//	virtual void Draw() = 0;
//
//	// プレイヤーの位置からスクロール用を決定する
////	virtual int GetScrollX() = 0;
//
//	// 指定した矩形と当たっているか判定する
//	virtual bool IsCollision(Rect rect, Rect& ChipRect) = 0;
//
//	// プレイヤーのポインタを設定
//	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
//
//protected:
//	// プレイヤーのポインタ
//	Player* m_pPlayer;
//
//	// グラフィックに含まれるマップチップの数
//	int m_graphChipNumX;
//	int m_graphChipNumY;
//
//	// マップチップのグラフィック
//	int m_mapHandle;
//
//	// 画像サイズ
//	struct Size
//	{
//		int width;
//		int height;
//	};
//
//
//};
//
