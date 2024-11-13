#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"
#include <memory>
#include "Game.h"


namespace
{
    // �L�����N�^�[�O���t�B�b�N�̕��ƍ���
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // �A�j���[�V�����̃R�}��
    constexpr int kJumpAnimNum[] = { 0 };
    constexpr int kRunAnimNum[] = { 2,3 };
    constexpr int kAnimFrameCycle = _countof(kRunAnimNum) * kSingleAnimFrame;

    // �L�����N�^�[�̈ړ����x
    constexpr float kSpeed = 2.0f;

	// �n�ʂ̍���
	constexpr float kFieldHeight = 720.0f - 80.0f;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v�̏���
    constexpr float kGravity = 0.4f;    // �d��

}

Player::Player() :
    m_runHandle(-1),
    m_jumpHandle(-1),
    m_animFrame(0),
	m_pos(120.0f, kFieldHeight),
    m_walkFrameCount(0),
    m_isRun(false),
    m_isDirLeft(false),
    m_isJump(false),
    m_isAnimJump(false),
    m_jumpSpeed(0.0f)
{
    m_runHandle = LoadGraph("date/image/Mario.png");
    assert(m_runHandle != -1);

    m_jumpHandle = LoadGraph("date/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    // �O���t�B�b�N�̊J��
    DeleteGraph(m_runHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init()
{
}

void Player::Update()
{
    // �ړ����̂ݕ��s�A�j���[�V�������s��
    if (m_isRun)
    {
        // �A�j���[�V�����̍X�V
        m_animFrame++;
        if (m_animFrame >= kAnimFrameCycle)
        {
            m_animFrame = 0;
        }
    }

    // ���E�ɃL�����N�^�[�𓮂���
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // ���L�[�������Ă��鎞�̏���
        m_pos.x -= kSpeed;   // �������Ɉʒu��ύX
        m_isDirLeft = true;  // �L�����N�^�[�����������Ă���
        m_isRun = true;      // �����Ă���
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // �E�L�[�������Ă��鎞�̏���
        m_pos.x += kSpeed;   // �E�����Ɉʒu��ύX
        m_isDirLeft = false; // �L�����N�^�[�����������Ă���
        m_isRun = true;      // �����Ă���
    }

    // �W�����v����
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        if (!m_isJump)
        {
            m_isJump = true;
            m_isAnimJump = true;
            m_jumpSpeed = kJumpPower;
        }
    }

    if (m_isJump)
    {
        m_pos.y += m_jumpSpeed;

        m_jumpSpeed += kGravity; // ���t���[���������ɉ�������

        if (m_jumpSpeed > 0.0f)
        {
            if (m_pos.y >= kFieldHeight)
            {
                // �W�����v�I������
                m_isJump = false;
                m_isAnimJump = false;
                m_jumpSpeed = 0.0f;

                // �n�ʂɂ߂荞�ނ��Ƃ�����̂Œn�ʂ̍����Ɉʒu��␳����
                m_pos.y >= kFieldHeight;
            }
        }
    }
}

void Player::Draw()
{
    // �v���C���[�̃A�j���[�V�����t���[��
    int animFrame = m_animFrame / kSingleAnimFrame;
    // �v���C���[�̐؂���摜
    int animNo = kRunAnimNum[animFrame];
    // �v���C���[�W�����v�̐؂�����W
    int animJumpNo = kJumpAnimNum[animFrame];

    // �W�����v�����ꍇ
    if (m_isAnimJump)
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            animJumpNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_jumpHandle, true, m_isDirLeft);
    }
    else
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_runHandle, true, m_isDirLeft);
    }
}

float Player::GetLeft() const
{
	return (m_pos.x - kGraphWidth * 0.5f);
}

float Player::GetTop() const
{
	return (m_pos.y - kGraphHeight);
}

float Player::GetRigth() const
{
	return (m_pos.x + kGraphWidth * 0.5f);
}

float Player::GetBottom() const
{
	return  m_pos.y;
}






