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
    // プレイヤーの描画サイズ
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;
    
    // プレイヤーのリスポーン位置
    constexpr float kRestartPosX = 150.0f;
    constexpr float kRestartPosY = 610.0f;

    // 拡大率
    constexpr float kScale = 2.0f;

    // 当たり判定の半径
    constexpr int kRadius = 9;

    // マップチップとの当たり判定の調整
    constexpr int kColChipAdjustmentX = 30;
    constexpr int kColChipAdjustmentY = 15;

    // 底の上限 
    constexpr int kFallMaX = 920;

    // ステージの左右端座標
    constexpr int kStageLeftEnd = 70;
    constexpr int kStageRightEnd = 6500;

    // 速度
    constexpr float kSpeed = 3.0f;
    // 加速
    constexpr float kAccel = 6.0f;

    // 重力
    constexpr float kGravity = 0.5f;

    // アニメーション1コマのフレーム数
    constexpr int kRunAnimFrame = 4;
    constexpr int kJumpAnimFrame = 12;

    // キャラクターのジャンプアニメーション
    constexpr int kJumpFrame[] = { 0 };
    // キャラクターの歩きアニメーション
    constexpr int kWalkFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
    // アニメーションの1サイクルのフレーム
    constexpr int kAnimFrameCycle = _countof(kWalkFrame) * kRunAnimFrame;

    // ジャンプ力
    constexpr float kJumpAcc = -12.5f;
    // ジャンプの初速
    constexpr float kJumpPower = -8.0f; 
    // ジャンプの長押し時間
    constexpr int kPressShortJumpFrame = 10;	// 10フレーム
    constexpr int kPressMediumJumpFrame = 30;	// 30フレーム
    // ジャンプの高さ調整
    constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
    constexpr float kInJumpHeight = 0.8f;		// 中ジャンプ

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
    m_isRightMove(false),
    m_isLeftMove(false),
    m_isWalk(false),
    m_isGround(false),
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
    // グラフィックの読み込み
    m_walkHandle = LoadGraph("data/image/Run.png");
    assert(m_walkHandle != -1);
    m_jumpHandle = LoadGraph("data/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    // グラフィックの開放
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
    if ((m_pos.y - kGraphHeight) > kFallMaX)
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
    int animFrame = m_animFrame / kRunAnimFrame;
    // プレイヤーの切り取り画像
    int walkSrcX = kWalkFrame[animFrame] * kGraphWidth;
    int walkSrcY = kGraphHeight;

    //ジャンプするときのアニメフレーム
    int jumpAnimFrame = m_animFrame / kJumpAnimFrame;

    //プレイヤージャンプの切り取り座標
    int JsrcX = kJumpFrame[jumpAnimFrame] * kGraphHeight;
    int JsrcY = 0;

    // ジャンプした場合
    //if (m_isAnimJump)
    //{

    //    DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth + kColChipAdjustmentX + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight - kColChipAdjustmentY),
    //        JsrcX, JsrcY, kGraphWidth, kGraphHeight, kScale, 0,
    //        m_jumpHandle, true, m_isAnimTurn);
    //}
    //else
    //{
    //    DrawRectRotaGraph(static_cast<int>( m_pos.x - kGraphWidth + kColChipAdjustmentX + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight - kColChipAdjustmentY),
    //        walkSrcX, 0, kGraphWidth, kGraphHeight, kScale, 0,
    //        m_walkHandle, true, m_isAnimTurn);

    //}
    
    DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth + kColChipAdjustmentX + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight + kColChipAdjustmentY),
        walkSrcX, 0, kGraphWidth, kGraphHeight, 1.0f ,0, 
        m_walkHandle, true, m_isAnimTurn);

   

#ifdef DISP_COLLISON
    // 当たり判定のデバッグ表示
    //DrawBox(GetLeft() + m_pCamera->m_drawOffset.x, 
    //    GetTop(),
    //    GetRigth() + m_pCamera->m_drawOffset.x, 
    //    GetBottom(),
    //    GetColor(0, 0, 255), false);
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

void Player::JumpOnEnemy()
{
    m_move.y = kJumpAcc * 0.5f; // 少しY軸方向にジャンプ
    m_isJump = true;
    m_isGround = false;
}

float Player::GetRadius() const
{
    return kRadius;
}

float Player::GetLeft() const
{
    return m_pos.x - kGraphWidth * static_cast<float>(0.5f);
}

float Player::GetTop() const
{
    return m_pos.y - kGraphHeight;
}

float Player::GetRigth() const
{
    return m_pos.x + kGraphWidth * static_cast<float>(0.5f);
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
            m_pos.x = chipRect.m_left - kGraphWidth * static_cast<float>(0.5f) - 1; // 左側の補正
        }
        else if (m_move.x < 0.0f) // プレイヤーが左方向に移動している
        {
            m_pos.x = chipRect.m_right + kGraphWidth * static_cast<float>(0.5f) + 1; // 右側の補正
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
            m_isGround = true;
        }
        else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
        {
            m_pos.y = chipRect.m_bottom + kGraphHeight + 1; // めり込まない位置に補正
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

float Player::GetMoveY() const
{
    return m_move.y;
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

    // 右移動
    if (pad & PAD_INPUT_RIGHT)
    {
        m_isRightMove = true;
        m_isLeftMove = false;
        m_move.x = kSpeed;
        m_isAnimTurn = false;
        m_isWalk = true;
    }
    // 左移動
    else if (pad & PAD_INPUT_LEFT)
    {
        m_isRightMove = false;
        m_isLeftMove = true;
        m_move.x = -kSpeed;
        m_isAnimTurn = true;
        m_isWalk = true;
    }
    else
    {
        m_isLeftMove = false;
        m_isRightMove = false;
        m_move.x = 0;
        m_isWalk = false;
    }

    // ダッシュ処理
    if (pad & PAD_INPUT_3 && m_isRightMove)
    {
        m_move.x += kAccel;
        m_isAnimTurn = false;
    }
    if (pad & PAD_INPUT_3 && m_isLeftMove)
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
        if (m_isGround)
        {
            m_jumpFrame = 0;
            m_isJump = false;
            // ジャンプ処理
            if (pad & PAD_INPUT_1)
            {
                m_isJump = true;
                m_isGround = false;
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
        }

        // 横の当たり判定
        m_pos.x += m_move.x;
        Rect chipRect;
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.x > 0.0f)
            {
                m_pos.x = chipRect.m_left - kGraphWidth * static_cast<float>(0.5f) - 1;
            }
            else if (m_move.x < 0.0f)
            {
                m_pos.x = chipRect.m_right + kGraphWidth * static_cast<float>(0.5f) + 1;
            }
        }

        // 縦の当たり判定
        m_pos.y += m_move.y;
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.y > 0.0f) // プレイヤーが下方向に移動している
            {
                // 地面に立っている何もしない
                m_pos.y = chipRect.m_top - 1;
                m_isJump = false;
                m_isAnimJump = false;
                m_isGround = true;;
            }
            else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
            {
                m_pos.y = chipRect.m_bottom + kGraphHeight + 1; // めり込まない位置に補正
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
