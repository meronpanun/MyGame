#include "TestPlayer.h"
#include "DxLib.h"
#include "BgStage1.h"
#include "Rect.h"
#include "Pad.h"
#include "Game.h"
#include <memory>

namespace
{
    // �L�����N�^�[�T�C�Y
    constexpr int kWidth = 20;
    constexpr int kHeight = 20;

    // �L�����N�^�[�̕`��T�C�Y
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �����蔻�蔼�a
    constexpr int kRadius = 9;
    
    // ���x
    constexpr float kSpeed = 3.0f;
    // ����
    constexpr float kAccel = 2.0f;

    // �d��
    constexpr float kGravity = 0.5f;
    // �W�����v��
    constexpr float kJumpAcc = -10.0f;

    constexpr int kUseFrame[] = { 2,3 };

    // �A�j���[�V����1�R�}�̃t���[����
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

    // ���E�ړ�
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

        // �_�b�V������
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

    // �A�j���[�V��������
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
