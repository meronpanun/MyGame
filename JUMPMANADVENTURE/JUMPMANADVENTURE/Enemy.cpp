#include "Enemy.h"
#include "DxLib.h"
#include "Game.h"
#include "BgStage1.h"
#include "Player.h"
#include "Camera.h"
#include <assert.h>

namespace
{
	// �G�̃T�C�Y	
	constexpr int kWidth = 30;
	constexpr int kHeight = 30;

	// �G�̕`��T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 28;

	// ���x
	constexpr float kSpeed = 2.5f;

	// �d��
	constexpr float kGravaity = 0.5f;

	// �L�����N�^�[�̃A�j���[�V����
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;


	// �~�̓����蔻��̔��a
	constexpr int kRadius = 10;
}

Enemy::Enemy():
	m_pos(550.0f,640.0f),
	m_move(0.0f, 0.0f),
	m_animFrame(0),
	m_animCount(0),
	m_isturnFlag(false),
	m_isAnimLeft(false),
	m_isAnimRight(false),
	m_dir(kRunRight)
{
	m_handle = LoadGraph("data/image/RockRun.png");
	assert(m_handle != -1);
}

Enemy::~Enemy()
{
	DeleteGraph(m_handle);
}

void Enemy::Init()
{
}

void Enemy::Update()
{
	bool isMove = false;

	// ���t���[���������ɉ�������
	m_move.y += kGravaity;

	if (m_isturnFlag = false)
	{
		m_move.x = kSpeed;
		m_isAnimRight = true;
		isMove = true;
		m_dir = kRunRight;
	}
	if (m_isturnFlag = true)
	{
		m_move.y = -kSpeed;
		m_isAnimLeft = true;
		isMove = true;
		m_dir = kRunLeft;
	}

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
//	m_pos.y += m_move.y;
	if (m_pBgStage1->IsCollision(GetRect(), chipRect))
	{
		if (m_move.y > 0.0f) // �v���C���[���������Ɉړ����Ă���
		{
			// �n�ʂɗ����Ă��鉽�����Ȃ�
			m_pos.y = chipRect.m_top - 1;
		}
		else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
		{
			m_pos.y = chipRect.m_bottom + kGraphHeight + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
			m_move.y *= -1.0f; // ������ւ̉������������ɕϊ�
		}
	}
}

void Enemy::Draw()
{
	// �O���t�B�b�N�̐؂�o���ʒu(X���W)���v�Z�ŋ��߂�
	int animFrame = m_animFrame / kAnimFrameNum;

	//int srcX = kRunFrame[animFrame] * kGraphWidth;
	//int srcY = kGraphHeight * m_dir;

	//bool isFlip = false;
	//if (kSpeed > 0.0f)
	//{
	//	isFlip = true;
	//}

	DrawRectRotaGraph(m_pos.x, m_pos.y,
		animFrame * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		1.0, 0.0, m_handle, true);

#ifdef _DEBUG
	// �����蔻��̃f�o�b�O�\��
	DrawBox(GetLeft(), GetTop(),
		GetRigth(), GetBottom(),
		0xff0000, false);
#endif // _DEBUG
}




float Enemy::GetLeft() 
{
	return m_pos.x - kGraphWidth * static_cast<float>(0.5f);
}

float Enemy::GetTop() 
{
	return m_pos.y - kGraphHeight;
}

float Enemy::GetRigth() 
{
	return m_pos.x + kGraphWidth * static_cast<float>(0.5f);
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

bool Enemy::IsGetHitPlayer(std::shared_ptr<Player> pPlayer)
{
	// �v���C���[�ƓG�̔��a�̍��v
	float Rlength = kRadius + pPlayer->GetRadius();
	// X�����̋���
	float delX = pPlayer->GetPos().x - m_pos.x;
	// Y�����̋���
	float delY = pPlayer->GetPos().y - m_pos.y;

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{
		return true;
	}

	return false;
}
