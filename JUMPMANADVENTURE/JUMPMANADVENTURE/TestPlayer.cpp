#include "TestPlayer.h"
#include "DxLib.h"
#include "Pad.h"
#include "Game.h"
#include "Camera.h"
#include <cassert>

namespace
{
	// �L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// �A�j���[�V�����̃R�}��
	constexpr int kIdleAnimNum = 11;
	constexpr int kRunAnimNum = 12;

	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 4;

	// �L�����N�^�[�̈ړ����x
	constexpr float kSpeed = 0.5f;
	// ���G����
	constexpr int kInvincible = 30;
	// �ő�c�@
	constexpr int kMaxHp = 3;

	// �n�ʂ̍���
	constexpr float kFieldHeight = 480.0f - 48.0f;

	// �W�����v����
	constexpr float kJumpPower = -9.5f;	// �W�����v�̏���
	float kJumpGravity = 0.4f;	// �d��
	float kGravity = 0.5f;
	bool FallFrag = false;

	// ���E�̕�
	constexpr float kLeftWall = 64.0f;
	constexpr float kRightWall = 96.0f;
}

TestPlayer::TestPlayer() :
	m_handleIdle(-1),
	m_handleRun(-1),
	m_pos(320.0f, kFieldHeight),
	m_isDirLeft(false),
	m_animFrame(0),
	m_isRun(false),
	m_invincibleCount(0),
	m_hp(kMaxHp),
	m_isJump(false),
	m_jumpSpeed(0.0f)
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Init(Camera* camera)
{
	m_handleIdle = LoadGraph("data/image/Idle .png");
	assert(m_handleIdle != -1);

	m_handleRun = LoadGraph("data/image/Run.png");
	m_camera = camera;
	m_camera->m_pos.SetPos(m_pos.x, m_pos.y);
}

void TestPlayer::End()
{
	// �O���t�B�b�N�����
	DeleteGraph(m_handleIdle);
	DeleteGraph(m_handleRun);
}

void TestPlayer::OnDamage()
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

void TestPlayer::Update()
{
	m_animFrame++;
	// m_animFrame
	// �ҋ@����0~65 0~71
	// m_animFrame >= 66 �̎��Ɉړ��A�j������ҋ@�A�j���ɐ؂�ւ��

	int totalFrame = kIdleAnimNum * kSingleAnimFrame;
	if (m_isRun)
	{
		totalFrame = kRunAnimNum * kSingleAnimFrame;
	}
	if (m_animFrame >= kIdleAnimNum * kSingleAnimFrame)
	{
		m_animFrame = 0;
	}

	// �O��̃A�j���[�V�������o���Ă���
	bool isLastRun = m_isRun;

	// ���G���Ԃ̍X�V
	m_invincibleCount--;
	if (m_invincibleCount < 0)
	{
		m_invincibleCount = 0;
	}

	// ���E�ɃL�����N�^�[�𓮂���
	m_isRun = false;
	if (Pad::IsPress(KEY_INPUT_LEFT))
	{
		// ���L�[�������Ă���Ƃ��̏���
		m_velocity.x -= kSpeed;
		m_isDirLeft = true;
		m_isRun = true;
	}
	else if (Pad::IsPress(KEY_INPUT_RIGHT))
	{
		// �E�L�[�������Ă���Ƃ��̏���
		m_velocity.x += kSpeed;
		m_isDirLeft = false;
		m_isRun = true;
	}

	if (!m_isRun)
	{
		m_velocity.x = 0.0f;
	}

	if (!m_isJump)
	{
		m_velocity.y += kGravity;
	}

	if (m_velocity.y > 0)
	{
		FallFrag = true;
	}
	else
	{
		FallFrag = false;
	}

	// velocity��3.0f�ɂȂ�����������~�߂�
	if (m_velocity.x >= 3.0f)
	{
		m_velocity.x = 3.0f;
	}
	if (m_velocity.x <= -3.0f)
	{
		m_velocity.x = -3.0f;
	}

	// 1�{�^���ŃW�����v
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		if (!m_isJump)
		{
			m_isJump = true;
			m_velocity.y = kJumpPower;
		}
	}

	// ���̕ǂɓ�����
	if (m_pos.x <= kLeftWall)
	{
		m_pos.x = kLeftWall + 0.1f;
		m_velocity.x = 0.0f;
	}

	// �E�̕ǂɓ�����
	if (m_pos.x >= Game::kScreenWidth - kRightWall)
	{
		m_pos.x = Game::kScreenWidth - kRightWall - 0.1f;
		m_velocity.x = 0.0f;
	}

	if (m_isJump)
	{
		m_velocity.y += kJumpGravity;
	}

	m_pos += m_velocity;
}

void TestPlayer::Draw()
{
	int animNo = m_animFrame / kSingleAnimFrame;

	int useHandle = m_handleIdle;
	if (m_isRun)
	{
		useHandle = m_handleRun;
	}
	//�`��ʒu�̌���
	int tempX = static_cast<int>(m_pos.x) + static_cast<int>(m_camera->m_drawOffset.x);
	int tempY = static_cast<int>(m_pos.y) + static_cast<int>(m_camera->m_drawOffset.y);
	DrawRectGraph(tempX, tempY,
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		useHandle, true, m_isDirLeft);
}

float TestPlayer::GetLeft() const
{
   return (m_pos.x + kGraphWidth * 0.5f);
}

float TestPlayer::GetTop() const
{
	return m_pos.y;
}

float TestPlayer::GetRight() const
{
	return (m_pos.x + kGraphWidth);
}

float TestPlayer::GetBottom() const
{
	return (m_pos.y + kGraphHeight);
}

float TestPlayer::PlayerAirPos()
{
	return m_pos.y -= 2.0f;
}

bool TestPlayer::FallFlag()
{
	return FallFrag;
}


int TestPlayer::GetPlayerHp()
{
	return m_hp;
}

void TestPlayer::AddMove(Vec2 move)
{
	m_pos += move;
}

void TestPlayer::AddMoveY(float DisY)
{
	m_pos.y += DisY;
}

void TestPlayer::AddMoveLeft(float left)
{
	m_pos.x -= left;
}

void TestPlayer::AddMoveRight(float right)
{
	m_pos.x += right;
}

void TestPlayer::SetVelocity(Vec2 velocity)
{
	m_velocity = velocity;
}

void TestPlayer::OnCollideY()
{
	m_velocity.y = 0;
}

void TestPlayer::OnCollideX()
{
	m_velocity.x = 0;
}

void TestPlayer::Landing(float DisY)
{
	m_isJump = false;
	m_pos.y -= DisY;
}

Vec2 TestPlayer::GetPos() const
{
	return m_pos;
}