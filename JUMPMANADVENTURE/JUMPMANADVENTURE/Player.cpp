#include "Player.h"
#include "DxLib.h"
#include "pad.h"
#include "Game.h"
#include "BgStage1.h"
#include "SceneStage1.h"
#include <cassert>

namespace
{
    // キャラクターグラフィックの幅と高さ
    constexpr int kScale = 0.3f;
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // 当たり判定サイズ
    constexpr int kColX = static_cast<int>(kGraphWidth);
    constexpr int kColY = static_cast<int>(kGraphHeight);

    // 当たり判定サイズの調整
    constexpr int kColAdjustment = 0.5f;

    // マップチップとの当たり判定調整
    constexpr int kColChipadjustment = 15;

    // アニメーション1コマのフレーム数
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // アニメーションのコマ数
   // constexpr int kJumpAnimNum[] = { 0 };
    constexpr int kWalkAnimNum[] = { 2,3 };
    constexpr int kAnimFrameCycle = _countof(kWalkAnimNum) * kSingleAnimFrame;

    // キャラクターの移動速度
    constexpr float kSpeed = 2.0f;

	// 地面の高さ
	constexpr float kFieldHeight = 720.0f - 80.0f;

    // ジャンプ処理
    constexpr float kJumpPower = -8.0f; // ジャンプの初速
    constexpr float kGravity = 0.4f;    // 重力
    // ジャンプの長押し時間
    constexpr int kPressShortJumpFrame = 10;	// 10フレーム
    constexpr int kPressMediumJumpFrame = 30;	// 30フレーム
    // ジャンプの高さ調整
    constexpr float kLittleJumpHeight = 0.5f;	// 小ジャンプ
    constexpr float kInJumpHeight = 0.8f;		// 中ジャンプ
    constexpr float kBigJumpHeight = 1.0f;		// 大ジャンプ

    // マップチップのサイズ
    constexpr int kMapWidth = 16;
    constexpr int kMapHeight = 16;
}

