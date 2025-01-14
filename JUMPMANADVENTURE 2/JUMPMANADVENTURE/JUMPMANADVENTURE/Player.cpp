#include "Player.h"
#include "DxLib.h"
#include "BgStage1.h"
#include "Pad.h"
#include "Game.h"
#include "Camera.h"
#include "SceneMain.h"
#include <cassert>

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{
    // �L�����N�^�[�T�C�Y
    constexpr int kWidth = 30;
    constexpr int kHeight = 30;

    // �L�����N�^�[�̕`��T�C�Y
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;
    
    // �v���C���[�̃��X�|�[���ʒu
    constexpr float kRestartPosX = 150.0f;
    constexpr float kRestartPosY = 610.0f;

    // �����蔻��̔��a
    constexpr int kRadius = 9;

    // ��̏�� 
    constexpr int kFallMaX = 920;

    // �X�e�[�W�̍��E�[���W
    constexpr int kStageLeftEnd = 40;
    constexpr int kStageRightEnd = 5100;

    // ���x
    constexpr float kSpeed = 3.0f;
    // ����
    constexpr float kAccel = 4.0f;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // �d��
    constexpr float kGravity = 0.5f;
    // �W�����v��
    constexpr float kJumpAcc = -10.0f;

    // �L�����N�^�[�̃W�����v�A�j���[�V����
    constexpr int kJumpFrame[] = { 0 };
    // �L�����N�^�[�̕����A�j���[�V����
    constexpr int kWalkFrame[] = { 2,3 };
    // �A�j���[�V������1�T�C�N���̃t���[����
    constexpr int kAnimFrameCycle = _countof(kWalkFrame) * kSingleAnimFrame;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v�̏���
    // �W�����v�̒���������
    constexpr int kPressShortJumpFrame = 10;	// 10�t���[��
    constexpr int kPressMediumJumpFrame = 30;	// 30�t���[��
    // �W�����v�̍�������
    constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
    constexpr float kInJumpHeight = 0.8f;		// ���W�����v
    constexpr float kBigJumpHeight = 1.0f;		// ��W�����v

    // ���G����
    constexpr int kInvincible = 30;

    // �����̎c�@��
    constexpr int kLife = 3;

    // �v���C���[�̏���HP
    constexpr int kMaxHp = 3;

    // ���S���o
    constexpr int kDeadStopFrame = 30;      // ���񂾏u�Ԏ~�܂鎞��
    constexpr float kDeadJumpSpeed = -4.0f; // ���񂾂��Ɣ�яオ�鏉��
}

Player::Player() :
    m_isJump(false),
    m_isRight(false),
    m_isLeft(false),
    m_isWalk(false),
    m_move(0.0f, 0.0f),
    m_pos(150.0f, 610.0f),
    m_animFrame(0),
    m_jumpFrame(0),
    m_jumpCount(0),
    m_jumpSpeed(0.0f),
    m_animCount(0),
    m_blinkFrameCount(0),
    m_hp(kMaxHp),
    m_deadFrameCount(0),
    m_isAnimJump(false),
    m_isAnimTurn(false)
{
    m_walkHandle = LoadGraph("data/image/Mario.png");
    assert(m_walkHandle != -1);
    m_jumpHandle = LoadGraph("data/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    DeleteGraph(m_walkHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init(Camera* pCamera)
{
    m_pCamera = pCamera;
    m_pCamera->m_pos.SetPos(m_pos.x, m_pos.y);
}

void Player::Update()
{
    // �v���C���[�����ɗ��������ꍇ
    if ((m_pos.y - kHeight) > kFallMaX)
    {
        m_pos.x = kRestartPosX;
        m_pos.y = kRestartPosY;

        m_pCamera->m_pos.SetPos(m_pos.x, m_pos.y);

        // hp�����炷
        m_hp--;
    }

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
    // �v���C���[�̃A�j���[�V�����t���[��
    int animFrame = m_animFrame / kSingleAnimFrame;
    // �v���C���[�̐؂���摜
    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
    int walkSrcX = kWalkFrame[animFrame];
    int walkSrcY = kGraphHeight;

    // �W�����v�����ꍇ
    if (m_isAnimJump)
    {

        DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth + 32 + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight + 3),
            kGraphWidth, 0, kGraphWidth, kGraphHeight, 2.0f, 0,
            m_jumpHandle, true, m_isAnimTurn);
    }
    else
    {
        DrawRectRotaGraph(static_cast<int>( m_pos.x  - kGraphWidth + 32 + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight + 3),
            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight, 2.0f, 0,
            m_walkHandle, true, m_isAnimTurn);

    }
    
#ifdef DISP_COLLISON
    // �����蔻��̃f�o�b�O�\��
 /*   DrawBox(GetLeft(), GetTop(),
        GetRigth(), GetBottom(),
        GetColor(0, 0, 255), false);*/
#endif // DISP_COLLISION
}

