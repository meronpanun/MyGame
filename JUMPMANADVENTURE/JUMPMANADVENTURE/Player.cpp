#include "Player.h"
#include "DxLib.h"
#include "BgStage1.h"
#include "Pad.h"
#include "Game.h"
#include "Camera.h"
#include "SceneMain.h"
#include "Enemy.h"
#include <cassert>
#include <stdexcept>

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

    // �X�e�[�W�̉E�[���W
    constexpr int kStageRightEnd = 10200;

    // ���x
    constexpr float kSpeed = 3.0f;
    // ����
   // constexpr float kAccel = 3.0f;
    constexpr float kAccel = 20.0f;

    // �d��
    constexpr float kGravity = 0.5f;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kRunAnimFrame = 4;
    constexpr int kJumpAnimFrame = 12;

    // �v���C���[�̃W�����v�A�j���[�V����
    constexpr int kJumpFrame[] = { 0 };
    // �v���C���[�̕����A�j���[�V����
    constexpr int kWalkFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };

    // �A�j���[�V������1�T�C�N���̃t���[��
    constexpr int kAnimFrameCycle = _countof(kWalkFrame) * kRunAnimFrame;

    // �W�����v��
    constexpr float kJumpAcc = -14.0f;
    // �W�����v�̏���
    constexpr float kJumpPower = -8.0f; 
    // �W�����v�̒���������
    constexpr int kPressShortJumpFrame = 10;	// 10�t���[��
    constexpr int kPressMediumJumpFrame = 30;	// 30�t���[��
    // �W�����v�̍�������
    constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
    constexpr float kInJumpHeight = 0.8f;		// ���W�����v

    // ���G����
    constexpr int kInvincible = 60;

    // �v���C���[�̏���HP
    constexpr int kMaxHp = 3;

    // ���S���o
    constexpr int kDeadStopFrame = 30;      // ���񂾏u�Ԏ~�܂鎞��
    constexpr float kDeadJumpSpeed = -4.0f; // ���񂾂��Ɣ�яオ�鏉��
    constexpr float kDeadPosY = -15.0f;

    // ���X�|�[���x�����ԁi�t���[�����j
    constexpr int kRespawnDelay = 120; // 2�b�i60FPS�̏ꍇ�j
}

Player::Player() :
    m_isJump(false),
    m_isRightMove(false),
    m_isLeftMove(false),
    m_isWalk(false),
    m_isGround(false),
    m_move(kSpeed, 0.0f),
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
    m_isAnimTurn(false),
    m_isGameOver(false),
    m_respawnTimer(0),
    m_isControlDisabled(false),
    m_height(0.0f)
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
    if (m_isControlDisabled)
    {
        // ���얳�����̓A�j���[�V�����̂ݍX�V
        if (m_isWalk)
        {
            // �A�j���[�V�����̍X�V
            m_animFrame++;
            if (m_animFrame >= kAnimFrameCycle)
            {
                m_animFrame = 0;
            }
        }

        // �W�����v�A�j���[�V�����̍X�V
        if (m_isJump)
        {
            m_jumpFrame++;
            if (m_jumpFrame >= _countof(kJumpFrame) * kJumpAnimFrame)
            {
                m_jumpFrame = 0;
            }
        }

        // �v���C���[�̈ʒu���X�V���Ȃ��悤�ɂ���
        return;
    }

    // �����Ă���Ƃ��Ǝ���ł���Ƃ��ŏ�����؂蕪����
    if (m_hp > 0)
    {
        // ���X�|�[���ɒx��������
        if (m_respawnTimer > 0)
        {
            --m_respawnTimer;
            if (m_respawnTimer == 0)
            {
                Respawn();
            }
        }
        else
        {
            UpdateNormal();
        }
    }
    else
    {
        UpdateDead();
    }
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
    return m_pos.x - (kGraphWidth * kScale * 0.5f);
}

float Player::GetTop() const
{
    return m_pos.y - kGraphHeight * kScale;
}

