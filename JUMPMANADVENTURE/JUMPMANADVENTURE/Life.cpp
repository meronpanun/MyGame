#include "Life.h"
#include "DxLib.h"
#include <cassert>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace
{
	// �O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 17;
	constexpr int kGraphHeight = 17;

	// �\�����W
	constexpr int kBasePosX = 100;
	constexpr int kIntervalX = 80;
	constexpr int kPosY = 50;

	// �T�C�Y(�g�嗦)
	constexpr double kScale = 3.0;
	constexpr double kScaleAnimRange = 0.5; // �g��k���͈̔�
	constexpr int kAnimCycle = 60; // �A�j���[�V�����̎���
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

void Life::Update()
{
	// �A�j���[�V�����t���[���J�E���g���X�V
	m_animFrameCount++;
}

void Life::Draw()
{
	// index����\���ʒu�����肷��
	int posX = kBasePosX + m_index * kIntervalX;

	// �g��k���̃A�j���[�V�����v�Z
    double scaleAnim = kScale + kScaleAnimRange * std::sin(2 * M_PI * m_animFrameCount / kAnimCycle);

	DrawRectRotaGraph(posX, kPosY, // ���S���W���w�肷��
		0, 0, kGraphWidth, kGraphHeight,  // �O���t�B�b�N�̐؂�o���ʒu 
		scaleAnim, 0.0f,     // �g�嗦�A��]
		m_handle, true);
}

