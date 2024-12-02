//#include "TestPlayer.h"
//#include "DxLib.h"
//#include "TestMap.h"
//#include "Rect.h"
//#include "Pad.h"
//#include "Game.h"
//#include <memory>
//
//namespace
//{
//    // キャラクターサイズ
//    constexpr int kWidth = 20;
//    constexpr int kHeight = 20;
//
//    // キャラクターの描画サイズ
//    constexpr int kGraphWidth = 32;
//    constexpr int kGraphHeight = 32;
//
//    // 当たり判定半径
//    constexpr int kRadius = 9;
//    
//    // 速度
//    constexpr float kSpeed = 3.0f;
//    // 加速
//    constexpr float kAccel = 2.0f;
//
//    // 重力
//    constexpr float kGravity = 0.5f;
//    // ジャンプ力
//    constexpr float kJumpAcc = 00.0f;
//
//    constexpr int kUseFrame[] = { 2,3 };
//
//    // アニメーション1コマのフレーム数
//    constexpr int kSingleAnimFrame = 10;
//    constexpr int kJumpAnimFrame = 12;
//
//    constexpr int kAnimFrameCycle = _countof(kUseFrame) * kSingleAnimFrame;
//
//    constexpr int kUseJumpFrame[] = { 0 };
//
//    
//}
//
//TestPlayer::TestPlayer() :
//    m_isJump(false),
//    m_isRight(false),
//    m_isLeft(false),
//    m_moveX(0.0f),
//    m_moveY(0.0f),
//    m_posX(120.0f),
//    m_posY(690.0f),
//    m_dir(kNutral),
//    m_animationFrame(0),
//    m_animFrame(0),
//    m_animCount(0),
//    m_isAnimJump(false),
//    m_isCommand(false),
//    m_isAnimTurn(false)
//{
//    m_playerHandle01 = LoadGraph("date/image/Mario.png");
//    m_playerHandle02 = LoadGraph("date/image/Jump.png");
//}
//
//TestPlayer::~TestPlayer()
//{
//    DeleteGraph(m_playerHandle01);
//    DeleteGraph(m_playerHandle02);
//}
//
//void TestPlayer::Init()
//{
//}
//
//void TestPlayer::Update()
//{
//    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//    bool isMove = false;
//    
//    Pad::Update();
//
//    m_dir = kNutral;
//
//    m_moveX = 0.0f;
//
//    // 左右移動
//    if (!m_isCommand)
//    {
//        if (pad & PAD_INPUT_LEFT)
//        {
//            m_moveX -= kSpeed;
//            m_isLeft = true;
//            m_isAnimTurn = true;
//            m_dir = kWalk;
//        }
//        else
//        {
//            m_isLeft = false;
//        }
//
//        if (pad & PAD_INPUT_RIGHT)
//        {
//            m_moveX += kSpeed;
//            m_isRight = true;
//            m_isAnimTurn = false;
//            m_dir = kWalk;
//        }
//        else
//        {
//            m_isRight = false;
//        }
//
//        // ダッシュ処理
//        if (pad & PAD_INPUT_3 && m_isRight)
//        {
//            m_moveX += kAccel;
//            m_dir = kWalk;
//            m_isAnimTurn = false;
//        }
//        if (pad & PAD_INPUT_3 && m_isLeft)
//        {
//            m_moveX -= kAccel;
//            m_dir = kWalk;
//            m_isAnimTurn = true;
//        }
//    }
//
//    // アニメーション処理
//    m_animFrame++;
//    if (m_animFrame >= kAnimFrameCycle)
//    {
//        m_animFrame = 0;
//    }
//
//    // ジャンプ処理
//    if (m_isJump) // ジャンプ中
//    {
//        m_moveY += kGravity;
//
//        m_posX += m_moveX;
//
//        TestRect chipRect;
//        // 横
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            if (m_moveX > 0.0f)
//            {
//                printfDx("プレイヤーが右側がマップにぶつかった\n");
//                m_posX = chipRect.left - kWidth * 0.5 - 1;
//            }
//            else if (m_moveX < 0.0f)
//            {
//                printfDx("プレイヤーが左側がマップにぶつかった\n");
//                m_posX = chipRect.right + kWidth * 0.5 + 1;
//            }
//        }
//
//        m_posY += m_moveY;
//        // 縦
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            if (m_moveY > 0.0f)
//            {
//                m_posY -= m_moveY;
//                m_moveY = 0.0f;
//                m_isJump = false;
//                m_isAnimJump = false;
//            }
//            else if (m_moveY < 0.0f)
//            {
//                m_posY = chipRect.bottom + kHeight + 1;
//                m_moveY *= 0.0f;
//            }
//        }
//    }
//    else // 地面についている場合
//    {
//        if (!m_isCommand)
//        {
//            if (pad & PAD_INPUT_1 && m_isJump == false)
//            {
//                m_isJump = true;
//                m_jumpCount++;
//            }
//            else m_jumpCount = 0;
//
//            if (m_jumpCount == 1 && m_isJump)
//            {
//                m_moveY = kJumpAcc;
//                m_isAnimJump = true;
//            }
//            else m_isJump = false;
//        }
//
//        m_posX += m_moveX;
//        TestRect chipRect;
//        // 横
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            if (m_moveX > 0.0f)
//            {
//                printfDx("プレイヤーが右側がマップにぶつかった\n");
//                m_posX = chipRect.left - kWidth * 0.5 - 1;
//            }
//            else if (m_moveX < 0.0f)
//            {
//                printfDx("プレイヤーが左側がマップにぶつかった\n");
//                m_posX = chipRect.right + kWidth * 0.5 + 1;
//            }
//        }
//
//        m_posY += m_moveY;
//        // 縦
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            // 上下どちらか当たったかをデバック表示
//            if (m_moveY > 0.0f) // プレイヤーが上下方向に移動している
//            {
//                // 地面に立っている何もしない
//                m_posY = chipRect.top - 1;
//                m_isJump = false;
//                m_isAnimJump = false;
//            }
//            else if (m_moveY < 0.0f)
//            {
//                m_posY = chipRect.bottom + kHeight + 1;
//                m_moveY *= 0.0f;
//            }
//        }
//        else
//        {
//            m_isJump = true;
//        }
//    }
//}
//
//void TestPlayer::Draw()
//{
//    // プレイヤーのアニメーションフレーム
//    int animFrame = m_animFrame / kSingleAnimFrame;
//    // プレイヤーの切り取り画像
//    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
//    int walkSrcX = kUseFrame[animFrame];
//    int walkScrY = kGraphHeight;
//
//
//    // ジャンプした場合
//    if (m_isAnimJump)
//    {
//
//        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
//            kGraphWidth, 0, kGraphWidth, kGraphHeight,
//            m_playerHandle02, true, m_isAnimTurn);
//    }
//    else
//    {
//        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
//            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight,
//            m_playerHandle01, true, m_isAnimTurn);
//
//    }
//}
//
//float TestPlayer::GetRadius()
//{
//    return kRadius;
//}
//
//float TestPlayer::GetLeft() const
//{
//    return m_posX - kWidth * 0.5;
//}
//
//float TestPlayer::GetTop() const
//{
//    return m_posY -kHeight;
//}
//
//float TestPlayer::GetRigth() const
//{
//    return m_posX + kWidth * 0.5;
//}
//
//float TestPlayer::GetBottom() const
//{
//    return m_posY;
//}
//
//TestRect TestPlayer::getRect()
//{
//    TestRect rect;
//    rect.top = GetTop();
//    rect.bottom = GetBottom();
//    rect.left = GetLeft();
//    rect.right = GetRigth();
//    return rect;
//}
