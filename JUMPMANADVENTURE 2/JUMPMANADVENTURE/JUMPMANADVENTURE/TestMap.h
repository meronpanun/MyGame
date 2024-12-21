#pragma once
#include "Game.h"
#include "Vec2.h"
#include "Camera.h"

class Player;

struct MapChip
{
	Vec2 pos;
	float w, h;
	int chipKind;
};

class TestMap
{
public:
	TestMap();
	~TestMap();

	void Init();	// 初期化
	void End();	// 終了
	void Update(Player* player);	// 更新
	void Draw(Camera* camera);	// 描画

private:
	// グラフィックハンドル
	int m_handle;
	// グラフィックに含まれるチップ数
	int m_graphChipNumX;
	int m_graphChipNumY;

	// マップチップの1つ分のサイズ
	const static int kChipWidth = 16;
	const static int kChipHeight = 16;

	// マップに敷き詰めるチップの数
	const static int kChipNumX = Game::kScreenWidth / kChipWidth;
	const static int kChipNumY = 54;
};