void Player::OnDamage()
{
    // ���Ƀ_���[�W���󂯂Ă���(���G����)�Ԃ�
    // �ēx�_���[�W���󂯂邱�Ƃ͂Ȃ�
    if (m_invincibleCount > 0)
    {
        return;
    }
    // ���G����(�_�ł��鎞��)��ݒ肷��
    m_invincibleCount = kInvincible;
    // �_���[�W���󂯂�
    m_hp--;
    printfDx("Damage ");
}

float Player::GetRadius() const
{
    return kRadius;
}

float Player::GetLeft() const
{
    return m_pos.x - kWidth * static_cast<float>(0.5f);
}

float Player::GetTop() const
{
    return m_pos.y - kHeight;
}

float Player::GetRigth() const
{
    return m_pos.x + kWidth * static_cast<float>(0.5f);
}

float Player::GetBottom() const
{
    return m_pos.y;
}

void Player::CheckHitBgStage1(Rect chipRect)
{
    // ���̓����蔻��
    m_pos.x += m_move.x;
    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
    {
        if (m_move.x > 0.0f) // �v���C���[���E�����Ɉړ����Ă���
        {
            m_pos.x = chipRect.m_left - kWidth * static_cast<float>(0.5f) - 1; // �����̕␳
        }
        else if (m_move.x < 0.0f) // �v���C���[���������Ɉړ����Ă���
        {
            m_pos.x = chipRect.m_right + kWidth * static_cast<float>(0.5f) + 1; // �E���̕␳
        }
    }

    // �c�̓����蔻��
    m_pos.y += m_move.y;
    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
    {
        if (m_move.y > 0.0f) // �v���C���[���������Ɉړ����Ă���
        {
            // ���n
            m_pos.y -= m_move.y;
            m_move.y = 0.0f;
            m_isJump = false;
            m_isAnimJump = false;
        }
        else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
        {
            m_pos.y = chipRect.m_bottom + kHeight + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
            m_move.y *= -1.0f; // ������ւ̉������������ɕϊ�
        }
    }
}

void Player::AddMoveY(float DisY)
{
    m_pos.y += DisY;
}

void Player::OnCollideY()
{
    m_move.y = 0;
}

Rect Player::GetRect() const
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

void Player::UpdateNormal()
{
    // ���G���Ԃ̍X�V
    m_blinkFrameCount--;
    if (m_blinkFrameCount < 0)
    {
        m_blinkFrameCount = 0;
    }

    // �ړ����̂ݕ��s�A�j���[�V�������s��
    if (m_isWalk)
    {
        // �A�j���[�V�����̍X�V
        m_animFrame++;
        if (m_animFrame >= kAnimFrameCycle)
        {
            m_animFrame = 0;
        }
    }

    // �v���C���[����ʒ[����o�Ă����Ȃ�
    if (m_pos.x < kStageLeftEnd)
    {
        m_pos.x = kStageLeftEnd;
    }
    if (m_pos.x > kStageRightEnd)
    {
        m_pos.x = kStageRightEnd;
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

    // �W�����v��
    if (m_isJump)
    {
        // �W�����v������
        UpdateJump();

        // �����x�ɏd�͂𑫂�
        m_move.y += kGravity;

        // �}�b�v�`�b�v�Ƃ̓����蔻��
        Rect chipRect;
        CheckHitBgStage1(chipRect);
    }
    else // �n�ʂɂ��Ă���ꍇ
    {
        // �W�����v����
        if (pad & PAD_INPUT_1 && m_isJump == false)
        {
            m_isJump = true;
            m_jumpCount++;
        }
        else
        {
            m_jumpCount = 0;
        }

        if (m_jumpCount == 1 && m_isJump)
        {
            m_move.y = kJumpAcc;
            m_isAnimJump = false;
        }
        else
        {
            m_isJump = false;
        }

        m_pos.x += m_move.x;
        Rect chipRect;
        // ���̓����蔻��
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.x > 0.0f)
            {
                m_pos.x = chipRect.m_left - kWidth * static_cast<float>(0.5f) - 1;
            }
            else if (m_move.x < 0.0f)
            {
                m_pos.x = chipRect.m_right + kWidth * static_cast<float>(0.5f) + 1;
            }
        }

        m_pos.y += m_move.y;
        // �c�̓����蔻��
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.y > 0.0f) // �v���C���[���㉺�����Ɉړ����Ă���
            {
                // �n�ʂɗ����Ă��鉽�����Ȃ�
                m_pos.y = chipRect.m_top - 1;
                m_isJump = false;
                m_isAnimJump = false;
            }
            else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
            {
                m_pos.y = chipRect.m_bottom + kHeight + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
                m_move.y *= -1.0f; // ������ւ̉������������ɕϊ�
            }
        }
        else
        {
            // �n�ʂɂ��瓖�����Ă��Ȃ�
            m_isJump = true;
        }
    }
}

/// <summary>
/// �v���C���[��HP��0�ȉ��ɂȂ����ꍇ
/// </summary>
void Player::UpdateDead()
{
    // ���S���u�~�܂�
    m_deadFrameCount++;
    if (m_deadFrameCount < kDeadStopFrame)
    {
        return;
    }

    // ��ʊO�ɗ����Ă������o
 /*   m_pos.y += m_jumpSpeed;
    m_jumpSpeed += kGravity;*/
}
