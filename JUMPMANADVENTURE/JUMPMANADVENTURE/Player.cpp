#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // �v���C���[�O���t�B�b�N�̕��ƍ���
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �A�j���[�V�����̃R�}��
    constexpr int kWalkAnimNo[] = { 2,3 };
    constexpr int kWalkAnimNum = _countof(kWalkAnimNo);

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kWalkAnimFrame = 10;

    // �v���C���[�̈ړ����x
    constexpr float kSpeed = 2.0f;

    // �n�ʂ̍���
    constexpr float kFieldHeight = 720.0f - 78.0f;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v��
    constexpr float kGravity = 0.4f; // �d��
}

Player::Player() :
    m_handle(-1),
    m_walkFrameCount(0),
    m_isRun(false),
    m_pos(150.0f, kFieldHeight),
    m_isDirLeft(false),
    m_isJump(false),
    m_jumpSpeed(0.0f)
{
    m_handle = LoadGraph("date/image/Mario.png");
    assert(m_handle != -1);
}

Player::~Player()
{
    // �O���t�B�b�N�̊J��
    DeleteGraph(m_handle);
}

void Player::Init()
{
}

void Player::Update()
{

    // ���E�ɃL�����N�^�[�𓮂���
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // ���L�[�������Ă���Ƃ��̏���
        m_pos.x -= kSpeed;  // �������Ɉʒu�ύX
        m_isDirLeft = true; // ������
        m_isRun = true;     // �����Ă���
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // �E�L�[�������Ă���Ƃ��̏���
        m_pos.x += kSpeed;   // �E�����Ɉʒu�ύX
        m_isDirLeft = false; // �E����
        m_isRun = true; // �����Ă���
    }

    // 1�{�^�����������Ƃ��ɃW�����v����
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        if (!m_isJump)
        {
            m_isJump = true;
            m_jumpSpeed = kJumpPower;
        }
    }

    // �A�j���[�V�����̍X�V
    if (m_isRun)
    {
        // �ړ����̂ݕ����A�j���[�V�������s��
        m_walkFrameCount++;
        if (m_walkFrameCount >= kWalkAnimNum * kWalkAnimFrame)
        {
            m_walkFrameCount = 0;
        }
    }

    if (m_isJump)
    {
        m_pos.y += m_jumpSpeed;

        m_jumpSpeed += kGravity;

        if (m_jumpSpeed > 0.0f)
        {
            if (m_pos.y >= kFieldHeight)
            {
                // �W�����v�I������
                m_isJump = false;
                m_jumpSpeed = 0.0f;
                // �n�ʂɂ߂荞�܂Ȃ��悤�ɒn�ʂ̍����Ɉʒu��␳
                m_pos.y >= kFieldHeight;
            }
        }
    }
}

void Player::Draw()
{
    int animIndex = m_walkFrameCount / kWalkAnimFrame;
    int animNo = kWalkAnimNo[animIndex];

    DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
        animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
         m_handle,true);

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



