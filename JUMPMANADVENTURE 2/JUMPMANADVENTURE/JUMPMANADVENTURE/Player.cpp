#include "Player.h"
#include "DxLib.h"
#include "BgStage1.h"
#include "Pad.h"
#include "Game.h"
#include "Camera.h"
#include "SceneMain.h"
#include <cassert>

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // キャラクターサイズ
    constexpr int kWidth = 30;
    constexpr int kHeight = 30;

    // キャラクターの描画サイズ
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;
    
    // プレイヤーのリスポーン位置
    constexpr float kRestartPosX = 150.0f;
    constexpr float kRestartPosY = 610.0f;

    // 当たり判定の半径
    constexpr int kRadius = 9;

    // 底の上限 
    constexpr int kFallMaX = 920;

    // ステージの左右端座標
    constexpr int kStageLeftEnd = 40;
    constexpr int kStageRightEnd = 5100;

    // 速度
    constexpr float kSpeed = 3.0f;
    // 加速
    constexpr float kAccel = 4.0f;

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // 重力
    constexpr float kGravity = 0.5f;
    // ジャンプ力
    constexpr float kJumpAcc = -10.0f;

    // キャラクターのジャンプアニメーション
    constexpr int kJumpFrame[] = { 0 };
    // キャラクターの歩きアニメーション
    constexpr int kWalkFrame[] = { 2,3 };
    // アニメーションの1サイクルのフレーム数
    constexpr int kAnimFrameCycle = _countof(kWalkFrame) * kSingleAnimFrame;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプの初速
    // ジャンプの長押し時間
    constexpr int kPressShortJumpFrame = 10;	// 10フレーム
    constexpr int kPressMediumJumpFrame = 30;	// 30フレーム
    // ジャンプの高さ調整
    constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
    constexpr float kInJumpHeight = 0.8f;		// 中ジャンプ
    constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ

    // 無敵時間
    constexpr int kInvincible = 30;

    // 初期の残機数
    constexpr int kLife = 3;

    // プレイヤーの初期HP
    constexpr int kMaxHp = 3;

    // 死亡演出
    constexpr int kDeadStopFrame = 30;      // 死んだ瞬間止まる時間
    constexpr float kDeadJumpSpeed = -4.0f; // 死んだあと飛び上がる初速
}

Player::Player() :
    m_isJump(false),
    m_isRight(false),
    m_isLeft(false),
    m_isWalk(false),
    m_move(0.0f, 0.0f),
    m_pos(150.0f, 610.0f),
    m_animFrame(0),
    m_jumpFrame(0),
    m_jumpCount(0),
    m_jumpSpeed(0.0f),
    m_animCount(0),
    m_blinkFrameCount(0),
    m_hp(kMaxHp),
    m_deadFrameCount(0),
    m_isAnimJump(false),
    m_isAnimTurn(false)
{
    m_walkHandle = LoadGraph("data/image/Mario.png");
    assert(m_walkHandle != -1);
    m_jumpHandle = LoadGraph("data/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    DeleteGraph(m_walkHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init(Camera* pCamera)
{
    m_pCamera = pCamera;
    m_pCamera->m_pos.SetPos(m_pos.x, m_pos.y);
}

void Player::Update()
{
    // プレイヤーが穴に落下した場合
    if ((m_pos.y - kHeight) > kFallMaX)
    {
        m_pos.x = kRestartPosX;
        m_pos.y = kRestartPosY;

        m_pCamera->m_pos.SetPos(m_pos.x, m_pos.y);

        // hpを減らす
        m_hp--;
    }

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
    // プレイヤーのアニメーションフレーム
    int animFrame = m_animFrame / kSingleAnimFrame;
    // プレイヤーの切り取り画像
    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
    int walkSrcX = kWalkFrame[animFrame];
    int walkSrcY = kGraphHeight;

    // ジャンプした場合
    if (m_isAnimJump)
    {

        DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth + 32 + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight + 3),
            kGraphWidth, 0, kGraphWidth, kGraphHeight, 2.0f, 0,
            m_jumpHandle, true, m_isAnimTurn);
    }
    else
    {
        DrawRectRotaGraph(static_cast<int>( m_pos.x  - kGraphWidth + 32 + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight + 3),
            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight, 2.0f, 0,
            m_walkHandle, true, m_isAnimTurn);

    }
    
#ifdef DISP_COLLISON
    // 当たり判定のデバッグ表示
 /*   DrawBox(GetLeft(), GetTop(),
        GetRigth(), GetBottom(),
        GetColor(0, 0, 255), false);*/
#endif // DISP_COLLISION
}

void Player::OnDamage()
{
    // 既にダメージを受けている(無敵時間)間は
    // 再度ダメージを受けることはない
    if (m_invincibleCount > 0)
    {
        return;
    }
    // 無敵時間(点滅する時間)を設定する
    m_invincibleCount = kInvincible;
    // ダメージを受ける
    m_hp--;
    printfDx("Damage ");
}

