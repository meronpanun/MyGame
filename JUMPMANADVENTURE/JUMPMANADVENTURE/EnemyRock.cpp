#include "EnemyRock.h"
#include "DxLib.h"
#include "BgStage1.h"

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
	constexpr int kRunFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 4;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kRunFrame) * kAnimFrameNum;
}

EnemyRock::EnemyRock():
	m_move(0.0f,0.0f),
	m_animFrame(0),
	m_animCount(0),
	m_isturnFlag(false),
	m_isAnimLeft(false),
	m_isAnimRight(false),
	m_dir(kRunRight)
{
}

EnemyRock::~EnemyRock()
{
}

void EnemyRock::Update()
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

	// ���������}�b�v�`�b�v�̋�`
	Rect chipRect;
	// �����瓖�����������`�F�b�N����
	m_pos.x += m_move.x;
	if (m_pBgStage1->IsCollision(GetRect(), chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.m_left - kWidth * 0.5f - 1;  // �}�b�v�`�b�v�̍����ɂԂ���Ȃ��ʒu�ɕ␳
			m_isturnFlag = true;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.m_right + kWidth * 0.5f + 1; // �}�b�v�`�b�v�̉E���ɂԂ���Ȃ��ʒu�ɕ␳
			m_isturnFlag = false;
		}
	}

	// �c���瓖�����������`�F�b�N����
	m_pos.y = m_move.y;
	if (m_pBgStage1->IsCollision(GetRect(), chipRect))
	{
		if (m_move.y > 0.0f) // �G���㉺�����Ɉړ����Ă���
		{
			// �n�ʂɂ���ꍇ�͉������Ȃ�
			m_pos.y = chipRect.m_top - 1;
			m_move.y = 0.0f;
		}
		else if (m_move.y < 0.0f)
		{
			m_move.y = chipRect.m_bottom + kHeight + 1;
		}
	}

}

void EnemyRock::Draw()
{
	// �O���t�B�b�N�̐؂�o���ʒu(X���W)���v�Z�ŋ��߂�
	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kRunFrame[animFrame] * kGraphWidth;
	int srcY = kGraphHeight * m_dir;

	DrawRectRotaGraph(m_pos.x, m_pos.y, 
		srcX, srcY, kGraphWidth, kGraphHeight, 
		1.0, 0.0, m_handle, true, false);
}
