#include "Life.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
	constexpr double kScaleAnimRange = 0.5; // 拡大縮小の範囲
	constexpr int kAnimCycle = 60; // アニメーションの周期
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

void Life::Update()
{
	// アニメーションフレームカウントを更新
	m_animFrameCount++;
}

void Life::Draw()
{
	// indexから表示位置を決定する
	int posX = kBasePosX + m_index * kIntervalX;

	// 拡大縮小のアニメーション計算
    double scaleAnim = kScale + kScaleAnimRange * std::sin(2 * M_PI * m_animFrameCount / kAnimCycle);

	DrawRectRotaGraph(posX, kPosY, // 中心座標を指定する
		0, 0, kGraphWidth, kGraphHeight,  // グラフィックの切り出し位置 
		scaleAnim, 0.0f,     // 拡大率、回転
		m_handle, true);
}

