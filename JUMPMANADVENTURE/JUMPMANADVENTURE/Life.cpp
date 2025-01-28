#include "Life.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// グラフィックのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	//constexpr int kGraphWidth = 16;
	//constexpr int kGraphHeight = 16;

	// HPのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
//	constexpr int kUseFrame[] = { 0,1,2 };
	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 4;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kSingleAnimFrame;

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
	// アニメーションの進行
	m_animFrameCount++;
	if (m_animFrameCount >= kAnimFrameCycle)
	{
		m_animFrameCount = 0;
	}
}

void Life::Draw()
{
	// グラフィックの切り出し位置(X座標)を計算で求める
	int animNo = m_animFrameCount / kSingleAnimFrame;

	// indexから表示位置を決定する
	int posX = kBasePosX + m_index * kIntervalX;

	DrawRectRotaGraph(posX, kPosY, // 中心座標を指定する
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,  // グラフィックの切り出し位置 
		kScale, 0.0,     // 拡大率、回転
		m_handle, true);
}
