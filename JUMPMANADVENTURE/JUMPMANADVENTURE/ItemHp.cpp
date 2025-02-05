#include "ItemHp.h"
#include "Player.h"
#include "BgStage.h"
#include "DxLib.h"
#include "Camera.h"
#include <cmath>
#include <cassert>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


namespace
{
	// 半径
	constexpr int kRadius = 16;

	// グラフィックのサイズ
	constexpr int kGraphWidth = 17;
	constexpr int kGraphHeight = 17;

	// サイズ(拡大率)
	constexpr double kScale = 2.0;
	constexpr double kScaleAnimRange = 0.5; // 拡大縮小の範囲
	constexpr int kAnimCycle = 60; // アニメーションの周期
}

ItemHp::ItemHp():
	m_pos(0.0f, 0.0f),
	m_handle(-1),
	m_animFrameCount(0),
	m_isExist(true)
{
	// グラフィックの読み込み
	m_handle = LoadGraph("data/image/heart.png");
	assert(m_handle != -1);
}

ItemHp::~ItemHp()
{
	// グラフィックの開放
	DeleteGraph(m_handle);
}

void ItemHp::Init(Camera* camera)
{
	m_pCamera = camera;
}

void ItemHp::Update()
{
	// アニメーションフレームカウントを更新
	m_animFrameCount++;
}

void ItemHp::Draw()
{
	if (!m_isExist) // アイテムが存在しない場合は描画しない
	{
		return;
	}

	// 拡大縮小のアニメーション計算
	double scaleAnim = kScale + kScaleAnimRange * std::sin(2 * M_PI * m_animFrameCount / kAnimCycle);

	DrawRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y),
		scaleAnim, 0.0f, m_handle, true);

#ifdef _DEBUG
	// 当たり判定のデバッグ表示
	DrawCircle(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y), kRadius, 0xff0000, false);
#endif // _DEBUG
}

void ItemHp::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void ItemHp::ItemLost()
{
	// アイテムが取得された場合は存在フラグをfalseにする
	m_isExist = false; 
}

float ItemHp::GetRadius()
{
	return kRadius;
}

bool ItemHp::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	float Rlength = kRadius + pPlayer->GetRadius();
	float delX = pPlayer->GetPos().x - m_pos.x;
	float delY = pPlayer->GetPos().y - m_pos.y;

	float del = sqrt(delX * delX + delY * delY);
	if (del <= Rlength)
	{
		return true;
	}

	return false;
}

bool ItemHp::IsExist() const
{
	return m_isExist;
}
