#include "Player.h"
#include "DxLib.h"
#include "Map.h"
#include "Pad.h"
#include "Game.h"
#include <memory>
#include <cassert>

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // キャラクターサイズ
    constexpr int kWidth = 20;
    constexpr int kHeight = 20;

    // キャラクターの描画サイズ
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // 当たり判定半径
    constexpr int kRadius = 9;

    // 速度
    constexpr float kSpeed = 3.0f;
    // 加速
    constexpr float kAccel = 2.0f;

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // 重力
    constexpr float kGravity = 0.5f;
    // ジャンプ力
    constexpr float kJumpAcc = -10.0f;

    constexpr int kUseJumpFrame[] = { 0 };
    constexpr int kUseFrame[] = { 2,3 };
    constexpr int kAnimFrameCycle = _countof(kUseFrame) * kSingleAnimFrame;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプの初速
    // ジャンプの長押し時間
    constexpr int kPressShortJumpFrame = 10;	// 10フレーム
    constexpr int kPressMediumJumpFrame = 30;	// 30フレーム
    // ジャンプの高さ調整
    constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
    constexpr float kInJumpHeight = 0.8f;		// 中ジャンプ
    constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ
}

Player::Player() :
    m_isJump(false),
    m_isRight(false),
    m_isLeft(false),
    m_isWalk(false),
    m_isGround(false),
    m_move(0.0f, 0.0f),
    m_pos(120.0f, 415.0f),
    m_animFrame(0),
    m_jumpFrame(0),
    m_jumpCount(0),
    m_animCount(0),
    m_isAnimJump(false),
    m_isAnimTurn(false)
{
    m_walkHandle = LoadGraph("date/image/Mario.png");
    assert(m_walkHandle != -1);
    m_jumpHandle = LoadGraph("date/image/Jump.png");
}

Player::~Player()
{
    DeleteGraph(m_walkHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init()
{
    // ジャンプフラグ
    m_isGround = false;
}

void Player::Update()
{

    // 移動中のみ歩行アニメーションを行う
    if (m_isWalk)
    {
        // if (m_animation == Anim::kWalk)
        {
            // アニメーションの更新
            m_animFrame++;
            if (m_animFrame >= kAnimFrameCycle)
            {
                m_animFrame = 0;
            }
        }
    }
    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    bool isMove = false;

    Pad::Update();

    m_move.x = 0.0f;

    // 左右移動
    m_isWalk = false;
    if (pad & PAD_INPUT_LEFT)
    {
        m_move.x -= kSpeed;
        m_isLeft = true;
        m_isAnimTurn = true;
        m_isWalk = true;
    }
    else
    {
        m_isLeft = false;
    }

    if (pad & PAD_INPUT_RIGHT)
    {
        m_move.x += kSpeed;
        m_isRight = true;
        m_isAnimTurn = false;
        m_isWalk = true;
    }
    else
    {
        m_isRight = false;
    }

    // ダッシュ処理
    if (pad & PAD_INPUT_3 && m_isRight)
    {
        m_move.x += kAccel;
        m_isAnimTurn = false;
    }
    if (pad & PAD_INPUT_3 && m_isLeft)
    {
        m_move.x -= kAccel;
        m_isAnimTurn = true;
    }



    // ジャンプ処理
    if (m_isJump) // ジャンプ中
    {
        m_move.y += kGravity;

        Rect chipRect;
        CheckHitMap(chipRect);
    }
    else // 地面についている場合
    {
        if (pad & PAD_INPUT_1 && m_isJump == false)
        {
            m_isJump = true;
            m_jumpCount++;
        }
        else m_jumpCount = 0;

        if (m_jumpCount == 1 && m_isJump)
        {
            m_move.y = kJumpAcc;
            m_isAnimJump = false;
        }
        else m_isJump = false;

        m_pos.x += m_move.x;
        Rect chipRect;
        // 横
        if (m_pMap->IsCollision(getRect(), chipRect))
        {
            if (m_move.x > 0.0f)
            {
                m_pos.x = chipRect.m_left - kWidth * 0.5 - 1;
            }
            else if (m_move.x < 0.0f)
            {
                m_pos.x = chipRect.m_right + kWidth * 0.5 + 1;
            }
        }

        m_pos.y += m_move.y;
        // 縦
        if (m_pMap->IsCollision(getRect(), chipRect))
        {
            // 上下どちらか当たったかをデバック表示
            if (m_move.y > 0.0f) // プレイヤーが上下方向に移動している
            {
                // 地面に立っている何もしない
                m_pos.y = chipRect.m_top - 1;
                m_isJump = false;
                m_isAnimJump = false;
            }
            else if (m_move.y < 0.0f)
            {
                m_pos.y = chipRect.m_bottom + kHeight + 1;
                m_move.y *= -1.0f;
            }
        }
        else
        {
            m_isJump = true;
        }
    }
    printfDx("m_pos:(%d,%d)\n",
        (int)m_pos.x,
        (int)m_pos.y);
}

void Player::Draw()
{
    // プレイヤーのアニメーションフレーム
    int animFrame = m_animFrame / kSingleAnimFrame;
    // プレイヤーの切り取り画像
    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
    int walkSrcX = kUseFrame[animFrame];
    int walkSrcY = kGraphHeight;


    // ジャンプした場合
    if (m_isAnimJump)
    {

        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_jumpHandle, true, m_isAnimTurn);
    }
    else
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_walkHandle, true, m_isAnimTurn);

    }
