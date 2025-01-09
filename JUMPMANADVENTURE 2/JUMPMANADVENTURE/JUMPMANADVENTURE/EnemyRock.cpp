#include "EnemyRock.h"
#include "DxLib.h"
#include "BgStage1.h"

namespace
{
	// 敵のサイズ	
	constexpr int kWidth = 30;
	constexpr int kHeight = 30;

	// 敵の描画サイズ
	constexpr int kDrawWidth = 32;
	constexpr int kDrawHeight = 28;

	// 速度
	constexpr float kSpeed = 2.5f;

	// 重力
	constexpr float kGravaity = 0.5f;

	// キャラクターのアニメーション
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;
}

EnemyRock::EnemyRock():
	m_move(0.0f,0.0f),
	m_animFrame(0),
	m_animCount(0)
{
}

EnemyRock::~EnemyRock()
{
}

void EnemyRock::Update()
{
}

void EnemyRock::Draw()
{
}
