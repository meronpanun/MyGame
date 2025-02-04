#pragma once
#include "Rect.h"
#include "Vec2.h"
#include <vector>

class Camera;
class Player;
class BgStage1
{
public:
	BgStage1();
	virtual ~BgStage1();

	void Init(Camera* camera);
	void Update(Player* player);
	void Draw();

	//指定した矩形と当たっているか判定
	bool IsCollision(Rect rect, Rect& ChipRect);
	// 地面の高さを取得
	float GetGroundHeight(float x) const; 

	// プレイヤーとブロックの衝突をチェックしてブロックを消す
	void CheckAndRemoveBlocks(Player* player);

private:
	Vec2 m_pos;

	Camera* m_pCamera;

	// ブロックの状態を管理するメンバ変数
	std::vector<Rect> m_brickBlocks;
	std::vector<Rect> m_questionBlocks;

	// マップのグラフィックハンドル
    int m_handle001;
    int m_handle002;
    int m_handle003;
    int m_handle004;
    int m_handle005;
    int m_handle006;
    int m_handle007;
    int m_handle008;
};

