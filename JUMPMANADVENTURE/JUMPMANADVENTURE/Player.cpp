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
    // �v���C���[�̕`��T�C�Y
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;
    
    // �v���C���[�̃��X�|�[���ʒu
    constexpr float kRestartPosX = 150.0f;
    constexpr float kRestartPosY = 610.0f;

    // �g�嗦
    constexpr float kScale = 2.0f;

    // �����蔻��̔��a
    constexpr int kRadius = 9;

    // �}�b�v�`�b�v�Ƃ̓����蔻��̒���
    constexpr int kColChipAdjustmentX = 30;
    constexpr int kColChipAdjustmentY = 15;

    // ��̏�� 
    constexpr int kFallMaX = 920;

    // �X�e�[�W�̍��E�[���W
    constexpr int kStageLeftEnd = 70;
    constexpr int kStageRightEnd = 6500;

    // ���x
    constexpr float kSpeed = 3.0f;
    // ����
    constexpr float kAccel = 6.0f;

    // �d��
    constexpr float kGravity = 0.5f;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kRunAnimFrame = 4;
    constexpr int kJumpAnimFrame = 12;

    // �L�����N�^�[�̃W�����v�A�j���[�V����
    constexpr int kJumpFrame[] = { 0 };
    // �L�����N�^�[�̕����A�j���[�V����
    constexpr int kWalkFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
    // �A�j���[�V������1�T�C�N���̃t���[��
    constexpr int kAnimFrameCycle = _countof(kWalkFrame) * kRunAnimFrame;

    // �W�����v��
    constexpr float kJumpAcc = -12.5f;
    // �W�����v�̏���
    constexpr float kJumpPower = -8.0f; 
    // �W�����v�̒���������
    constexpr int kPressShortJumpFrame = 10;	// 10�t���[��
    constexpr int kPressMediumJumpFrame = 30;	// 30�t���[��
    // �W�����v�̍�������
    constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
    constexpr float kInJumpHeight = 0.8f;		// ���W�����v

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
    m_isRightMove(false),
    m_isLeftMove(false),
    m_isWalk(false),
    m_isGround(false),
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
    // �O���t�B�b�N�̓ǂݍ���
    m_walkHandle = LoadGraph("data/image/Run.png");
    assert(m_walkHandle != -1);
    m_jumpHandle = LoadGraph("data/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    // �O���t�B�b�N�̊J��
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
    if ((m_pos.y - kGraphHeight) > kFallMaX)
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
    int animFrame = m_animFrame / kRunAnimFrame;
    // �v���C���[�̐؂���摜
    int walkSrcX = kWalkFrame[animFrame] * kGraphWidth;
    int walkSrcY = kGraphHeight;

    //�W�����v����Ƃ��̃A�j���t���[��
    int jumpAnimFrame = m_animFrame / kJumpAnimFrame;

    //�v���C���[�W�����v�̐؂�����W
    int JsrcX = kJumpFrame[jumpAnimFrame] * kGraphHeight;
    int JsrcY = 0;

    // �W�����v�����ꍇ
    //if (m_isAnimJump)
    //{

    //    DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth + kColChipAdjustmentX + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight - kColChipAdjustmentY),
    //        JsrcX, JsrcY, kGraphWidth, kGraphHeight, kScale, 0,
    //        m_jumpHandle, true, m_isAnimTurn);
    //}
    //else
    //{
    //    DrawRectRotaGraph(static_cast<int>( m_pos.x - kGraphWidth + kColChipAdjustmentX + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight - kColChipAdjustmentY),
    //        walkSrcX, 0, kGraphWidth, kGraphHeight, kScale, 0,
    //        m_walkHandle, true, m_isAnimTurn);

    //}
    
    DrawRectRotaGraph(static_cast<int>(m_pos.x - kGraphWidth + kColChipAdjustmentX + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kGraphHeight + kColChipAdjustmentY),
        walkSrcX, 0, kGraphWidth, kGraphHeight, 1.0f ,0, 
        m_walkHandle, true, m_isAnimTurn);

   

#ifdef DISP_COLLISON
    // �����蔻��̃f�o�b�O�\��
    //DrawBox(GetLeft() + m_pCamera->m_drawOffset.x, 
    //    GetTop(),
    //    GetRigth() + m_pCamera->m_drawOffset.x, 
    //    GetBottom(),
    //    GetColor(0, 0, 255), false);
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

void Player::JumpOnEnemy()
{
    m_move.y = kJumpAcc * 0.5f; // ����Y�������ɃW�����v
    m_isJump = true;
    m_isGround = false;
}

float Player::GetRadius() const
{
    return kRadius;
}

float Player::GetLeft() const
{
    return m_pos.x - kGraphWidth * static_cast<float>(0.5f);
}

float Player::GetTop() const
{
    return m_pos.y - kGraphHeight;
}

float Player::GetRigth() const
{
    return m_pos.x + kGraphWidth * static_cast<float>(0.5f);
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
            m_pos.x = chipRect.m_left - kGraphWidth * static_cast<float>(0.5f) - 1; // �����̕␳
        }
        else if (m_move.x < 0.0f) // �v���C���[���������Ɉړ����Ă���
        {
            m_pos.x = chipRect.m_right + kGraphWidth * static_cast<float>(0.5f) + 1; // �E���̕␳
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
            m_isGround = true;
        }
        else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
        {
            m_pos.y = chipRect.m_bottom + kGraphHeight + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
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

float Player::GetMoveY() const
{
    return m_move.y;
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

    // �E�ړ�
    if (pad & PAD_INPUT_RIGHT)
    {
        m_isRightMove = true;
        m_isLeftMove = false;
        m_move.x = kSpeed;
        m_isAnimTurn = false;
        m_isWalk = true;
    }
    // ���ړ�
    else if (pad & PAD_INPUT_LEFT)
    {
        m_isRightMove = false;
        m_isLeftMove = true;
        m_move.x = -kSpeed;
        m_isAnimTurn = true;
        m_isWalk = true;
    }
    else
    {
        m_isLeftMove = false;
        m_isRightMove = false;
        m_move.x = 0;
        m_isWalk = false;
    }

    // �_�b�V������
    if (pad & PAD_INPUT_3 && m_isRightMove)
    {
        m_move.x += kAccel;
        m_isAnimTurn = false;
    }
    if (pad & PAD_INPUT_3 && m_isLeftMove)
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
        if (m_isGround)
        {
            m_jumpFrame = 0;
            m_isJump = false;
            // �W�����v����
            if (pad & PAD_INPUT_1)
            {
                m_isJump = true;
                m_isGround = false;
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
        }

        // ���̓����蔻��
        m_pos.x += m_move.x;
        Rect chipRect;
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.x > 0.0f)
            {
                m_pos.x = chipRect.m_left - kGraphWidth * static_cast<float>(0.5f) - 1;
            }
            else if (m_move.x < 0.0f)
            {
                m_pos.x = chipRect.m_right + kGraphWidth * static_cast<float>(0.5f) + 1;
            }
        }

        // �c�̓����蔻��
        m_pos.y += m_move.y;
        if (m_pBgStage1->IsCollision(GetRect(), chipRect))
        {
            if (m_move.y > 0.0f) // �v���C���[���������Ɉړ����Ă���
            {
                // �n�ʂɗ����Ă��鉽�����Ȃ�
                m_pos.y = chipRect.m_top - 1;
                m_isJump = false;
                m_isAnimJump = false;
                m_isGround = true;;
            }
            else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
            {
                m_pos.y = chipRect.m_bottom + kGraphHeight + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
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
