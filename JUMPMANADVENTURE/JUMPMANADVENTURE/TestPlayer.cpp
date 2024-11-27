#include "TestPlayer.h"
#include "DxLib.h"
#include "BgStage1.h"
#include "Rect.h"
#include "Pad.h"
#include "Game.h"
#include <memory>

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

    // 重力
    constexpr float kGravity = 0.5f;
    // ジャンプ力
    constexpr float kJumpAcc = -10.0f;

    constexpr int kUseFrame[] = { 2,3 };

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    constexpr int kAnimFrameCycle = _countof(kUseFrame) * kSingleAnimFrame;

    constexpr int kUseJumpFrame[] = { 0 };

    
}

TestPlayer::TestPlayer() :
    m_isJump(false),
    m_isRight(false),
    m_isLeft(false),
    m_moveX(0.0f),
    m_moveY(0.0f),
    m_posX(120.0f),
    m_posY(690.0f),
    m_dir(kNutral),
    m_animationFrame(0),
    m_animFrame(0),
    m_animCount(0),
    m_isAnimJump(false),
    m_isCommand(false),
    m_isAnimTurn(false)
{
    m_playerHandle01 = LoadGraph("date/image/Mario.png");
    m_playerHandle02 = LoadGraph("date/image/Jump.png");
}

TestPlayer::~TestPlayer()
{
    DeleteGraph(m_playerHandle01);
    DeleteGraph(m_playerHandle02);
}

void TestPlayer::init()
{
}

void TestPlayer::Update()
{
    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    bool isMove = false;
    
    Pad::Update();

    m_dir = kNutral;

    m_moveX = 0.0f;

    // 左右移動
    if (!m_isCommand)
    {
        if (pad & PAD_INPUT_LEFT)
        {
            m_moveX -= kSpeed;
            m_isLeft = true;
            m_isAnimTurn = true;
            m_dir = kWalk;
        }
        else
        {
            m_isLeft = false;
        }

        if (pad & PAD_INPUT_RIGHT)
        {
            m_moveX += kSpeed;
            m_isRight = true;
            m_isAnimTurn = false;
            m_dir = kWalk;
        }
        else
        {
            m_isRight = false;
        }

        // ダッシュ処理
        if (pad & PAD_INPUT_3 && m_isRight)
        {
            m_moveX += kAccel;
            m_dir = kWalk;
            m_isAnimTurn = false;
        }
        if (pad & PAD_INPUT_3 && m_isLeft)
        {
            m_moveX -= kAccel;
            m_dir = kWalk;
            m_isAnimTurn = true;
        }
    }

    // アニメーション処理
}

void TestPlayer::Draw()
{
}

float TestPlayer::GetRadius()
{
    return 0.0f;
}

float TestPlayer::GetLeft() const
{
    return 0.0f;
}

float TestPlayer::GetTop() const
{
    return 0.0f;
}

float TestPlayer::GetRigth() const
{
    return 0.0f;
}

float TestPlayer::GetBottom() const
{
    return 0.0f;
}

TestRect TestPlayer::getRect()
{
    return TestRect();
}
