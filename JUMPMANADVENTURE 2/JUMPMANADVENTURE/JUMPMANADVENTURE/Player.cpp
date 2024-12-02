#include "Player.h"
#include "DxLib.h"
#include "Map.h"
#include "Pad.h"
#include "Game.h"
#include <memory>
#include <cassert>

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

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

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // �d��
    constexpr float kGravity = 0.5f;
    // �W�����v��
    constexpr float kJumpAcc = -10.0f;

    constexpr int kUseJumpFrame[] = { 0 };
    constexpr int kUseFrame[] = { 2,3 };
    constexpr int kAnimFrameCycle = _countof(kUseFrame) * kSingleAnimFrame;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v�̏���
    // �W�����v�̒���������
    constexpr int kPressShortJumpFrame = 10;	// 10�t���[��
    constexpr int kPressMediumJumpFrame = 30;	// 30�t���[��
    // �W�����v�̍�������
    constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
    constexpr float kInJumpHeight = 0.8f;		// ���W�����v
    constexpr float kBigJumpHeight = 1.0f;		// ��W�����v
}

Player::Player() :
    m_isJump(false),
    m_isRight(false),
    m_isLeft(false),
    m_isWalk(false),
    m_isGround(false),
    m_move(0.0f, 0.0f),
    m_pos(120.0f, 415.0f),
    m_animFrame(0),
    m_jumpFrame(0),
    m_jumpCount(0),
    m_animCount(0),
    m_isAnimJump(false),
    m_isAnimTurn(false)
{
    m_walkHandle = LoadGraph("date/image/Mario.png");
    assert(m_walkHandle != -1);
    m_jumpHandle = LoadGraph("date/image/Jump.png");
}

Player::~Player()
{
    DeleteGraph(m_walkHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init()
{
    // �W�����v�t���O
    m_isGround = false;
}

void Player::Update()
{

    // �ړ����̂ݕ��s�A�j���[�V�������s��
    if (m_isWalk)
    {
        // if (m_animation == Anim::kWalk)
        {
            // �A�j���[�V�����̍X�V
            m_animFrame++;
            if (m_animFrame >= kAnimFrameCycle)
            {
                m_animFrame = 0;
            }
        }
    }
    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    bool isMove = false;

    Pad::Update();

    m_move.x = 0.0f;

    // ���E�ړ�
    m_isWalk = false;
    if (pad & PAD_INPUT_LEFT)
    {
        m_move.x -= kSpeed;
        m_isLeft = true;
        m_isAnimTurn = true;
        m_isWalk = true;
    }
    else
    {
        m_isLeft = false;
    }

    if (pad & PAD_INPUT_RIGHT)
    {
        m_move.x += kSpeed;
        m_isRight = true;
        m_isAnimTurn = false;
        m_isWalk = true;
    }
    else
    {
        m_isRight = false;
    }

    // �_�b�V������
    if (pad & PAD_INPUT_3 && m_isRight)
    {
        m_move.x += kAccel;
        m_isAnimTurn = false;
    }
    if (pad & PAD_INPUT_3 && m_isLeft)
    {
        m_move.x -= kAccel;
        m_isAnimTurn = true;
    }



    // �W�����v����
    if (m_isJump) // �W�����v��
    {
        m_move.y += kGravity;

        Rect chipRect;
        CheckHitMap(chipRect);
    }
    else // �n�ʂɂ��Ă���ꍇ
    {
        if (pad & PAD_INPUT_1 && m_isJump == false)
        {
            m_isJump = true;
            m_jumpCount++;
        }
        else m_jumpCount = 0;

        if (m_jumpCount == 1 && m_isJump)
        {
            m_move.y = kJumpAcc;
            m_isAnimJump = false;
        }
        else m_isJump = false;

        m_pos.x += m_move.x;
        Rect chipRect;
        // ��
        if (m_pMap->IsCollision(getRect(), chipRect))
        {
            if (m_move.x > 0.0f)
            {
                m_pos.x = chipRect.m_left - kWidth * 0.5 - 1;
            }
            else if (m_move.x < 0.0f)
            {
                m_pos.x = chipRect.m_right + kWidth * 0.5 + 1;
            }
        }

        m_pos.y += m_move.y;
        // �c
        if (m_pMap->IsCollision(getRect(), chipRect))
        {
            // �㉺�ǂ��炩�������������f�o�b�N�\��
            if (m_move.y > 0.0f) // �v���C���[���㉺�����Ɉړ����Ă���
            {
                // �n�ʂɗ����Ă��鉽�����Ȃ�
                m_pos.y = chipRect.m_top - 1;
                m_isJump = false;
                m_isAnimJump = false;
            }
            else if (m_move.y < 0.0f)
            {
                m_pos.y = chipRect.m_bottom + kHeight + 1;
                m_move.y *= -1.0f;
            }
        }
        else
        {
            m_isJump = true;
        }
    }
    printfDx("m_pos:(%d,%d)\n",
        (int)m_pos.x,
        (int)m_pos.y);
}

void Player::Draw()
{
    // �v���C���[�̃A�j���[�V�����t���[��
    int animFrame = m_animFrame / kSingleAnimFrame;
    // �v���C���[�̐؂���摜
    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
    int walkSrcX = kUseFrame[animFrame];
    int walkSrcY = kGraphHeight;


    // �W�����v�����ꍇ
    if (m_isAnimJump)
    {

        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_jumpHandle, true, m_isAnimTurn);
    }
    else
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_walkHandle, true, m_isAnimTurn);

    }
#ifdef DISP_COLLISON
    // �����蔻��̃f�o�b�O�\��
    DrawBox(GetLeft(), GetTop(),
        GetRigth(), GetBottom(),
        GetColor(0, 0, 255), false);
#endif // DISP_COLLISION
}

float Player::GetLeft() const
{
    return m_pos.x - kWidth * 0.5;
}

float Player::GetTop() const
{
    return m_pos.y - kHeight;
}

float Player::GetRigth() const
{
    return m_pos.x + kWidth * 0.5;
}

float Player::GetBottom() const
{
    return m_pos.y;
}

void Player::CheckHitMap(Rect chipRect)
{
    // ���̓����蔻��
    m_pos.x += m_move.x;
    if (m_pMap->IsCollision(getRect(), chipRect))
    {
        if (m_move.x > 0.0f)
        {
            m_pos.x = chipRect.m_left - kWidth * 0.5 - 1;
        }
        else if (m_move.x < 0.0f)
        {
            m_pos.x = chipRect.m_right + kWidth * 0.5 + 1;
        }
    }

    // �c�̓����蔻��
    m_pos.y += m_move.y;
    if (m_pMap->IsCollision(getRect(), chipRect))
    {
        if (m_move.y > 0.0f)
        {
            m_pos.y -= m_move.y;
            m_move.y = 0.0f;
            m_isJump = false;
            m_isAnimJump = false;
        }
        else if (m_move.y < 0.0f)
        {
            m_pos.y = chipRect.m_bottom + kHeight + 1;
            m_move.y *= 0.0f;
        }
    }
}

Rect Player::getRect()
{
    // �v���C���[�̋�`�����蔻����
    Rect rect;
    rect.m_top = GetTop();
    rect.m_bottom = GetBottom();
    rect.m_left = GetLeft();
    rect.m_right = GetRigth();
    return rect;
}

void Player::UpdateJump()
{
    m_jumpFrame++;
    // �W�����v����
    if (Pad::IsRelase(PAD_INPUT_1))
    {
        //�@�W�����v�̍��������߂�
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
