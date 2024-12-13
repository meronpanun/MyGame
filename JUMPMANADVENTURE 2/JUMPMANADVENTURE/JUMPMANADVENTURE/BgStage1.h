#pragma once
#include "Bg.h"
#include "Rect.h"

class Player;
class BgStage1 /* : public Bg*/
{
public:
	BgStage1();
	virtual ~BgStage1();

//	virtual void Init() override;
//	virtual void Update() override;
//	virtual void Draw(/*Camera* camera*/) override;

	void Init();
	void Update();
	void Draw();

	// プレイヤーの位置からスクロール量を決定する
//	virtual int GetScrollX() override;
//	int GetScrollX();

	//指定した矩形と当たっているか判定
//	virtual bool IsCollision(Rect rect, Rect& ChipRect) override;
	bool IsCollision(Rect rect, Rect& ChipRect);


	//メンバー変数にアクセスする
 //	void SetHandle(int handle) { m_handle001 = handle; }
 //	void SetHandle02(int handle) { m_handle002 = handle; }

	//プレイヤーのポインタを設定する
//	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
	Player* m_pPlayer;

	// マップのグラフィックハンドル
	  int m_handle001;
	//	int m_handle002;
};