#ifdef DISP_COLLISON
    // 当たり判定のデバッグ表示
    DrawBox(GetLeft(), GetTop(),
        GetRigth(), GetBottom(),
        GetColor(0, 0, 255), false);
#endif // DISP_COLLISION
}

float Player::GetLeft() const
{
    return m_pos.x - kWidth * 0.5;
}

float Player::GetTop() const
{
    return m_pos.y - kHeight;
}

float Player::GetRigth() const
{
    return m_pos.x + kWidth * 0.5;
}

float Player::GetBottom() const
{
    return m_pos.y;
}

void Player::CheckHitMap(Rect chipRect)
{
    // 横の当たり判定
    m_pos.x += m_move.x;
    if (m_pMap->IsCollision(getRect(), chipRect))
    {
        if (m_move.x > 0.0f)
        {
            m_pos.x = chipRect.m_left - kWidth * 0.5 - 1;
        }
        else if (m_move.x < 0.0f)
        {
            m_pos.x = chipRect.m_right + kWidth * 0.5 + 1;
        }
    }

    // 縦の当たり判定
    m_pos.y += m_move.y;
    if (m_pMap->IsCollision(getRect(), chipRect))
    {
        if (m_move.y > 0.0f)
        {
            m_pos.y -= m_move.y;
            m_move.y = 0.0f;
            m_isJump = false;
            m_isAnimJump = false;
        }
        else if (m_move.y < 0.0f)
        {
            m_pos.y = chipRect.m_bottom + kHeight + 1;
            m_move.y *= 0.0f;
        }
    }
}

Rect Player::getRect()
{
    // プレイヤーの矩形当たり判定情報
    Rect rect;
    rect.m_top = GetTop();
    rect.m_bottom = GetBottom();
    rect.m_left = GetLeft();
    rect.m_right = GetRigth();
    return rect;
}

void Player::UpdateJump()
{
    m_jumpFrame++;
    // ジャンプ処理
    if (Pad::IsRelase(PAD_INPUT_1))
    {
        //　ジャンプの高さを決める
        float jumpHeight;

        if (m_jumpFrame < kPressShortJumpFrame)
        {
            jumpHeight = kLittleJumpHeight;
        }
        else if (m_jumpFrame < kPressMediumJumpFrame)
        {
            jumpHeight = kInJumpHeight;
        }
        else
        {
            jumpHeight = kLittleJumpHeight;
        }
        m_move.y *= jumpHeight;
    }
}
