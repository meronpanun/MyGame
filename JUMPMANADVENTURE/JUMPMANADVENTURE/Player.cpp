#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // プレイヤーグラフィックの幅と高さ
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // アニメーションのコマ数
    constexpr int kWalkAnimNo[] = { 2,3 };
    constexpr int kWalkAnimNum = _countof(kWalkAnimNo);

    // アニメーション1コマのフレーム数
    constexpr int kWalkAnimFrame = 10;

    // プレイヤーの移動速度
    constexpr float kSpeed = 2.0f;

    // 地面の高さ
    constexpr float kFieldHeight = 720.0f - 78.0f;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプ力
    constexpr float kGravity = 0.4f; // 重力
}

Player::Player() :
    m_handle(-1),
    m_walkFrameCount(0),
    m_isRun(false),
    m_pos(150.0f, kFieldHeight),
    m_isDirLeft(false),
    m_isJump(false),
    m_jumpSpeed(0.0f)
{
    m_handle = LoadGraph("date/image/Mario.png");
    assert(m_handle != -1);
}

Player::~Player()
{
    // グラフィックの開放
    DeleteGraph(m_handle);
}

void Player::Init()
{
}

void Player::Update()
{

    // 左右にキャラクターを動かす
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // 左キーを押しているときの処理
        m_pos.x -= kSpeed;  // 左方向に位置変更
        m_isDirLeft = true; // 左向き
        m_isRun = true;     // 走っている
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // 右キーを押しているときの処理
        m_pos.x += kSpeed;   // 右方向に位置変更
        m_isDirLeft = false; // 右向き
        m_isRun = true; // 走っている
    }

    // 1ボタンを押したときにジャンプする
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        if (!m_isJump)
        {
            m_isJump = true;
            m_jumpSpeed = kJumpPower;
        }
    }

    // アニメーションの更新
    if (m_isRun)
    {
        // 移動中のみ歩くアニメーションを行う
        m_walkFrameCount++;
        if (m_walkFrameCount >= kWalkAnimNum * kWalkAnimFrame)
        {
            m_walkFrameCount = 0;
        }
    }

    if (m_isJump)
    {
        m_pos.y += m_jumpSpeed;

        m_jumpSpeed += kGravity;

        if (m_jumpSpeed > 0.0f)
        {
            if (m_pos.y >= kFieldHeight)
            {
                // ジャンプ終了する
                m_isJump = false;
                m_jumpSpeed = 0.0f;
                // 地面にめり込まないように地面の高さに位置を補正
                m_pos.y >= kFieldHeight;
            }
        }
    }
}

void Player::Draw()
{
    int animIndex = m_walkFrameCount / kWalkAnimFrame;
    int animNo = kWalkAnimNo[animIndex];

    DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
        animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
         m_handle,true);

#ifdef DISP_COLLISON
    DrawBox(GetLeft(), GetTop(),
        GetRight(), GetBottom(),
        GetColor(0, 0, 255), false);
#endif // DISP_COLLISON
}

float Player::GetLeft() const
{
    return (m_pos.x - kGraphWidth / 2);
}

float Player::GetRight() const
{
    return (m_pos.x + kGraphWidth / 2);
}

float Player::GetTop() const
{
    return (m_pos.y - kGraphHeight);
}

float Player::GetBottom() const
{
    return m_pos.y;
}



