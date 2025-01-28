#include "Life.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	// �O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	//constexpr int kGraphWidth = 16;
	//constexpr int kGraphHeight = 16;

	// HP�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
//	constexpr int kUseFrame[] = { 0,1,2 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 4;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kSingleAnimFrame;

	// �\�����W
	constexpr int kBasePosX = 100;
	constexpr int kIntervalX = 80;

	constexpr int kPosY = 50;

	// �T�C�Y(�g�嗦)
	constexpr double kScale = 3.0;
}

Life::Life():
	m_handle(-1),
	m_animFrameCount(0),
	m_index(0)
{
}

Life::~Life()
{
}

void Life::Init()
{
}

void Life::End()
{
}

void Life::Update()
{
	// �A�j���[�V�����̐i�s
	m_animFrameCount++;
	if (m_animFrameCount >= kAnimFrameCycle)
	{
		m_animFrameCount = 0;
	}
}

void Life::Draw()
{
	// �O���t�B�b�N�̐؂�o���ʒu(X���W)���v�Z�ŋ��߂�
	int animNo = m_animFrameCount / kSingleAnimFrame;

	// index����\���ʒu�����肷��
	int posX = kBasePosX + m_index * kIntervalX;

	DrawRectRotaGraph(posX, kPosY, // ���S���W���w�肷��
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,  // �O���t�B�b�N�̐؂�o���ʒu 
		kScale, 0.0,     // �g�嗦�A��]
		m_handle, true);
}
