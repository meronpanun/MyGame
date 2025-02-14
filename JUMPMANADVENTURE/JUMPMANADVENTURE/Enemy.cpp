#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"
#include "BgStage.h"
#include "Player.h"
#include "Camera.h"
#include <assert.h>

namespace
{
	// �G�̕`��T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 28;
	
	// �g�嗦
	constexpr float kScale = 2.0f;

	// ���x
	constexpr float kSpeed = 1.5f;

	// �d��
	constexpr float kGravaity = 0.5f;

	// �L�����N�^�[�̃A�j���[�V����
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;

	// �}�b�v�`�b�v�Ƃ̓����蔻��̒���
	constexpr int kColChipAdjustmentY = 28;

	// �q�b�g�A�j���[�V����
	constexpr int kHitFrame[] = { 0 };
	constexpr int kHitAnimFrame = 12;

	// ���S�A�j���[�V�����̃t���[����
	constexpr int kDeathAnimDuration = 30;
}

Enemy::Enemy():
	m_pCamera(nullptr), 
	m_pos(0.0f,0.0f),
	m_move(-kSpeed, 0.0f),
	m_animFrame(0),
	m_animCount(0),
	m_videoFadeFrameCount(0), 
	m_videoFadeInFrameCount(0), 
	m_videoHandle(-1),
	m_isAnimLeft(true),
	m_isAnimRight(false),
	m_isAlive(true),
	m_isFacingRight(false),
	m_isActive(false),
	m_isVideoPlaying(false)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_handle = LoadGraph("data/image/rockRun.png");
	assert(m_handle != -1);
	m_hitHandle = LoadGraph("data/image/rockHit.png");
	assert(m_hitHandle != -1);
}

Enemy::~Enemy()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_handle);
	DeleteGraph(m_hitHandle);
}

void Enemy::Init(Camera* camera)
{
	m_pCamera = camera;
}

void Enemy::Update()
{
	// �G�������Ă���ꍇ�͏������s��Ȃ�
	if (!m_isAlive) return;

	bool isMove = false;

	// ���t���[���������ɉ�������
	m_move.y += kGravaity;

	// �G�̈ړ�����
	if (m_move.x < 0.0f)
	{
		m_isAnimLeft = true;
		m_isAnimRight = false;
		m_isFacingRight = false;
	}
	else
	{
		m_isAnimLeft = false;
		m_isAnimRight = true;
		m_isFacingRight = true;
	}

	isMove = true;

	if (isMove)
	{
		// �A�j���[�V�����̐i�s
		m_animFrame++;
		if (m_animFrame >= kAnimFrameCycle)
		{
			m_animFrame = 0;
		}
	}

	// ���̓����蔻��
	m_pos.x += m_move.x;
	Rect chipRect;
	if (m_pBgStage->IsCollision(GetRect(), chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.m_left - kGraphWidth * kScale * 0.5f - 1;
			ReverseDirection(); // �ǂɓ�������������]��
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.m_right + kGraphWidth * kScale * 0.5f + 1;
			ReverseDirection(); // �ǂɓ�������������]��
		}
	}

	// �c�̓����蔻��
	m_pos.y += m_move.y;
	if (m_pBgStage->IsCollision(GetRect(), chipRect))
	{
		if (m_move.y > 0.0f) // �G�l�~�[���������Ɉړ����Ă���
		{
			m_pos.y = chipRect.m_top - 1;
			m_move.y = 0.0f; // �n�ʂɗ����Ă���̂�y�����̑��x�����Z�b�g
		}
		else if (m_move.y < 0.0f) // �G�l�~�[��������Ɉړ����Ă���
		{
			m_pos.y = chipRect.m_bottom + kGraphHeight * kScale + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
			m_move.y = 0.0f; // ������ւ̉��������Z�b�g
		}
	}
}

void Enemy::Draw()
{
	// �G�������Ă���ꍇ�͏������s��Ȃ�
	if (!m_isAlive) return;

	// �O���t�B�b�N�̐؂�o���ʒu(X���W)���v�Z�ŋ��߂�
	int animFrame = m_animFrame / kAnimFrameNum;

	DrawRectRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x),static_cast<int>(m_pos.y - kColChipAdjustmentY),
		animFrame * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		kScale, 0.0f, m_handle, true, m_isFacingRight);

#ifdef _DEBUG
	// �����蔻��̃f�o�b�O�\��
	DrawBox(GetLeft() + m_pCamera->m_drawOffset.x,
		GetTop(),
		GetRigth() + m_pCamera->m_drawOffset.x,
		GetBottom(),
		0xff0000, false);
#endif // _DEBUG
}


float Enemy::GetLeft() 
{
	return m_pos.x - kGraphWidth * kScale * 0.5f;
}

float Enemy::GetTop() 
{
	return m_pos.y - kGraphHeight * kScale;
}

float Enemy::GetRigth() 
{
	return m_pos.x + kGraphWidth * kScale * 0.5f;
}

float Enemy::GetBottom() 
{
	return m_pos.y;
}

Rect Enemy::GetRect() 
{
	// �G�̋�`�����蔻����
	Rect rect;
	rect.m_top = GetTop();
	rect.m_bottom = GetBottom();
	rect.m_left = GetLeft();
	rect.m_right = GetRigth();
	return rect;
}

// �G�̐����t���O��ݒ�
void Enemy::SetAlive(bool isAlive)
{
	m_isAlive = isAlive;
}

// �G�̈ʒu��ݒ�
void Enemy::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

// �G�̈ړ������𔽓]
void Enemy::ReverseDirection()
{
	// �ړ������𔽓]
	m_move.x = -m_move.x;
	// �O���t�B�b�N�̌����𔽓]
	m_isFacingRight = !m_isFacingRight;
}

// �G���������Ă��邩�ǂ���
bool Enemy::IsAlive() const
{
	return m_isAlive;
}

// �v���C���[���G�̍U���͈͓��ɂ��邩�ǂ���
bool Enemy::IsPlayerInRange(const Vec2& playerPos, float range)
{
	Vec2 enemyPos = m_pos;
	return (playerPos - enemyPos).Length() <= range;
}

// �v���C���[���G�̍U���͈͂ɓ�������G���A�N�e�B�u�ɂ���
void Enemy::Activate()
{
	m_isActive = true;
}

// �G���A�N�e�B�u���ǂ���
bool Enemy::IsActive() const
{
	return m_isActive;
}
