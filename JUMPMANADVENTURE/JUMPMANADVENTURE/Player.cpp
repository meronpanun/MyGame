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
    constexpr int kIdleAnimNum = 1;
    constexpr int kRunAnimNum = 3;

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 6;

    // プレイヤーの移動速度
    constexpr float kSpeed = 2.0f;

    // 地面の高さ
    constexpr float kFieldHeight = 720.0f - 78.0f;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプ力
    constexpr float kGravity = 0.4f; // 重力

    // ダメージをくらった後の無敵時間(点滅時間)
    constexpr int kDamegeBlinkFrame = 30;

    // プレイヤーの初期残機
    constexpr int kMaxHp = 3;

    // 死亡演出
    constexpr int kDeadStopFrame = 30;      // 死んだ瞬間停止する時間
    constexpr float kDeadJumpSpeed = -4.0f; // 死んだあと飛び上がる初速 
}

Player::Player() :
    m_handleIdle(-1),
    m_handleRun(-1),
    m_animFrame(0),
    m_isRun(false),
    m_pos(150.0f, kFieldHeight),
    m_isDirLeft(false),
    m_isJump(false),
    m_jumpSpeed(0.0f),
    m_blinkFrameCount(0),
    m_hp(kMaxHp),
    m_deadFrameCount(0)
{
    m_handleIdle = LoadGraph("date/image/Idle.png");
    assert(m_handleIdle != -1);

    m_handleRun = LoadGraph("date/image/Run.png");
    assert(m_handleRun != -1);
}

Player::~Player()
{
    // グラフィックの開放
    DeleteGraph(m_handleIdle);
    DeleteGraph(m_handleRun);
}

void Player::Init()
{
}

void Player::Update()
{
    // 生きているときと死んでいるときで処理を切り分ける
    if (m_hp > 0)
    {
        UpdateNormal();
    }
    else
    {
        UpdateDead();
    }
}

void Player::Draw()
{
    // 点滅処理
    if ((m_blinkFrameCount / 2) % 2)
    {
        return;
    }

    int animNo = m_animFrame / kSingleAnimFrame;

    int useHandle = m_handleIdle;
    if (m_isRun)
    {
        useHandle = m_handleRun;
    }


    bool isDead = false;
    if (m_hp <= 0)
    {
        isDead = true;
    }

    DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
        animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
        useHandle, true, m_isDirLeft, isDead);

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

void Player::OnDamage()
{
    // 既にダメージを受けている(無敵時間)は再度ダメージを受けない
    if (m_blinkFrameCount > 0)
    {
        return;
    }

    // 無敵時間
    m_blinkFrameCount = kDamegeBlinkFrame; // 点滅する時間を設定

    // ダメージを受ける
    m_hp--;
    // HPが0以下になったら死亡演出を開始
    if (m_hp <= 0)
    {
        InitDead();
    }
}

void Player::InitDead()
{
    m_jumpSpeed = kDeadJumpSpeed;
    m_deadFrameCount = 0;
    m_blinkFrameCount = 0;
}

void Player::UpdateNormal()
{
    // 無敵時間の更新
    m_blinkFrameCount--;
    if (m_blinkFrameCount < 0)
    {
        m_blinkFrameCount = 0;
    }

    // アニメーションの更新
    m_animFrame++;

   // int totalFrame = kRunAnimNum * kSingleAnimFrame;
    int totalFrame = kIdleAnimNum * kSingleAnimFrame;
    if (m_isRun)
    {
        int totalFrame = kIdleAnimNum * kSingleAnimFrame;
    }
 

    // アニメーションの合計フレーム数を超えたら最初に戻す
    if (m_animFrame >= totalFrame)
    {
        m_animFrame = 0;
    }

    //  前回のアニメーションの状態を覚えておく
    bool isLastRun = m_isRun;

    // 左右にキャラクターを動かす
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // 左キーを押しているときの処理
        m_pos.x -= kSpeed;  // 左方向に位置変更
        m_isDirLeft = true; // キャラクターが左を向いている
        m_isRun = true;
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // 右キーを押しているときの処理
        m_pos.x += kSpeed;   // 右方向に位置変更
        m_isDirLeft = false; // キャラクターが左を向いている
        m_isRun = true;
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

#ifdef _DEBUG
    // 即死でバック機能　5ボタン(Lボタン)
    if (Pad::IsTrigger(PAD_INPUT_5))
    {
        m_hp = 0;
        InitDead();
    }
#endif // _DEBUG

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
        // 処理を行った結果、アニメーションが変わっていた場合の処理
        if (m_isRun != isLastRun)
        {
            m_animFrame = 0;
        }
    }

}

void Player::UpdateDead()
{
    // 死亡後一瞬止まる
    m_deadFrameCount++;
    if (m_deadFrameCount < kDeadStopFrame)
    {
        return;
    }

    // 画面外に落ちていく演出
    m_pos.y += m_jumpSpeed;
    m_jumpSpeed += kGravity;
}
