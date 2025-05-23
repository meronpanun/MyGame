#pragma once
#include "Rect.h"
#include "Vec2.h"
#include <vector>

class Camera;
class Player;

/// <summary>
/// ステージクラス
/// </summary>
class BgStage
{
public:
	BgStage();
	virtual ~BgStage();

	void Init(Camera* camera);
	void Update();
	void Draw();

	//指定した矩形と当たっているか判定
	bool IsCollision(Rect rect, Rect& ChipRect);
	// 地面の高さを取得
	float GetGroundHeight(float x) const; 

private:
	Vec2 m_pos;

	Camera* m_pCamera;

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

