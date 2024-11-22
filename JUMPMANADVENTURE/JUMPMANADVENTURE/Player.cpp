#include "Player.h"
#include "DxLib.h"
#include "pad.h"
#include "Game.h"
#include "BgStage1.h"
#include "SceneStage1.h"
#include <cassert>

namespace
{
    // �L�����N�^�[�O���t�B�b�N�̕��ƍ���
    constexpr int kScale = 0.3f;
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �����蔻��T�C�Y
    constexpr int kColX = static_cast<int>(kGraphWidth);
    constexpr int kColY = static_cast<int>(kGraphHeight);

    // �����蔻��T�C�Y�̒���
    constexpr int kColAdjustment = 0.5f;

    // �}�b�v�`�b�v�Ƃ̓����蔻�蒲��
    constexpr int kColChipadjustment = 15;

    // �A�j���[�V����1�R�}�̃t���[����
    constexpr int kSingleAnimFrame = 10;
    constexpr int kJumpAnimFrame = 12;

    // �A�j���[�V�����̃R�}��
   // constexpr int kJumpAnimNum[] = { 0 };
    constexpr int kWalkAnimNum[] = { 2,3 };
    constexpr int kAnimFrameCycle = _countof(kWalkAnimNum) * kSingleAnimFrame;

    // �L�����N�^�[�̈ړ����x
    constexpr float kSpeed = 2.0f;

	// �n�ʂ̍���
	constexpr float kFieldHeight = 720.0f - 80.0f;

    // �W�����v����
    constexpr float kJumpPower = -8.0f; // �W�����v�̏���
    constexpr float kGravity = 0.4f;    // �d��
    // �W�����v�̒���������
    constexpr int kPressShortJumpFrame = 10;	// 10�t���[��
    constexpr int kPressMediumJumpFrame = 30;	// 30�t���[��
    // �W�����v�̍�������
    constexpr float kLittleJumpHeight = 0.5f;	// ���W�����v
    constexpr float kInJumpHeight = 0.8f;		// ���W�����v
    constexpr float kBigJumpHeight = 1.0f;		// ��W�����v

    // �}�b�v�`�b�v�̃T�C�Y
    constexpr int kMapWidth = 16;
    constexpr int kMapHeight = 16;
}

Player::Player() :
    m_pBg(nullptr),
    m_pMain(nullptr),
    m_move(0.0f,0.0f),
    m_isDirLeft(false),
    m_isGround(false),
    m_isJump(false),
    m_jumpFrame(0),
    m_keyState(0),
    m_pressTime(0),
    m_nowPressTime(0),
    m_walkHandle(0),
    m_jumpHandle(0),
    m_animFrame(0),
	//m_pos(120.0f, kFieldHeight),
    m_walkFrameCount(0),
    m_isWalk(false),
    m_isAnimJump(false),
    m_jumpSpeed(0.0f),
    m_animation(Anim::kWalk),
    m_walkAnimFrame(0)
{
    m_walkHandle = LoadGraph("date/image/Mario.png");
    assert(m_walkHandle != -1);

    m_jumpHandle = LoadGraph("date/image/Jump.png");
    assert(m_jumpHandle != -1);
}

Player::~Player()
{
    // �O���t�B�b�N�̊J��
    DeleteGraph(m_walkHandle);
    DeleteGraph(m_jumpHandle);
}

void Player::Init(Bg* pBg, SceneMain* pMain, Vec2 initPos)
{
    // �w�i
    m_pBg = pBg;
    m_pMain = pMain;
    // ���݈ʒu
    m_pos.x = initPos.x;
    m_pos.y = initPos.y;
    // �W�����v�t���O
    m_isGround = false;
    m_isJump = false;
    // �����x
    m_move.y = 0.0f;
    // �ҋ@���
    m_animation = Anim::kWalk;
    m_walkAnimFrame = 0;
}

