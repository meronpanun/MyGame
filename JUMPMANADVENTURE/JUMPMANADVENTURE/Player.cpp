#include "Player.h"
#include "DxLib.h"
#include "BgStage1.h"
#include "Pad.h"
#include "Game.h"
#include "Camera.h"
#include "SceneMain.h"
#include "Enemy.h"
#include <cassert>
#include <stdexcept>

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

    // ステージの右端座標
    constexpr int kStageRightEnd = 10200;

    // 速度
    constexpr float kSpeed = 3.0f;
    // 加速
   // constexpr float kAccel = 3.0f;
    constexpr float kAccel = 20.0f;

    // 重力
    constexpr float kGravity = 0.5f;

    // アニメーション1コマのフレーム数
    constexpr int kRunAnimFrame = 4;
    constexpr int kJumpAnimFrame = 12;

    // プレイヤーのジャンプアニメーション
    constexpr int kJumpFrame[] = { 0 };
    // プレイヤーの歩きアニメーション
    constexpr int kWalkFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };

    // アニメーションの1サイクルのフレーム
    constexpr int kAnimFrameCycle = _countof(kWalkFrame) * kRunAnimFrame;

    // ジャンプ力
    constexpr float kJumpAcc = -14.0f;
    // ジャンプの初速
    constexpr float kJumpPower = -8.0f; 
    // ジャンプの長押し時間
    constexpr int kPressShortJumpFrame = 10;	// 10フレーム
    constexpr int kPressMediumJumpFrame = 30;	// 30フレーム
    // ジャンプの高さ調整
    constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
    constexpr float kInJumpHeight = 0.8f;		// 中ジャンプ

    // 無敵時間
    constexpr int kInvincible = 60;

    // プレイヤーの初期HP
    constexpr int kMaxHp = 3;

    // 死亡演出
    constexpr int kDeadStopFrame = 30;      // 死んだ瞬間止まる時間
    constexpr float kDeadJumpSpeed = -4.0f; // 死んだあと飛び上がる初速
    constexpr float kDeadPosY = -15.0f;

    // リスポーン遅延時間（フレーム数）
    constexpr int kRespawnDelay = 120; // 2秒（60FPSの場合）
}

Player::Player() :
    m_isJump(false),
    m_isRightMove(false),
    m_isLeftMove(false),
    m_isWalk(false),
    m_isGround(false),
    m_move(kSpeed, 0.0f),
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
    m_isAnimTurn(false),
    m_isGameOver(false),
    m_respawnTimer(0),
    m_isControlDisabled(false),
    m_height(0.0f)
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
    if (m_isControlDisabled)
    {
        // 操作無効時はアニメーションのみ更新
        if (m_isWalk)
        {
            // アニメーションの更新
            m_animFrame++;
            if (m_animFrame >= kAnimFrameCycle)
            {
                m_animFrame = 0;
            }
        }

        // ジャンプアニメーションの更新
        if (m_isJump)
        {
            m_jumpFrame++;
            if (m_jumpFrame >= _countof(kJumpFrame) * kJumpAnimFrame)
            {
                m_jumpFrame = 0;
            }
        }

        // プレイヤーの位置を更新しないようにする
        return;
    }

    // 生きているときと死んでいるときで処理を切り分ける
    if (m_hp > 0)
    {
        // リスポーンに遅延をつける
        if (m_respawnTimer > 0)
        {
            --m_respawnTimer;
            if (m_respawnTimer == 0)
            {
                Respawn();
            }
        }
        else
        {
            UpdateNormal();
        }
    }
    else
    {
        UpdateDead();
    }
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
    return m_pos.x - (kGraphWidth * kScale * 0.5f);
}

float Player::GetTop() const
{
    return m_pos.y - kGraphHeight * kScale;
}

float Player::GetRigth() const
{
    return m_pos.x + (kGraphWidth * kScale * 0.5f);
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
            m_pos.x = chipRect.m_left - kGraphWidth * kScale * 0.5f - 1; // 左側の補正
        }
        else if (m_move.x < 0.0f) // プレイヤーが左方向に移動している
        {
            m_pos.x = chipRect.m_right + kGraphWidth * kScale * 0.5f + 1; // 右側の補正
        }
    }

    // 縦の当たり判定
    m_pos.y += m_move.y;
    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
    {
        if (m_move.y > 0.0f) // プレイヤーが下方向に移動している
        {
            // 着地
            m_pos.y = chipRect.m_top - 1;
            m_move.y = 0.0f;
            m_isJump = false;
            m_isAnimJump = false;
            m_isGround = true;
        }
        else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
        {
            m_pos.y = chipRect.m_bottom + kGraphHeight * kScale + 1; // めり込まない位置に補正
            m_move.y *= -1.0f; // 上方向への加速を下方向に変換
        }
    }
    else
    {
        // 地面にすら当たっていない
        m_isJump = true;
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

void Player::Draw()
{
    // 半透明な板の描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明の設定
    DrawBox(0, 0, 1280, 100, 0x000000, TRUE);  // 半透明な黒い板を描画
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ブレンドモードを元に戻す

	// プレイヤーが無敵時間中は点滅させる
	if ((m_blinkFrameCount / 2) % 2)
	{
		return;
	}

    // プレイヤーのアニメーションフレーム
    int animFrame = m_animFrame / kRunAnimFrame;
    // プレイヤーの切り取り画像
    int walkSrcX = kWalkFrame[animFrame] * kGraphWidth;
    int walkSrcY = kGraphHeight;

    //ジャンプするときのアニメーションフレーム
    int jumpAnimFrame = m_jumpFrame / kJumpAnimFrame;
    //プレイヤージャンプの切り取り座標
    int jumpSrcX = kJumpFrame[jumpAnimFrame] * kGraphHeight;

    // ジャンプした場合
    if (m_isAnimJump)
    {
        DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kColChipAdjustmentY * kScale),
            jumpSrcX, 0, kGraphWidth, kGraphHeight, kScale, 0,
            m_jumpHandle, true, m_isAnimTurn);
    }
    else
    {
        DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kColChipAdjustmentY * kScale),
            walkSrcX, 0, kGraphWidth, kGraphHeight, kScale, 0,
            m_walkHandle, true, m_isAnimTurn);

    }
 