float Player::GetRigth() const
{
    return m_pos.x + (kGraphWidth * kScale * 0.5f);
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
            m_pos.x = chipRect.m_left - kGraphWidth * kScale * 0.5f - 1; // �����̕␳
        }
        else if (m_move.x < 0.0f) // �v���C���[���������Ɉړ����Ă���
        {
            m_pos.x = chipRect.m_right + kGraphWidth * kScale * 0.5f + 1; // �E���̕␳
        }
    }

    // �c�̓����蔻��
    m_pos.y += m_move.y;
    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
    {
        if (m_move.y > 0.0f) // �v���C���[���������Ɉړ����Ă���
        {
            // ���n
            m_pos.y = chipRect.m_top - 1;
            m_move.y = 0.0f;
            m_isJump = false;
            m_isAnimJump = false;
            m_isGround = true;
        }
        else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
        {
            m_pos.y = chipRect.m_bottom + kGraphHeight * kScale + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
            m_move.y *= -1.0f; // ������ւ̉������������ɕϊ�
        }
    }
    else
    {
        // �n�ʂɂ��瓖�����Ă��Ȃ�
        m_isJump = true;
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

void Player::Draw()
{
    // �������Ȕ̕`��
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // �������̐ݒ�
    DrawBox(0, 0, 1280, 100, 0x000000, TRUE);  // �������ȍ�����`��
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // �u�����h���[�h�����ɖ߂�

	// �v���C���[�����G���Ԓ��͓_�ł�����
	if ((m_blinkFrameCount / 2) % 2)
	{
		return;
	}

    // �v���C���[�̃A�j���[�V�����t���[��
    int animFrame = m_animFrame / kRunAnimFrame;
    // �v���C���[�̐؂���摜
    int walkSrcX = kWalkFrame[animFrame] * kGraphWidth;
    int walkSrcY = kGraphHeight;

    //�W�����v����Ƃ��̃A�j���[�V�����t���[��
    int jumpAnimFrame = m_jumpFrame / kJumpAnimFrame;
    //�v���C���[�W�����v�̐؂�����W
    int jumpSrcX = kJumpFrame[jumpAnimFrame] * kGraphHeight;

    // �W�����v�����ꍇ
    if (m_isAnimJump)
    {
        DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kColChipAdjustmentY * kScale),
            jumpSrcX, 0, kGraphWidth, kGraphHeight, kScale, 0,
            m_jumpHandle, true, m_isAnimTurn);
    }
    else
    {
        DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y - kColChipAdjustmentY * kScale),
            walkSrcX, 0, kGraphWidth, kGraphHeight, kScale, 0,
            m_walkHandle, true, m_isAnimTurn);

    }
 

#ifdef DISP_COLLISON
    // �����蔻��̃f�o�b�O�\��
    DrawBox(GetLeft() + m_pCamera->m_drawOffset.x, 
        GetTop(),
        GetRigth() + m_pCamera->m_drawOffset.x, 
        GetBottom(),
        0xff0000, false);
#endif // DISP_COLLISION
}

void Player::OnDamage()
{
    // ���Ƀ_���[�W���󂯂Ă���(���G����)�Ԃ�
    // �ēx�_���[�W���󂯂邱�Ƃ͂Ȃ�
    if (m_blinkFrameCount > 0)
    {
        return;
    }
    // ���G����(�_�ł��鎞��)��ݒ肷��
    m_blinkFrameCount = kInvincible;
    // �_���[�W���󂯂�
    m_hp--;

    // ��ʗh��
    if (m_pCamera)
    {
        // ���x10.0�A30�t���[���̗h��
        m_pCamera->Shake(10.0f, 30); 
    }

	// HP��0�ȉ��ɂȂ����玀�S���o���s��
	if (m_hp <= 0)
	{
        InitDead();
	}
}