void Player::Update()
{
    UpdatePlayerAnim();
    // ���E�ɃL�����N�^�[�𓮂���
    //m_isWalk = false;
    //if (Pad::IsPress(PAD_INPUT_LEFT))
    //{
    //    // ���L�[�������Ă��鎞�̏���
    //    m_pos.x -= kSpeed;   // �������Ɉʒu��ύX
    //    m_isDirLeft = true;  // �L�����N�^�[�����������Ă���
    //    m_isWalk = true;      // �����Ă���
    //}
    //if (Pad::IsPress(PAD_INPUT_RIGHT))
    //{
    //    // �E�L�[�������Ă��鎞�̏���
    //    m_pos.x += kSpeed;   // �E�����Ɉʒu��ύX
    //    m_isDirLeft = false; // �L�����N�^�[�����������Ă���
    //    m_isWalk = true;      // �����Ă���
    //}

    // �p�b�h���g�p����
    int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    m_isWalk = false;
    if (pad & (PAD_INPUT_RIGHT))
    {
        m_pos.x += kSpeed;
        m_isDirLeft = false;
       // m_animation = Anim::kWalk;
        m_isWalk = true;
    }
    if (pad & (PAD_INPUT_LEFT))
    {
        m_pos.x -= kSpeed;
        m_isDirLeft = true;
       // m_animation = Anim::kWalk;
        m_isWalk = true;
    }
   /* else
    {
        m_move.x = 0;
    }*/


 // �n�ʂɐڂ��Ă���
  if (m_isGround)
  {
      m_jumpFrame = 0;
      m_isJump = false;
      m_isAnimJump = false;
      if (Pad::IsTrigger(PAD_INPUT_1))
      {
          m_isGround = false;
          m_isJump = true;
          m_move.y += kJumpPower;
      }
      // �}�b�v�`�b�v�Ƃ̓����蔻��
      Rect chipRect;
      CheckHitMap(chipRect);
  }
  else
  {
     // m_isAnimJump = true;
      if (m_isJump)
      {
          UpdateJump();
      }
      m_move.y += kGravity;

      // �}�b�v�`�b�v�Ƃ̓����蔻��
      Rect chipRect;
      CheckHitMap(chipRect);
  }

    // �W�����v�̏���
    //if (pad & (PAD_INPUT_1))
    //{
    //    if (!m_isJump)
    //    {
    //        m_isJump = true;
    //        m_isAnimJump = false;
    //        m_jumpSpeed = kJumpPower;
    //    }
    //}

    //if (m_isJump)
    //{
    //    m_pos.y += m_jumpSpeed;

    //    m_jumpSpeed += kGravity; // ���t���[���������ɉ�������

    //    if (m_jumpSpeed > 0.0f)
    //    {
    //        if (m_pos.y >= kFieldHeight)
    //        {
    //             �W�����v�I������
    //            m_isJump = false;
    //            m_isAnimJump = false;
    //            m_jumpSpeed = 0.0f;
    //            
    //             �n�ʂɂ߂荞�ނ��Ƃ�����̂Œn�ʂ̍����Ɉʒu��␳����
    //            m_pos.y >= kFieldHeight;
    //        }
    //    }
    //}
    printfDx("m_pos:(%d,%d)\n",
        (int)m_pos.x,
        (int)m_pos.y);
}

void Player::Draw()
{
    DrawPlayer();
}

//float Player::GetLeft() const
//{
//	return (m_pos.x - kGraphWidth * 0.5f);
//}
//
//float Player::GetTop() const
//{
//	return (m_pos.y - kGraphHeight);
//}
//
//float Player::GetRigth() const
//{
//	return (m_pos.x + kGraphWidth * 0.5f);
//}
//
//float Player::GetBottom() const
//{
//	return  m_pos.y;
//}

void Player::CheckHitMap(Rect chipRect)
{
    // �����炠���������`�F�b�N����
    m_pos.x += m_move.x;
    m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kColX), static_cast<float>(kColY));
    if (m_pBg->IsCollision(m_colRect, chipRect))
    {
        if (m_move.x > 0.0f)
        {
            m_pos.x = chipRect.GetLeft() - kGraphWidth * 0.5f + kColChipadjustment;
        }
        else if (m_move.x < 0.0f)
        {
            m_pos.x = chipRect.GetRight() + kGraphWidth * 0.5f - kColChipadjustment;
        }
    }

    // �c���炠���������`�F�b�N����
    m_pos.y += m_move.y;
    m_colRect.SetCenter(m_pos.x, m_pos.y, static_cast<float>(kColX), static_cast<float>(kColY));
    if (m_pBg->IsCollision(m_colRect, chipRect))
    {
        if (m_move.x > 0.0f)
        {
            m_pos.y = chipRect.GetTop() - kGraphHeight * 0.5f;
            m_isGround = true;
        }
        else if (m_move.x < 0.0f)
        {
            m_pos.y = chipRect.GetBottom() + kGraphHeight * 0.5f;
            m_move.y *= -1.0f;
        }
    }
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

void Player::UpdatePlayerAnim()
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
}

void Player::DrawPlayer()
{
    // �v���C���[�̃A�j���[�V�����t���[��
    int animFrame = m_animFrame / kSingleAnimFrame;
    // �v���C���[�̐؂���摜
    // int walkSrcX = kWalkAnimNum[animFrame] * kGraphWidth;
    int walkSrcX = kWalkAnimNum[animFrame];
    int walkScrY = kGraphHeight;
    // �v���C���[�W�����v�̐؂�����W
//   int animJumpNo = kJumpAnimNum[animFrame];

  /*  if (m_animation == Anim::kWalk)
    {
        DrawRectRotaGraph(x, y, walkSrcX, walkScrY, kGraphWidth, kGraphHeight, kScale, 0.0f, m_walkHandle, true);
    }
    else if (m_animation == Anim::kJump)
    {
        DrawRectRotaGraph(x, y, 0, 0,kGraphWidth, kGraphHeight, kScale, 0.0f, m_jumpHandle, true);
    }*/



    // �W�����v�����ꍇ
    if (m_isAnimJump)
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_jumpHandle, true, m_isDirLeft);

    }
    else
    {
        DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth * 0.5f), static_cast<int>(m_pos.y - kGraphHeight),
            walkSrcX * kGraphWidth, 0, kGraphWidth, kGraphHeight,
            m_walkHandle, true, m_isDirLeft);

    }
}






