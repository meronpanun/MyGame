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
    constexpr int kIdleAnimNum = 1;
    constexpr int kRunAnimNum = 3;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kSingleAnimFrame = 6;

    // �v���C���[�̈ړ����x
    constexpr float kSpeed = 2.0f;

    // �n�ʂ̍���
    constexpr float kFieldHeight = 720.0f - 78.0f;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v��
    constexpr float kGravity = 0.4f; // �d��

    // �_���[�W�����������̖��G����(�_�Ŏ���)
    constexpr int kDamegeBlinkFrame = 30;

    // �v���C���[�̏����c�@
    constexpr int kMaxHp = 3;

    // ���S���o
    constexpr int kDeadStopFrame = 30;      // ���񂾏u�Ԓ�~���鎞��
    constexpr float kDeadJumpSpeed = -4.0f; // ���񂾂��Ɣ�яオ�鏉�� 
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
    // �O���t�B�b�N�̊J��
    DeleteGraph(m_handleIdle);
    DeleteGraph(m_handleRun);
}

void Player::Init()
{
}

void Player::Update()
{
    // �����Ă���Ƃ��Ǝ���ł���Ƃ��ŏ�����؂蕪����
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
    // �_�ŏ���
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
    // ���Ƀ_���[�W���󂯂Ă���(���G����)�͍ēx�_���[�W���󂯂Ȃ�
    if (m_blinkFrameCount > 0)
    {
        return;
    }

    // ���G����
    m_blinkFrameCount = kDamegeBlinkFrame; // �_�ł��鎞�Ԃ�ݒ�

    // �_���[�W���󂯂�
    m_hp--;
    // HP��0�ȉ��ɂȂ����玀�S���o���J�n
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
    // ���G���Ԃ̍X�V
    m_blinkFrameCount--;
    if (m_blinkFrameCount < 0)
    {
        m_blinkFrameCount = 0;
    }

    // �A�j���[�V�����̍X�V
    m_animFrame++;

   // int totalFrame = kRunAnimNum * kSingleAnimFrame;
    int totalFrame = kIdleAnimNum * kSingleAnimFrame;
    if (m_isRun)
    {
        int totalFrame = kIdleAnimNum * kSingleAnimFrame;
    }
 

    // �A�j���[�V�����̍��v�t���[�����𒴂�����ŏ��ɖ߂�
    if (m_animFrame >= totalFrame)
    {
        m_animFrame = 0;
    }

    //  �O��̃A�j���[�V�����̏�Ԃ��o���Ă���
    bool isLastRun = m_isRun;

    // ���E�ɃL�����N�^�[�𓮂���
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // ���L�[�������Ă���Ƃ��̏���
        m_pos.x -= kSpeed;  // �������Ɉʒu�ύX
        m_isDirLeft = true; // �L�����N�^�[�����������Ă���
        m_isRun = true;
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // �E�L�[�������Ă���Ƃ��̏���
        m_pos.x += kSpeed;   // �E�����Ɉʒu�ύX
        m_isDirLeft = false; // �L�����N�^�[�����������Ă���
        m_isRun = true;
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

#ifdef _DEBUG
    // �����Ńo�b�N�@�\�@5�{�^��(L�{�^��)
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
                // �W�����v�I������
                m_isJump = false;
                m_jumpSpeed = 0.0f;
                // �n�ʂɂ߂荞�܂Ȃ��悤�ɒn�ʂ̍����Ɉʒu��␳
                m_pos.y >= kFieldHeight;
            }
        }
        // �������s�������ʁA�A�j���[�V�������ς���Ă����ꍇ�̏���
        if (m_isRun != isLastRun)
        {
            m_animFrame = 0;
        }
    }

}

void Player::UpdateDead()
{
    // ���S���u�~�܂�
    m_deadFrameCount++;
    if (m_deadFrameCount < kDeadStopFrame)
    {
        return;
    }

    // ��ʊO�ɗ����Ă������o
    m_pos.y += m_jumpSpeed;
    m_jumpSpeed += kGravity;
}
