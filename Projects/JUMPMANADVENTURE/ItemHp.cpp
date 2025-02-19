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
	constexpr int kRadius = 28;

	// グラフィックのサイズ
	constexpr int kGraphWidth = 17;
	constexpr int kGraphHeight = 17;

	// サイズ(拡大率)
	constexpr double kScale = 2.0;
	constexpr double kScaleAnimRange = 0.5; // 拡大縮小の範囲
	constexpr int kAnimCycle = 60; // アニメーションの周期

	// エフェクトの描画サイズ
	constexpr int kEffectGraphWidth = 64; 
	constexpr int kEffectGraphHeight = 62;

	// エフェクトのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	// アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 6;
	// アニメーションの1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

ItemHp::ItemHp():
	m_pCamera(nullptr),
	m_pos(0.0f, 0.0f),
	m_handle(-1),
	m_effectHandle(-1),
	m_animFrameCount(0),
	m_isExist(true),
	m_effectAnimFrameCount(0),
	m_isEffectPlaying(false)
{
	// グラフィックの読み込み
	m_handle = LoadGraph("data/image/heart.png");
	assert(m_handle != -1);

	// エフェクトの読み込み
	m_effectHandle = LoadGraph("data/image/itemHpEffect.png");
	assert(m_effectHandle != -1);
}

ItemHp::~ItemHp()
{
	// グラフィックの開放
	DeleteGraph(m_handle);

	// エフェクトの開放
	DeleteGraph(m_effectHandle);
}

void ItemHp::Init(Camera* camera)
{
	m_pCamera = camera;
}

void ItemHp::Update()
{
	// アニメーションフレームカウントを更新
	m_animFrameCount++;

	// エフェクトのアニメーションが再生中の場合、フレームカウントを更新
	if (m_isEffectPlaying)
	{
		m_effectAnimFrameCount++;
		if (m_effectAnimFrameCount >= kAnimFrameCycle)
		{
			m_isEffectPlaying = false; // アニメーションが終了したら再生フラグをオフにする
		}
	}
}

void ItemHp::Draw()
{
	// アイテムが存在せず、エフェクトも再生中でない場合は描画しない
	if (!m_isExist && !m_isEffectPlaying)
	{
		return;
	}

	// 拡大縮小のアニメーション計算
	double scaleAnim = kScale + kScaleAnimRange * std::sin(2 * M_PI * m_animFrameCount / kAnimCycle);

	if (m_isExist)
	{
		DrawRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y),
			scaleAnim, 0.0f, m_handle, true);
	}

	// エフェクトのアニメーションを描画
	if (m_isEffectPlaying)
	{
		int frameIndex = m_effectAnimFrameCount / kAnimFrameNum;
		// エフェクトの描画位置
		int effectX = static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x - kEffectGraphWidth); // 中心に描画するために幅の半分を引く
		int effectY = static_cast<int>(m_pos.y - kEffectGraphHeight); // 上端に描画するために高さを引く
		DrawRectExtendGraph(effectX, effectY, effectX + 2 * kEffectGraphWidth, effectY + 2 * kEffectGraphHeight,
			kUseFrame[frameIndex] * kEffectGraphWidth, 0, kEffectGraphWidth, kEffectGraphHeight, m_effectHandle, true);
	}

#ifdef _DEBUG
	// 当たり判定のデバッグ表示
	DrawCircle(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y), kRadius, 0xff0000, false);
#endif // _DEBUG
}

/// <summary>
/// アイテムの位置を設定
/// </summary>
/// <param name="x">X座標</param>
/// <param name="y">Y座標</param>
void ItemHp::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

/// <summary>
/// アイテムが消える処理
/// </summary>
void ItemHp::ItemLost()
{
	// アイテムが取得された場合は存在フラグをfalseにする
	m_isExist = false; 

	// エフェクトのアニメーションを開始
	m_isEffectPlaying = true;
	m_effectAnimFrameCount = 0;
}

/// <summary>
/// アイテムの半径を取得
/// </summary>
/// <returns>半径</returns>
float ItemHp::GetRadius()
{
	return kRadius;
}

/// <summary>
/// アイテムとプレイヤーが当たったかどうか
/// </summary>
/// <param name="pPlayer">プレイヤーのポインタ</param>
/// <returns>当たったかどうか</returns>
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

/// <summary>
///  アイテムが存在するかどうかを判定
/// </summary>
/// <returns>存在フラグ</returns>
bool ItemHp::IsExist() const
{
	return m_isExist;
}
