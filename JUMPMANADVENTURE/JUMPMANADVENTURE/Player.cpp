#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"
#include <memory>
#include "Game.h"

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // キャラクターグラフィックの幅と高さ
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // アニメーションのコマ数
    constexpr int kJumpAnimNum = 1;
    constexpr int kRunAnimNum = 2;
    
    // キャラクターの移動速度
    constexpr float kSpeed = 2.0f;

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 10;

    // 歩きアニメーションで使用する順番
   // constexpr int kWalkAnimNo[] = { 1,2, };
   // constexpr int kWalkAnimNum = _countof(kWalkAnimNo);
   // constexpr int kWalkAnimFrame = 10;

	// 地面の高さ
	constexpr float kFieldHeight = 720.0f - 28.0f;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプの初速
    constexpr float kGravity = 0.4f;    // 重力

}

Player::Player() :
    m_runHandle(-1),
    m_jumpHandle(-1),
    m_animFrame(0),
    //m_dir(kDirDown),
	m_pos(720.0f, kFieldHeight),
    m_walkFrameCount(0),
    m_isRun(false),
    m_isDirLeft(false),
    m_isJump(false),
    m_jumpSpeed(0.0f)
{
    m_runHandle = LoadGraph("date/image/Mario.png");
    assert(m_runHandle != -1);

    m_jumpHandle = LoadGraph("date/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    // グラフィックの開放
    DeleteGraph(m_runHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init()
{

}

void Player::Update()
{

}





void Player::Draw()
{
    int animNo = m_animFrame / kSingleAnimFrame;

    int useHandle = m_runHandle;
    if (m_isRun)
    {
        useHandle = m_jumpHandle;
    }
//	int animIndex = m_walkFrameCount / kWalkAnimFrame;
//	int animNo = kWalkAnimNo[animIndex];

; DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
    animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
    useHandle,true, m_isDirLeft);

#ifdef DISP_COLLISON
    DrawBox(GetLeft(), GetTop(),
        GetRigth(), GetBottom(),
        GetColor(0, 0, 255), false);
#endif // DISP_COLLISON
}

float Player::GetLeft() const
{
	return (m_pos.x - kGraphWidth / 2);
}

float Player::GetTop() const
{
	return (m_pos.y - kGraphHeight);
}

float Player::GetRigth() const
{
	return (m_pos.x + kGraphWidth / 2);
}

float Player::GetBottom() const
{
	return  m_pos.y;
}

void Player::UpdateNormal()
{
    // アニメーションの更新
    m_animFrame++;

    int totalFrame = kJumpAnimNum * kSingleAnimFrame;
    if (m_isRun)
    {
        totalFrame = kJumpAnimNum * kSingleAnimFrame;
    }
    // アニメーションの合計フレーム数を超えたら最初に戻す
    if (m_animFrame >= totalFrame)
    {
        m_animFrame = 0;
    }

    // 左右にキャラクターを動かす
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // 左キーを押している時の処理
        m_pos.x -= kSpeed;   // 左方向に位置を変更
        m_isDirLeft = true;  // キャラクターが左を向いている
        m_isRun = true;
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // 右キーを押している時の処理
        m_pos.x += kSpeed;   // 右方向に位置を変更
        m_isDirLeft = false; // キャラクターが左を向いている
        m_isRun = true;
    }

    // ジャンプ処理
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        if (!m_isJump)
        {
            m_isJump = true;
            m_jumpSpeed = kJumpPower;
        }
    }
    if (m_isJump)
    {
        m_pos.y += m_jumpSpeed;

        m_jumpSpeed += kGravity; // 毎フレーム下方向に加速する

        if (m_jumpSpeed > 0.0f)
        {
            if (m_pos.y >= kFieldHeight)
            {
                // ジャンプ終了する
                m_isJump = false;
                m_jumpSpeed = 0.0f;

                // 地面にめり込むことがあるので地面の高さに位置を補正する
                m_pos.y >= kFieldHeight;
            }
        }
    }
}




