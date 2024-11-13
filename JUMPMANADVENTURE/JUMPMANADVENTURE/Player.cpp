#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"
#include <memory>
#include "Game.h"

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // �L�����N�^�[�O���t�B�b�N�̕��ƍ���
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �A�j���[�V�����̃R�}��
    constexpr int kJumpAnimNum = 1;
    constexpr int kRunAnimNum = 2;
    
    // �L�����N�^�[�̈ړ����x
    constexpr float kSpeed = 2.0f;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kSingleAnimFrame = 10;

    // �����A�j���[�V�����Ŏg�p���鏇��
   // constexpr int kWalkAnimNo[] = { 1,2, };
   // constexpr int kWalkAnimNum = _countof(kWalkAnimNo);
   // constexpr int kWalkAnimFrame = 10;

	// �n�ʂ̍���
	constexpr float kFieldHeight = 720.0f - 28.0f;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v�̏���
    constexpr float kGravity = 0.4f;    // �d��

}

Player::Player() :
    m_runHandle(-1),
    m_jumpHandle(-1),
    m_animFrame(0),
    //m_dir(kDirDown),
	m_pos(720.0f, kFieldHeight),
    m_walkFrameCount(0),
    m_isRun(false),
    m_isDirLeft(false),
    m_isJump(false),
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

}





void Player::Draw()
{
    int animNo = m_animFrame / kSingleAnimFrame;

    int useHandle = m_runHandle;
    if (m_isRun)
    {
        useHandle = m_jumpHandle;
    }
//	int animIndex = m_walkFrameCount / kWalkAnimFrame;
//	int animNo = kWalkAnimNo[animIndex];

; DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
    animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
    useHandle,true, m_isDirLeft);

#ifdef DISP_COLLISON
    DrawBox(GetLeft(), GetTop(),
        GetRigth(), GetBottom(),
        GetColor(0, 0, 255), false);
#endif // DISP_COLLISON
}

float Player::GetLeft() const
{
	return (m_pos.x - kGraphWidth / 2);
}

float Player::GetTop() const
{
	return (m_pos.y - kGraphHeight);
}

float Player::GetRigth() const
{
	return (m_pos.x + kGraphWidth / 2);
}

float Player::GetBottom() const
{
	return  m_pos.y;
}

void Player::UpdateNormal()
{
    // �A�j���[�V�����̍X�V
    m_animFrame++;

    int totalFrame = kJumpAnimNum * kSingleAnimFrame;
    if (m_isRun)
    {
        totalFrame = kJumpAnimNum * kSingleAnimFrame;
    }
    // �A�j���[�V�����̍��v�t���[�����𒴂�����ŏ��ɖ߂�
    if (m_animFrame >= totalFrame)
    {
        m_animFrame = 0;
    }

    // ���E�ɃL�����N�^�[�𓮂���
    m_isRun = false;
    if (Pad::IsPress(PAD_INPUT_LEFT))
    {
        // ���L�[�������Ă��鎞�̏���
        m_pos.x -= kSpeed;   // �������Ɉʒu��ύX
        m_isDirLeft = true;  // �L�����N�^�[�����������Ă���
        m_isRun = true;
    }
    if (Pad::IsPress(PAD_INPUT_RIGHT))
    {
        // �E�L�[�������Ă��鎞�̏���
        m_pos.x += kSpeed;   // �E�����Ɉʒu��ύX
        m_isDirLeft = false; // �L�����N�^�[�����������Ă���
        m_isRun = true;
    }

    // �W�����v����
    if (Pad::IsTrigger(PAD_INPUT_1))
    {
        if (!m_isJump)
        {
            m_isJump = true;
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
                m_jumpSpeed = 0.0f;

                // �n�ʂɂ߂荞�ނ��Ƃ�����̂Œn�ʂ̍����Ɉʒu��␳����
                m_pos.y >= kFieldHeight;
            }
        }
    }
}




