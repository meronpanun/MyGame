#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Pad.h"
#include <memory>

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // �v���C���[�O���t�B�b�N�̕��ƍ���
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �L�����N�^�[�T�C�Y
    constexpr int kWidth = 20;
    constexpr int kHeight = 20;

    // ���a�̓����蔻��
    constexpr int kRadius = 9;

    // �v���C���[�̈ړ����x
    constexpr float kSpeed = 2.0f;

    // �v���C���[�̉����x
    constexpr float kAccel = 2.0f;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kWalkAnimFrame = 10;

    // �A�j���[�V�����̃R�}��
    constexpr int kWalkAnimNo[] = { 2,3 };
    constexpr int kWalkAnimNum = _countof(kWalkAnimNo) * kWalkAnimFrame;

    // �v���C���[�̃W�����v�A�j���[�V����
    constexpr int kJumpAnim[] = { 0 };

    // �W�����v�A�j���[�V������1�R�}�̃t���[����
    constexpr int kJumpAnimFrameNum = 12;

    // �n�ʂ̍���
    constexpr float kFieldHeight = 720.0f - 78.0f;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v��
    constexpr float kGravity = 0.4f; // �d��

}

Player::Player() :
    m_isJump(false),
    m_isRight(false),
    m_isLeft(false),
    m_moveX(0.0f),
    m_moveY(0.0f),
    m_pos(720.0f, kFieldHeight),
    /*m_posX(40.0f),
    m_posY(800.0f),*/
    m_dir(kNutral),
    m_animFrame(0),
    m_animCount(0),
    m_isAnimJump(false),
    m_isCommand(false),
    m_isAnimTrun(false)
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
    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    bool isMove = false;

    Pad::Update();

    m_dir = kNutral;

    m_moveX = 0.0f;

    if (!m_isCommand)
    {
        if (pad & PAD_INPUT_LEFT)
        {
            m_moveX -= kSpeed;
            m_isLeft = true;
            m_isAnimTrun = true;
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
            m_isAnimTrun = false;
            m_dir = kFall;
        }
        else
        {
            m_isRight = false;
        }

        // �_�b�V������
        if (pad & PAD_INPUT_3 && m_isLeft)
        {
            m_moveX -= kAccel;
            m_dir = kWalk;
            m_isAnimTrun = true;
        }

        if (pad & PAD_INPUT_3 && m_isRight)
        {
            m_moveX += kAccel;
            m_dir = kWalk;
            m_isAnimTrun = false;
        }
    }

    // �A�j���[�V��������
    m_animFrame++;
    if (m_animFrame >= kWalkAnimNum) m_animFrame = 0;

    // �W�����v����
    //if (m_isJump)
    //{
    //    // ���t���[���������Ƀv���X
    //    m_moveY += kGravity;

    //    m_posX += m_moveX;
    //}
}

void Player::Draw()
{
    //
    int animIjndex = m_animFrame / kWalkAnimFrame;

    //int srcX = kWalkAnimNo[animIjndex] * kGraphWidth;
    //int srcY = kGraphHeight * m_dir;

    int animNo = kWalkAnimNo[animIjndex];

    DrawRectGraph(m_pos.x - kGraphWidth / 2, m_pos.y - kGraphHeight,
        animNo * kGraphWidth, m_dir * kGraphHeight,
        kWidth, kHeight, m_runHandle, true);

#ifdef DISP_COLLISON
    DrawBox(GetLeft(), GetTop(),
        GetRight(), GetBottom(),
        GetColor(0, 0, 255), false);
#endif // DISP_COLLISON
}

float Player::GetRadius()
{
    return kRadius;
}

float Player::GetLeft()
{
    return m_pos.x - kGraphWidth / 2;
}

float Player::GetRight()
{
    return m_pos.x + kGraphWidth / 2;
}

float Player::GetTop()
{
    return m_pos.y - kGraphWidth / 2;
}

float Player::GetBottom()
{
    return m_pos.y;
}