float Player::GetRadius() const
{
    return kRadius;
}

float Player::GetLeft() const
{
    return m_pos.x - kWidth * static_cast<float>(0.5f);
}

float Player::GetTop() const
{
    return m_pos.y - kHeight;
}

float Player::GetRigth() const
{
    return m_pos.x + kWidth * static_cast<float>(0.5f);
}

float Player::GetBottom() const
{
    return m_pos.y;
}

void Player::CheckHitBgStage1(Rect chipRect)
{
    // 横の当たり判定
    m_pos.x += m_move.x;
    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
    {
        if (m_move.x > 0.0f) // プレイヤーが右方向に移動している
        {
            m_pos.x = chipRect.m_left - kWidth * static_cast<float>(0.5f) - 1; // 左側の補正
        }
        else if (m_move.x < 0.0f) // プレイヤーが左方向に移動している
        {
            m_pos.x = chipRect.m_right + kWidth * static_cast<float>(0.5f) + 1; // 右側の補正
        }
    }

    // 縦の当たり判定
    m_pos.y += m_move.y;
    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
    {
        if (m_move.y > 0.0f) // プレイヤーが下方向に移動している
        {
            // 着地
            m_pos.y -= m_move.y;
            m_move.y = 0.0f;
            m_isJump = false;
            m_isAnimJump = false;
        }
        else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
        {
            m_pos.y = chipRect.m_bottom + kHeight + 1; // めり込まない位置に補正
            m_move.y *= -1.0f; // 上方向への加速を下方向に変換
        }
    }
}

void Player::AddMoveY(float DisY)
{
    m_pos.y += DisY;
}

void Player::OnCollideY()
{
    m_move.y = 0;
}

Rect Player::GetRect() const
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

void Player::UpdateNormal()
{
    // 無敵時間の更新
    m_blinkFrameCount--;
    if (m_blinkFrameCount < 0)
    {
        m_blinkFrameCount = 0;
    }

    // 移動中のみ歩行アニメーションを行う
    if (m_isWalk)
    {
        // アニメーションの更新
        m_animFrame++;
        if (m_animFrame >= kAnimFrameCycle)
        {
            m_animFrame = 0;
        }
    }

    // プレイヤーが画面端から出ていかない
    if (m_pos.x < kStageLeftEnd)
    {
        m_pos.x = kStageLeftEnd;
    }
    if (m_pos.x > kStageRightEnd)
    {
        m_pos.x = kStageRightEnd;
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

    // ジャンプ中
    if (m_isJump)
    {
        // ジャンプ中処理
        UpdateJump();

        // 初速度に重力を足す
        m_move.y += kGravity;

        // マップチップとの当たり判定
        Rect chipRect;
        CheckHitBgStage1(chipRect);
    }
    else // 地面についている場合
    {
        // ジャンプ処理
        if (pad & PAD_INPUT_1 && m_isJump == false)
        {
            m_isJump = true;
            m_jumpCount++;
        }
        else
        {
            m_jumpCount = 0;
        }

        if (m_jumpCount == 1 && m_isJump)
        {
            m_move.y = kJumpAcc;
            m_isAnimJump = false;
        }
        else
        {
            m_isJump = false;
        }

        m_pos.x += m_move.x;
        Rect chipRect;
        // 横の当たり判定
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.x > 0.0f)
            {
                m_pos.x = chipRect.m_left - kWidth * static_cast<float>(0.5f) - 1;
            }
            else if (m_move.x < 0.0f)
            {
                m_pos.x = chipRect.m_right + kWidth * static_cast<float>(0.5f) + 1;
            }
        }

        m_pos.y += m_move.y;
        // 縦の当たり判定
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.y > 0.0f) // プレイヤーが上下方向に移動している
            {
                // 地面に立っている何もしない
                m_pos.y = chipRect.m_top - 1;
                m_isJump = false;
                m_isAnimJump = false;
            }
            else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
            {
                m_pos.y = chipRect.m_bottom + kHeight + 1; // めり込まない位置に補正
                m_move.y *= -1.0f; // 上方向への加速を下方向に変換
            }
        }
        else
        {
            // 地面にすら当たっていない
            m_isJump = true;
        }
    }
}

/// <summary>
/// プレイヤーのHPが0以下になった場合
/// </summary>
void Player::UpdateDead()
{
    // 死亡後一瞬止まる
    m_deadFrameCount++;
    if (m_deadFrameCount < kDeadStopFrame)
    {
        return;
    }

    // 画面外に落ちていく演出
 /*   m_pos.y += m_jumpSpeed;
    m_jumpSpeed += kGravity;*/
}
