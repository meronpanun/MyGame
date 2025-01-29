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

	// 拡大率
	constexpr float kScale = 2.0f;

	// 速度
	constexpr float kSpeed = 1.5f;
//	constexpr float kSpeed = 0.0f;

	// 重力
	constexpr float kGravaity = 0.5f;

	// キャラクターのアニメーション
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	constexpr int kDeadFrame[] = { 0,1,2,3,4 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 4;
	constexpr int kDeadAnimFrameNum = 10;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;
	constexpr int kDeadAnimFrameCycle = _countof(kDeadFrame) * kDeadAnimFrameNum;

	// マップチップとの当たり判定の調整
	constexpr int kColChipAdjustmentY = 28;

	// 円の当たり判定の半径
	constexpr int kRadius = 10;
}

Enemy::Enemy():
	m_pos(0.0f,0.0f),
	m_move(-kSpeed, 0.0f),
	m_animFrame(0),
	m_animCount(0),
	m_isTurnFlag(false),
	m_isAnimLeft(true),
	m_isAnimRight(false),
	m_isAlive(true),
	m_isFacingRight(false),
	m_isActive(false),
	m_isDead(false),
	m_deadAnimFrame(0)
{
	// グラフィックの読み込み
	m_handle = LoadGraph("data/image/RockRun.png");
	assert(m_handle != -1);
	m_deadHandle = LoadGraph("data/image/RockDead.png");
	assert(m_deadHandle != -1);
}

Enemy::~Enemy()
{
	// グラフィックの開放
	DeleteGraph(m_handle);
	DeleteGraph(m_deadHandle);
}

void Enemy::Init(Camera* camera)
{
	m_pCamera = camera;
}

void Enemy::Update()
{
	// 敵が消えている場合は処理を行わない
	if (!m_isAlive && !m_isDead) return;
	
	// 死亡アニメーション中の場合
	if (m_isDead)
	{
		// 死亡アニメーションの更新
		m_deadAnimFrame++;
		if (m_deadAnimFrame >= kDeadAnimFrameCycle)
		{
			m_isDead = false; // 死亡アニメーションが終了したらフラグをリセット
		}
		return;
	}

	bool isMove = false;

	// 毎フレーム下方向に加速する
	m_move.y += kGravaity;

	if (m_move.x < 0.0f)
	{
		m_isAnimLeft = true;
		m_isAnimRight = false;
		m_isFacingRight = false;
	}
	else
	{
		m_isAnimLeft = false;
		m_isAnimRight = true;
		m_isFacingRight = true;
	}

	isMove = true;

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
			m_pos.x = chipRect.m_left - kGraphWidth * kScale * 0.5f - 1;
			ReverseDirection(); // 壁に当たったら方向転換
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.m_right + kGraphWidth * kScale * 0.5f + 1;
			ReverseDirection(); // 壁に当たったら方向転換
		}
	}

	// 縦の当たり判定
	m_pos.y += m_move.y;
	if (m_pBgStage1->IsCollision(GetRect(), chipRect))
	{
		if (m_move.y > 0.0f) // エネミーが下方向に移動している
		{
			m_pos.y = chipRect.m_top - 1;
			m_move.y = 0.0f; // 地面に立っているのでy方向の速度をリセット
		}
		else if (m_move.y < 0.0f) // エネミーが上方向に移動している
		{
			m_pos.y = chipRect.m_bottom + kGraphHeight * kScale + 1; // めり込まない位置に補正
			m_move.y = 0.0f; // 上方向への加速をリセット
		}
	}


}

void Enemy::Draw()
{
	// 敵が消えている場合は処理を行わない
	if (!m_isAlive && !m_isDead) return;

	// 死亡アニメーション中の場合
	if (m_isDead)
	{
		// 死亡アニメーションのフレームを計算
		int deadAnimFrame = m_deadAnimFrame / kDeadAnimFrameNum;
		DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kColChipAdjustmentY),
			deadAnimFrame * kGraphWidth, 0, kGraphWidth, kGraphHeight,
			kScale, 0.0, m_deadHandle, true, m_isFacingRight);
		return;
	}

	// グラフィックの切り出し位置(X座標)を計算で求める
	int animFrame = m_animFrame / kAnimFrameNum;

	DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x),static_cast<int>(m_pos.y - kColChipAdjustmentY),
		animFrame * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		kScale, 0.0, m_handle, true, m_isFacingRight);

#ifdef _DEBUG
	// 当たり判定のデバッグ表示
	//DrawBox(GetLeft() + m_pCamera->m_drawOffset.x,
	//	GetTop(),
	//	GetRigth() + m_pCamera->m_drawOffset.x,
	//	GetBottom(),
	//	0xff0000, false);
#endif // _DEBUG
}


float Enemy::GetLeft() 
{
	return m_pos.x - kGraphWidth * kScale * 0.5f;
}

float Enemy::GetTop() 
{
	return m_pos.y - kGraphHeight * kScale;
}

float Enemy::GetRigth() 
{
	return m_pos.x + kGraphWidth * kScale * 0.5f;
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

void Enemy::SetAlive(bool isAlive)
{
	m_isAlive = isAlive;
	if (!isAlive)
	{
		m_isDead = true;     // 死亡アニメーションを開始
		m_deadAnimFrame = 0; // 死亡アニメーションのフレームをリセット
	}
}

void Enemy::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void Enemy::ReverseDirection()
{
	// 移動方向を反転
	m_move.x = -m_move.x;
	// グラフィックの向きを反転
	m_isFacingRight = !m_isFacingRight;
}

bool Enemy::IsAlive() const
{
	return m_isAlive;
}

bool Enemy::IsPlayerInRange(const Vec2& playerPos, float range)
{
	Vec2 enemyPos = m_pos;
	return (playerPos - enemyPos).Length() <= range;
}

void Enemy::Activate()
{
	m_isActive = true;
}

bool Enemy::IsActive() const
{
	return m_isActive;
}