#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"
#include <memory>
#include "Game.h"


namespace
{
    // キャラクターグラフィックの幅と高さ
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // アニメーションのコマ数
    constexpr int kJumpAnimNum[] = { 0 };
    constexpr int kRunAnimNum[] = { 2,3 };
    constexpr int kAnimFrameCycle = _countof(kRunAnimNum) * kSingleAnimFrame;

    // キャラクターの移動速度
    constexpr float kSpeed = 2.0f;

	// 地面の高さ
	constexpr float kFieldHeight = 720.0f - 80.0f;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプの初速
    constexpr float kGravity = 0.4f;    // 重力

}

Player::Player() :
    m_runHandle(-1),
    m_jumpHandle(-1),
    m_animFrame(0),
	m_pos(120.0f, kFieldHeight),
    m_walkFrameCount(0),
    m_isRun(false),
    m_isDirLeft(false),
    m_isJump(false),
    m_isAnimJump(false),
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
    // 移動中のみ歩行アニメーションを行う
    if (m_isRun)
    {
        // アニメーションの更新
        m_animFrame++;
        if (m_animFrame >= kAnimFrameCycle)
        {
            m_animFrame = 0;
        }
    }

    // 左右にキャラクターを動かす
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // 左キーを押している時の処理
        m_pos.x -= kSpeed;   // 左方向に位置を変更
        m_isDirLeft = true;  // キャラクターが左を向いている
        m_isRun = true;      // 走っている
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // 右キーを押している時の処理
        m_pos.x += kSpeed;   // 右方向に位置を変更
        m_isDirLeft = false; // キャラクターが左を向いている
        m_isRun = true;      // 走っている
    }

    // ジャンプ処理
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        if (!m_isJump)
        {
            m_isJump = true;
            m_isAnimJump = true;
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
                m_isAnimJump = false;
                m_jumpSpeed = 0.0f;

                // 地面にめり込むことがあるので地面の高さに位置を補正する
                m_pos.y >= kFieldHeight;
            }
        }
    }
}

void Player::Draw()
{
    // プレイヤーのアニメーションフレーム
    int animFrame = m_animFrame / kSingleAnimFrame;
    // プレイヤーの切り取り画像
    int animNo = kRunAnimNum[animFrame];
    // プレイヤージャンプの切り取り座標
    int animJumpNo = kJumpAnimNum[animFrame];

    // ジャンプした場合
    if (m_isAnimJump)
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            animJumpNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_jumpHandle, true, m_isDirLeft);
    }
    else
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_runHandle, true, m_isDirLeft);
    }
}

float Player::GetLeft() const
{
	return (m_pos.x - kGraphWidth * 0.5f);
}

float Player::GetTop() const
{
	return (m_pos.y - kGraphHeight);
}

float Player::GetRigth() const
{
	return (m_pos.x + kGraphWidth * 0.5f);
}

float Player::GetBottom() const
{
	return  m_pos.y;
}






