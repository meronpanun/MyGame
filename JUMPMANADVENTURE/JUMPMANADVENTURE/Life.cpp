#include "Life.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// グラフィックのサイズ
	constexpr int kGraphWidth = 17;
	constexpr int kGraphHeight = 17;

	// 表示座標
	constexpr int kBasePosX = 100;
	constexpr int kIntervalX = 80;
	constexpr int kPosY = 50;

	// サイズ(拡大率)
	constexpr double kScale = 3.0;
}

Life::Life():
	m_handle(-1),
	m_animFrameCount(0),
	m_index(0)
{
}

Life::~Life()
{
}

void Life::Init()
{
}

void Life::End()
{
}

void Life::Update()
{
}

void Life::Draw()
{
	// indexから表示位置を決定する
	int posX = kBasePosX + m_index * kIntervalX;

	DrawRectRotaGraph(posX, kPosY, // 中心座標を指定する
		0, 0, kGraphWidth, kGraphHeight,  // グラフィックの切り出し位置 
		kScale, 0.0,     // 拡大率、回転
		m_handle, true);
}