Player::Player() :
    m_pBg(nullptr),
    m_pMain(nullptr),
    m_move(0.0f,0.0f),
    m_isDirLeft(false),
    m_isGround(false),
    m_isJump(false),
    m_jumpFrame(0),
    m_keyState(0),
    m_pressTime(0),
    m_nowPressTime(0),
    m_walkHandle(0),
    m_jumpHandle(0),
    m_animFrame(0),
	//m_pos(120.0f, kFieldHeight),
    m_walkFrameCount(0),
    m_isWalk(false),
    m_isAnimJump(false),
    m_jumpSpeed(0.0f),
    m_animation(Anim::kWalk),
    m_walkAnimFrame(0)
{
    m_walkHandle = LoadGraph("date/image/Mario.png");
    assert(m_walkHandle != -1);

    m_jumpHandle = LoadGraph("date/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    // グラフィックの開放
    DeleteGraph(m_walkHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init(Bg* pBg, SceneMain* pMain, Vec2 initPos)
{
    // 背景
    m_pBg = pBg;
    m_pMain = pMain;
    // 現在位置
    m_pos.x = initPos.x;
    m_pos.y = initPos.y;
    // ジャンプフラグ
    m_isGround = false;
    m_isJump = false;
    // 加速度
    m_move.y = 0.0f;
    // 待機状態
    m_animation = Anim::kWalk;
    m_walkAnimFrame = 0;
}

void Player::Update()
{
    UpdatePlayerAnim();
    // 左右にキャラクターを動かす
    //m_isWalk = false;
    //if (Pad::IsPress(PAD_INPUT_LEFT))
    //{
    //    // 左キーを押している時の処理
    //    m_pos.x -= kSpeed;   // 左方向に位置を変更
    //    m_isDirLeft = true;  // キャラクターが左を向いている
    //    m_isWalk = true;      // 走っている
    //}
    //if (Pad::IsPress(PAD_INPUT_RIGHT))
    //{
    //    // 右キーを押している時の処理
    //    m_pos.x += kSpeed;   // 右方向に位置を変更
    //    m_isDirLeft = false; // キャラクターが左を向いている
    //    m_isWalk = true;      // 走っている
    //}

    // パッドを使用する
    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    m_isWalk = false;
    if (pad & (PAD_INPUT_RIGHT))
    {
        m_pos.x += kSpeed;
        m_isDirLeft = false;
       // m_animation = Anim::kWalk;
        m_isWalk = true;
    }
    if (pad & (PAD_INPUT_LEFT))
    {
        m_pos.x -= kSpeed;
        m_isDirLeft = true;
       // m_animation = Anim::kWalk;
        m_isWalk = true;
    }
   /* else
    {
        m_move.x = 0;
    }*/


 // 地面に接している
  if (m_isGround)
  {
      m_jumpFrame = 0;
      m_isJump = false;
      m_isAnimJump = false;
      if (Pad::IsTrigger(PAD_INPUT_1))
      {
          m_isGround = false;
          m_isJump = true;
          m_move.y += kJumpPower;
      }
      // マップチップとの当たり判定
      Rect chipRect;
      CheckHitMap(chipRect);
  }
  else
  {
     // m_isAnimJump = true;
      if (m_isJump)
      {
          UpdateJump();
      }
      m_move.y += kGravity;

      // マップチップとの当たり判定
      Rect chipRect;
      CheckHitMap(chipRect);
  }

    // ジャンプの処理
    //if (pad & (PAD_INPUT_1))
    //{
    //    if (!m_isJump)
    //    {
    //        m_isJump = true;
    //        m_isAnimJump = false;
    //        m_jumpSpeed = kJumpPower;
    //    }
    //}

    //if (m_isJump)
    //{
    //    m_pos.y += m_jumpSpeed;

    //    m_jumpSpeed += kGravity; // 毎フレーム下方向に加速する

    //    if (m_jumpSpeed > 0.0f)
    //    {
    //        if (m_pos.y >= kFieldHeight)
    //        {
    //             ジャンプ終了する
    //            m_isJump = false;
    //            m_isAnimJump = false;
    //            m_jumpSpeed = 0.0f;
    //            
    //             地面にめり込むことがあるので地面の高さに位置を補正する
    //            m_pos.y >= kFieldHeight;
    //        }
    //    }
    //}
    printfDx("m_pos:(%d,%d)\n",
        (int)m_pos.x,
        (int)m_pos.y);
}

void Player::Draw()
{
    DrawPlayer();
}

//float Player::GetLeft() const
//{
//	return (m_pos.x - kGraphWidth * 0.5f);
//}
//
//float Player::GetTop() const
//{
//	return (m_pos.y - kGraphHeight);
//}
//
//float Player::GetRigth() const
//{
//	return (m_pos.x + kGraphWidth * 0.5f);
//}
//
//float Player::GetBottom() const
//{
//	return  m_pos.y;
//}

void Player::CheckHitMap(Rect chipRect)
{
    // 横からあたったかチェックする
    m_pos.x += m_move.x;
    m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kColX), static_cast<float>(kColY));
    if (m_pBg->IsCollision(m_colRect, chipRect))
    {
        if (m_move.x > 0.0f)
        {
            m_pos.x = chipRect.GetLeft() - kGraphWidth * 0.5f + kColChipadjustment;
        }
        else if (m_move.x < 0.0f)
        {
            m_pos.x = chipRect.GetRight() + kGraphWidth * 0.5f - kColChipadjustment;
        }
    }

    // 縦からあたったかチェックする
    m_pos.y += m_move.y;
    m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kColX), static_cast<float>(kColY));
    if (m_pBg->IsCollision(m_colRect, chipRect))
    {
        if (m_move.x > 0.0f)
        {
            m_pos.y = chipRect.GetTop() - kGraphHeight * 0.5f;
            m_isGround = true;
        }
        else if (m_move.x < 0.0f)
        {
            m_pos.y = chipRect.GetBottom() + kGraphHeight * 0.5f;
            m_move.y *= -1.0f;
        }
    }
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

void Player::UpdatePlayerAnim()
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
}

void Player::DrawPlayer()
{
    // プレイヤーのアニメーションフレーム
    int animFrame = m_animFrame / kSingleAnimFrame;
    // プレイヤーの切り取り画像
    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
    int walkSrcX = kWalkAnimNum[animFrame];
    int walkScrY = kGraphHeight;
    // プレイヤージャンプの切り取り座標
//   int animJumpNo = kJumpAnimNum[animFrame];

  /*  if (m_animation == Anim::kWalk)
    {
        DrawRectRotaGraph(x, y, walkSrcX, walkScrY, kGraphWidth, kGraphHeight, kScale, 0.0f, m_walkHandle, true);
    }
    else if (m_animation == Anim::kJump)
    {
        DrawRectRotaGraph(x, y, 0, 0,kGraphWidth, kGraphHeight, kScale, 0.0f, m_jumpHandle, true);
    }*/



    // ジャンプした場合
    if (m_isAnimJump)
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_jumpHandle, true, m_isDirLeft);

    }
    else
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_walkHandle, true, m_isDirLeft);

    }
}