void Player::UpdateNormal()
{
    // �v���C���[�����ɗ��������ꍇ
    if ((m_pos.y - kGraphHeight) > kFallMaX)
    {
        // ��ʗh��
        if (m_pCamera)
        {
            // ���x10.0�A30�t���[���̗h��
            m_pCamera->Shake(10.0f, 30);
        }
        StartRespawn();
    }

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
    if (m_pos.x > kStageRightEnd)
    {
        m_pos.x = kStageRightEnd;
    }
    // �v���C���[�̈ʒu���J�����̍��[�𒴂��Ȃ��悤�ɐ���
    if (m_pos.x < m_pCamera->GetLeft())
    {
        m_pos.x = m_pCamera->GetLeft();
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
    else // ���E�ړ������Ă��Ȃ��ꍇ
    {
        m_isRightMove = false;
        m_isLeftMove = false;
        m_move.x = 0;
		m_isWalk = false;
    }

    // �E�_�b�V��
    if (pad & PAD_INPUT_3 && m_isRightMove)
    {
        m_move.x += kAccel;
        m_isAnimTurn = false;
    }
    // ���_�b�V��
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

        // �W�����v�A�j���[�V�����̍X�V
        m_jumpFrame++;
        if (m_jumpFrame >= _countof(kJumpFrame) * kJumpAnimFrame)
        {
            m_jumpFrame = 0;
        }
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
                m_isAnimJump = true;
            }
            else
            {
                m_isJump = false;
            }
        }
        // �}�b�v�`�b�v�Ƃ̓����蔻��
        Rect chipRect;
        CheckHitBgStage1(chipRect);
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
    m_pos.y += m_jumpSpeed;
    m_jumpSpeed += kGravity;

    // �v���C���[����ʊO�Ɋ��S�ɗ��������ǂ����𔻒�
    if (m_pos.y > Game::kScreenHeight + kGraphHeight * kScale)
    {
        m_isGameOver = true; // �Q�[���I�[�o�[���o���J�n����t���O��ݒ�
    }
}

bool Player::IsGameOver() const
{
    return m_isGameOver;
}

void Player::StartRespawn()
{
    m_respawnTimer = kRespawnDelay;
}

void Player::Respawn()
{
    // �v���C���[�̈ʒu�����Z�b�g
    m_pos.x = kRestartPosX;
    m_pos.y = kRestartPosY;

    // �J�������v���C���[���l���Z�b�g
    m_pCamera->m_pos.SetPos(m_pos.x, m_pos.y);

    // hp�����炷
    m_hp--;

    // HP��0�ȉ��ɂȂ����玀�S���o���s��
    if (m_hp <= 0)
    {
        m_isGameOver = true; // �Q�[���I�[�o�[���o���J�n����t���O��ݒ�
        return;
    }
}

// �v���C���[�̑���𖳌�������
void Player::DisableControl()
{
    m_isControlDisabled = true;
}

// �v���C���[�̑��삪�������ǂ����𔻒肷��
bool Player::IsControlDisabled() const
{
     return m_isControlDisabled;
}

// �v���C���[��X���W��ݒ肷��
void Player::SetPosX(float x)
{
    m_pos.x = x;
}

// �v���C���[���n�ʂɂ��邩�ǂ����𔻒肷��
bool Player::IsOnGround() const
{
    return m_isGround;
}

// �v���C���[��n�ʂ̍����܂ł�����藎�Ƃ�
void Player::FallToGround(float groundHeight)
{
    if (m_pos.y < groundHeight - m_height) 
    {
        m_pos.y += 3.0f; // �������x�𒲐�
        if (m_pos.y > groundHeight - m_height) 
        {
            m_pos.y = groundHeight - m_height;
        }
    }
}

// �v���C���[�������Ă��邩�ǂ�����ݒ肷��
void Player::SetIsWalking(bool isWalking)
{
    m_isWalk = isWalking;
}

void Player::UpdateAnimation()
{
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
}

//  �v���C���[�����S��ԂɂȂ����Ƃ��̏�����
void Player::InitDead()
{
	m_jumpSpeed = kDeadPosY;
	m_deadFrameCount = 0;
	m_blinkFrameCount = 0;
}