#ifdef DISP_COLLISON
    // 当たり判定のデバッグ表示
    DrawBox(GetLeft() + m_pCamera->m_drawOffset.x, 
        GetTop(),
        GetRigth() + m_pCamera->m_drawOffset.x, 
        GetBottom(),
        0xff0000, false);
#endif // DISP_COLLISION
}

void Player::OnDamage()
{
    // 既にダメージを受けている(無敵時間)間は
    // 再度ダメージを受けることはない
    if (m_blinkFrameCount > 0)
    {
        return;
    }
    // 無敵時間(点滅する時間)を設定する
    m_blinkFrameCount = kInvincible;
    // ダメージを受ける
    m_hp--;

    // 画面揺れ
    if (m_pCamera)
    {
        // 強度10.0、30フレームの揺れ
        m_pCamera->Shake(10.0f, 30); 
    }

	// HPが0以下になったら死亡演出を行う
	if (m_hp <= 0)
	{
        InitDead();
	}
}

void Player::UpdateNormal()
{
    // プレイヤーが穴に落下した場合
    if ((m_pos.y - kGraphHeight) > kFallMaX)
    {
        // 画面揺れ
        if (m_pCamera)
        {
            // 強度10.0、30フレームの揺れ
            m_pCamera->Shake(10.0f, 30);
        }
        StartRespawn();
    }

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
    if (m_pos.x > kStageRightEnd)
    {
        m_pos.x = kStageRightEnd;
    }
    // プレイヤーの位置がカメラの左端を超えないように制限
    if (m_pos.x < m_pCamera->GetLeft())
    {
        m_pos.x = m_pCamera->GetLeft();
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
    else // 左右移動をしていない場合
    {
        m_isRightMove = false;
        m_isLeftMove = false;
        m_move.x = 0;
		m_isWalk = false;
    }

    // 右ダッシュ
    if (pad & PAD_INPUT_3 && m_isRightMove)
    {
        m_move.x += kAccel;
        m_isAnimTurn = false;
    }
    // 左ダッシュ
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

        // ジャンプアニメーションの更新
        m_jumpFrame++;
        if (m_jumpFrame >= _countof(kJumpFrame) * kJumpAnimFrame)
        {
            m_jumpFrame = 0;
        }
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
                m_isAnimJump = true;
            }
            else
            {
                m_isJump = false;
            }
        }
        // マップチップとの当たり判定
        Rect chipRect;
        CheckHitBgStage1(chipRect);
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
    m_pos.y += m_jumpSpeed;
    m_jumpSpeed += kGravity;

    // プレイヤーが画面外に完全に落ちたかどうかを判定
    if (m_pos.y > Game::kScreenHeight + kGraphHeight * kScale)
    {
        m_isGameOver = true; // ゲームオーバー演出を開始するフラグを設定
    }
}

bool Player::IsGameOver() const
{
    return m_isGameOver;
}

void Player::StartRespawn()
{
    m_respawnTimer = kRespawnDelay;
}

void Player::Respawn()
{
    // プレイヤーの位置をリセット
    m_pos.x = kRestartPosX;
    m_pos.y = kRestartPosY;

    // カメラもプレイヤー同様リセット
    m_pCamera->m_pos.SetPos(m_pos.x, m_pos.y);

    // hpを減らす
    m_hp--;

    // HPが0以下になったら死亡演出を行う
    if (m_hp <= 0)
    {
        m_isGameOver = true; // ゲームオーバー演出を開始するフラグを設定
        return;
    }
}

// プレイヤーの操作を無効化する
void Player::DisableControl()
{
    m_isControlDisabled = true;
}

// プレイヤーの操作が無効かどうかを判定する
bool Player::IsControlDisabled() const
{
     return m_isControlDisabled;
}

// プレイヤーのX座標を設定する
void Player::SetPosX(float x)
{
    m_pos.x = x;
}

// プレイヤーが地面にいるかどうかを判定する
bool Player::IsOnGround() const
{
    return m_isGround;
}

// プレイヤーを地面の高さまでゆっくり落とす
void Player::FallToGround(float groundHeight)
{
    if (m_pos.y < groundHeight - m_height) 
    {
        m_pos.y += 3.0f; // 落下速度を調整
        if (m_pos.y > groundHeight - m_height) 
        {
            m_pos.y = groundHeight - m_height;
        }
    }
}

// プレイヤーが歩いているかどうかを設定する
void Player::SetIsWalking(bool isWalking)
{
    m_isWalk = isWalking;
}

void Player::UpdateAnimation()
{
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
}

//  プレイヤーが死亡状態になったときの初期化
void Player::InitDead()
{
	m_jumpSpeed = kDeadPosY;
	m_deadFrameCount = 0;
	m_blinkFrameCount = 0;
}
