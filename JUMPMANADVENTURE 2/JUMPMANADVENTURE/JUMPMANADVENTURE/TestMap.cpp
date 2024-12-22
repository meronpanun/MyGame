#include "TestMap.h"
#include"Player.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	bool hitBottom = false;
	float liftX = 0;
}

TestMap::TestMap() :
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_handle(-1)
{
}

TestMap::~TestMap()
{
}

void TestMap::Init()
{
	// グラフィックの読み込み
	m_handle = LoadGraph("data/image/map.png");
	assert(m_handle != -1);
	// グラフィックに含まれるチップ数を数える
	int graphWidth = 0;
	int GraphHeight = 0;
	GetGraphSize(m_handle, &graphWidth, &GraphHeight);
	//マップチップの数
	m_graphChipNumX = graphWidth / kChipWidth;
	m_graphChipNumY = GraphHeight / kChipHeight;
	//配列のマップデータをマップチップに入れる。
	for (int wIndex = 0; wIndex < m_graphChipNumX; wIndex++)
	{
		for (int hIndex = 0; hIndex < m_graphChipNumY; hIndex++)
		{
			MapChip& temp = m_map.mapChips[wIndex][hIndex];
			temp.w = kChipWidth;//幅
			temp.h = kChipHeight;//高さ
			temp.chipKind = kChipSetData[kChipNumY][kChipNumX];//種類
			//mapChipのposを決める
			float tempX = wIndex * temp.w + temp.w * 0.5f;
			float tempY = hIndex * temp.h + temp.w * 0.5f;
			temp.pos.SetPos(tempX, tempY);
		}
	}
}

void TestMap::End()
{
	// グラフィックの解放
	DeleteGraph(m_handle);
}

void TestMap::Update(Player* player)
{
	for (int h = 0; h < kChipNumY; h++)
	{
		for (int w = 0; w < kChipNumX; w++)
		{
			int chipNo = kChipSetData[h][w];
			if (chipNo < 440 && chipNo >= 0)
			{
				if (player->GetLeft() >= w * kChipWidth && player->GetLeft() <= w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight - m_AllChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight - m_AllChipHeight)
				{
					// 下から当たった場合
					float chipBottom = h * kChipHeight + kChipHeight - m_AllChipHeight;
					player->AddMoveY(chipBottom - player->GetTop());// マップチップとプレイヤーの重なった分だけ下にずらす
					player->OnCollideY();// m_velocity.yを0にする
					if (h * kChipHeight + kChipHeight - m_AllChipHeight == player->GetTop() && player->FallFlag() == false)
					{
						hitBottom = true;
						// マップチップを壊す
						kChipSetData[h][w] = -1;
					}
				}

				// 上から当たった場合
				if (player->GetLeft() >= w * kChipWidth && player->GetLeft() <= w * kChipWidth + kChipWidth
					&& player->GetBottom() >= h * kChipHeight - m_AllChipHeight && player->GetBottom() <= h * kChipHeight + kChipHeight - m_AllChipHeight)
				{
					//printfDx("着地");
					float chipTop = h * kChipHeight - m_AllChipHeight;
					player->Landing(player->GetBottom() - chipTop);// マップチップとプレイヤーの重なった分だけ上にずらす
					hitBottom = false;
					player->OnCollideY();
				}

				// マップチップの左側から当たった場合
				// 1マスの隙間からマップチップの下から当たると左側から当たった時の処理に引っかかって
				// プレイヤーが左にずれてしまう　一通り終わってから調整する
				if (player->GetRight() >= w * kChipWidth && player->GetRight() < w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight - m_AllChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight - m_AllChipHeight
					&& hitBottom == false)
				{
					float chipLeft = w * kChipWidth;
					player->AddMoveLeft(player->GetRight() - chipLeft);// マップチップとプレイヤーの重なった分だけ左にずらす
					player->OnCollideX();// m_velocity.xを0にする
				}

				// マップチップの右側から当たった場合
				/*if (player->GetLeft() > w * kChipWidth && player->GetLeft() < w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight)
				{
					float chipRight = w * kChipWidth + kChipWidth;
					player->AddMoveRight(chipRight - player->GetLeft());
					player->OnCollideX();
				}*/
			}

			if (chipNo == 440 || chipNo == 441 || chipNo == 442)
			{
				// 上から当たった場合
				if (player->GetLeft() >= w * kChipWidth && player->GetLeft() <= w * kChipWidth + kChipWidth
					&& player->GetBottom() >= h * kChipHeight - m_AllChipHeight && player->GetBottom() <= h * kChipHeight + kChipHeight - m_AllChipHeight
					&& player->FallFlag() == true)
				{
					float chipTop = h * kChipHeight - m_AllChipHeight;
					if (player->PlayerAirPos() < chipTop)
					{
						player->Landing(player->GetBottom() - chipTop);
						player->OnCollideY();
					}
				}

				// マップチップの左側から当たった場合
				if (player->GetRight() == w * kChipWidth && player->GetRight() < w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight)
				{
					float chipLeft = w * kChipWidth;
					player->AddMoveLeft(player->GetRight() - chipLeft);
					player->OnCollideX();
				}
			}
		}
	}
}

void TestMap::Draw(Camera* camera)
{
}
