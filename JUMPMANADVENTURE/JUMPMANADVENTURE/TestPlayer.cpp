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
//    // �L�����N�^�[�T�C�Y
//    constexpr int kWidth = 20;
//    constexpr int kHeight = 20;
//
//    // �L�����N�^�[�̕`��T�C�Y
//    constexpr int kGraphWidth = 32;
//    constexpr int kGraphHeight = 32;
//
//    // �����蔻�蔼�a
//    constexpr int kRadius = 9;
//    
//    // ���x
//    constexpr float kSpeed = 3.0f;
//    // ����
//    constexpr float kAccel = 2.0f;
//
//    // �d��
//    constexpr float kGravity = 0.5f;
//    // �W�����v��
//    constexpr float kJumpAcc = 00.0f;
//
//    constexpr int kUseFrame[] = { 2,3 };
//
//    // �A�j���[�V����1�R�}�̃t���[����
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
//    // ���E�ړ�
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
//        // �_�b�V������
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
//    // �A�j���[�V��������
//    m_animFrame++;
//    if (m_animFrame >= kAnimFrameCycle)
//    {
//        m_animFrame = 0;
//    }
//
//    // �W�����v����
//    if (m_isJump) // �W�����v��
//    {
//        m_moveY += kGravity;
//
//        m_posX += m_moveX;
//
//        TestRect chipRect;
//        // ��
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            if (m_moveX > 0.0f)
//            {
//                printfDx("�v���C���[���E�����}�b�v�ɂԂ�����\n");
//                m_posX = chipRect.left - kWidth * 0.5 - 1;
//            }
//            else if (m_moveX < 0.0f)
//            {
//                printfDx("�v���C���[���������}�b�v�ɂԂ�����\n");
//                m_posX = chipRect.right + kWidth * 0.5 + 1;
//            }
//        }
//
//        m_posY += m_moveY;
//        // �c
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
//    else // �n�ʂɂ��Ă���ꍇ
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
//        // ��
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            if (m_moveX > 0.0f)
//            {
//                printfDx("�v���C���[���E�����}�b�v�ɂԂ�����\n");
//                m_posX = chipRect.left - kWidth * 0.5 - 1;
//            }
//            else if (m_moveX < 0.0f)
//            {
//                printfDx("�v���C���[���������}�b�v�ɂԂ�����\n");
//                m_posX = chipRect.right + kWidth * 0.5 + 1;
//            }
//        }
//
//        m_posY += m_moveY;
//        // �c
//        if (m_pTestMap->IsCol(getRect(), chipRect))
//        {
//            // �㉺�ǂ��炩�������������f�o�b�N�\��
//            if (m_moveY > 0.0f) // �v���C���[���㉺�����Ɉړ����Ă���
//            {
//                // �n�ʂɗ����Ă��鉽�����Ȃ�
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
//    // �v���C���[�̃A�j���[�V�����t���[��
//    int animFrame = m_animFrame / kSingleAnimFrame;
//    // �v���C���[�̐؂���摜
//    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
//    int walkSrcX = kUseFrame[animFrame];
//    int walkScrY = kGraphHeight;
//
//
//    // �W�����v�����ꍇ
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
