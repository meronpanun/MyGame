#include "Life.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// グラフィックのサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// アニメーションのコマ数
	constexpr int kLoopAnimNum = 17;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 4;

	// 表示座標
	constexpr int kBasePosX = 100;
	constexpr int kIntervalX = 60;

	constexpr int kPosY = 50;

	// サイズ(拡大率)
	constexpr double kScale = 2.0;
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
	if (m_animFrameCount >= kLoopAnimNum * kSingleAnimFrame)
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
