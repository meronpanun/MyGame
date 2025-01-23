#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include <assert.h>

namespace
{
	// 敵のサイズ	
	constexpr int kWidth = 30;
	constexpr int kHeight = 30;

	// 敵の描画サイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 28;

	// 速度
	constexpr float kSpeed = 2.5f;

	// 重力
	constexpr float kGravaity = 0.5f;

	// キャラクターのアニメーション
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;


	// 円の当たり判定の半径
	constexpr int kRadius = 10;
}

Enemy::Enemy():
	m_pos(550.0f,640.0f),
	m_move(0.0f, 0.0f),
	m_animFrame(0),
	m_animCount(0),
	m_isturnFlag(false),
	m_isAnimLeft(false),
	m_isAnimRight(false),
	m_dir(kRunRight)
{
	m_handle = LoadGraph("data/image/RockRun.png");
	assert(m_handle != -1);
}

Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	bool isMove = false;

	// 毎フレーム下方向に加速する
	m_move.y += kGravaity;

	if (m_isturnFlag = false)
	{
		m_move.x = kSpeed;
		m_isAnimRight = true;
		isMove = true;
		m_dir = kRunRight;
	}
	if (m_isturnFlag = true)
	{
		m_move.y = -kSpeed;
		m_isAnimLeft = true;
		isMove = true;
		m_dir = kRunLeft;
	}

	if (isMove)
	{
		// アニメーションの進行
		m_animFrame++;
		if (m_animFrame >= kAnimFrameCycle)
		{
			m_animFrame = 0;
		}
	}

	// 横の当たり判定
	m_pos.x += m_move.x;
	Rect chipRect;
	if (m_pBgStage1->IsCollision(GetRect(), chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.m_left - kGraphWidth * static_cast<float>(0.5f) - 1;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.m_right + kGraphWidth * static_cast<float>(0.5f) + 1;
		}
	}

	// 縦の当たり判定
//	m_pos.y += m_move.y;
	if (m_pBgStage1->IsCollision(GetRect(), chipRect))
	{
		if (m_move.y > 0.0f) // プレイヤーが下方向に移動している
		{
			// 地面に立っている何もしない
			m_pos.y = chipRect.m_top - 1;
		}
		else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
		{
			m_pos.y = chipRect.m_bottom + kGraphHeight + 1; // めり込まない位置に補正
			m_move.y *= -1.0f; // 上方向への加速を下方向に変換
		}
	}
}

void Enemy::Draw()
{
	// グラフィックの切り出し位置(X座標)を計算で求める
	int animFrame = m_animFrame / kAnimFrameNum;

	//int srcX = kRunFrame[animFrame] * kGraphWidth;
	//int srcY = kGraphHeight * m_dir;

	//bool isFlip = false;
	//if (kSpeed > 0.0f)
	//{
	//	isFlip = true;
	//}

	DrawRectRotaGraph(m_pos.x, m_pos.y,
		animFrame * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		1.0, 0.0, m_handle, true);

#ifdef _DEBUG
	// 当たり判定のデバッグ表示
	DrawBox(GetLeft(), GetTop(),
		GetRigth(), GetBottom(),
		0xff0000, false);
#endif // _DEBUG
}




float Enemy::GetLeft() 
{
	return m_pos.x - kGraphWidth * static_cast<float>(0.5f);
}

float Enemy::GetTop() 
{
	return m_pos.y - kGraphHeight;
}

float Enemy::GetRigth() 
{
	return m_pos.x + kGraphWidth * static_cast<float>(0.5f);
}

float Enemy::GetBottom() 
{
	return m_pos.y;
}

Rect Enemy::GetRect()
{
	// 敵の矩形当たり判定情報
	Rect rect;
	rect.m_top = GetTop();
	rect.m_bottom = GetBottom();
	rect.m_left = GetLeft();
	rect.m_right = GetRigth();
	return rect;
}

bool Enemy::IsGetHitPlayer(std::shared_ptr<Player> pPlayer)
{
	// プレイヤーと敵の半径の合計
	float Rlength = kRadius + pPlayer->GetRadius();
	// X成分の距離
	float delX = pPlayer->GetPos().x - m_pos.x;
	// Y成分の距離
	float delY = pPlayer->GetPos().y - m_pos.y;

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{
		return true;
	}

	return false;
}
