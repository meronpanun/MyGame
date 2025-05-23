#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "BgStage.h"
#include "Camera.h"
#include "SceneGameClear.h"

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{	
	// 旗の描画サイズ
	constexpr int kGraphWidth = 64;
	constexpr int kGraphHeight = 24;
	// ポールの描画サイズ
	constexpr int kPoleGraphWidth = 24;
	constexpr int kPoleGraphHeight = 103;

	// ゴールのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 6;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// ゴールの表示座標
	constexpr int kFlagPosX = 10000;
	constexpr int kFlagPosY = 300;
	constexpr int kPolePosX = 10034;
	constexpr int kPolePosY = 450;

	// ポールの当たり判定位置
	constexpr float kPoleColPosX = 6.0f;
	constexpr float kPoleColPosY = 220.0f;
	// ポールの当たり判定サイズ
	constexpr float kPoleColSizeX = 15.0f;
	constexpr float kPoleColSizeY = 600.0f;

	// 拡大率
	constexpr double kScale = 4.0f; 

	// 旗が落ちる速度
	constexpr float kFlagFallSpeed = 2.0f;

	// ゴール座標
	constexpr float kGoalPosX = 10000.0f;
	constexpr float kGoalPosY = 528.0f;
}

Goal::Goal():
	m_pCamera(nullptr),
	m_pos(kGoalPosX, kGoalPosY),
	m_animFrame(0),
	m_handle(0),
	m_index(0),
	m_poleCollisionOffset(-kPoleColPosX, -kPoleColPosY),
	m_poleCollisionSize(kPoleColSizeX, kPoleColSizeY),
	m_flagPosY(kFlagPosY),
	m_isFlagFalling(false),
	m_flagFallHeight(600),
	m_collisionTimer(0),
	m_isPlayerCollided(false),
	m_poleHandle(0),
	m_score(0), 
	m_timer(0), 
	m_transitionTimer(0) 
{
}

Goal::~Goal()
{
}

void Goal::Init(Camera* camera)
{
	m_pCamera = camera;
}

void Goal::Update()
{
	// アニメーションの進行
	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle)
	{
		m_animFrame = 0;
	}

	// 旗が落ちる処理
	if (m_isFlagFalling)
	{
		m_flagPosY += static_cast<int>(kFlagFallSpeed);
		if (m_flagPosY >= kFlagPosY + m_flagFallHeight)
		{
			m_flagPosY = kFlagPosY + m_flagFallHeight;
			m_isFlagFalling = false; // 旗が指定の高さまで落ちたら停止
		}
	}

	// プレイヤーが当たった後にタイマーを進める
	if (m_isPlayerCollided)
	{
		m_collisionTimer++;
	}
}

void Goal::Draw()
{
	// グラフィックの切り出し位置(X座標)を計算で求める
	int animNo = m_animFrame / kAnimFrameNum;

	// 旗の描画
	DrawRectRotaGraph(static_cast<int>(kFlagPosX + m_pCamera->m_drawOffset.x), static_cast<int>(m_flagPosY),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		kScale, 0.0,
		m_handle, true);


	// ポールの描画
	DrawRectRotaGraph(static_cast<int>(kPolePosX + m_pCamera->m_drawOffset.x), static_cast<int>(kPolePosY),
		0, 0, kPoleGraphWidth, kPoleGraphHeight,
		kScale, 0.0,
		m_poleHandle, true);

#ifdef DISP_COLLISON
	// 当たり判定のデバッグ表示
	DrawBox(kPolePosX + m_pCamera->m_drawOffset.x + m_poleCollisionOffset.x, kPolePosY + m_poleCollisionOffset.y,
		kPolePosX + m_pCamera->m_drawOffset.x + m_poleCollisionOffset.x + m_poleCollisionSize.x,
		kPolePosY + m_poleCollisionOffset.y + m_poleCollisionSize.y,
		0xff0000, false);
#endif // DISP_COLLISION
}

/// <summary>
/// プレイヤーとの当たり判定フラグを取得
/// </summary>
/// <param name="pPlayer">プレイヤーのポインタ</param>
/// <returns>プレイヤーとの当たり判定フラグ</returns>
bool Goal::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	// プレイヤーとポールの当たり判定
	Rect poleRect;
	poleRect.SetTopLeftSize(Vec2(kPolePosX + m_poleCollisionOffset.x, kPolePosY + m_poleCollisionOffset.y),
		Vec2(m_poleCollisionSize.x, m_poleCollisionSize.y));

	Rect playerRect = pPlayer->GetRect();

	if (poleRect.IsCollision(playerRect))
	{
		m_isFlagFalling = true;	   // 旗が落ちるフラグを設定
		m_isPlayerCollided = true; // プレイヤーが当たったフラグを設定
		return true;
	}

	return false;
}

/// <summary>
/// ポールの当たり判定のオフセットを設定
/// </summary>
/// <param name="offsetX">X座標</param>
/// <param name="offsetY">Y座標</param>
void Goal::SetPoleCollisionOffset(float offsetX, float offsetY)
{
	m_poleCollisionOffset.SetPos(offsetX, offsetY);
}

/// <summary>
/// ポールの当たり判定サイズ
/// </summary>
/// <param name="width">幅</param>
/// <param name="height">高さ</param>
void Goal::SetPoleCollisionSize(float width, float height)
{
	m_poleCollisionSize.SetPos(width, height);
}

/// <summary>
/// 旗の落ちる高さを設定
/// </summary>
/// <param name="height">高さ</param>
void Goal::SetFlagFallHeight(int height)
{
	m_flagFallHeight = height;
}

/// <summary>
/// 旗が指定の高さまで落ちたかどうかを判定
/// </summary>
/// <returns>旗が指定の高さまで落ちたかどうか</returns>
bool Goal::IsFlagFalling() const
{
	return m_isFlagFalling;
}
