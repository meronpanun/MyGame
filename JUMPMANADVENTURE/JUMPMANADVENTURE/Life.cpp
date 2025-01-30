#include "Life.h"
#include "DxLib.h"
#include <cassert>

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
}

void Life::Draw()
{
	// index����\���ʒu�����肷��
	int posX = kBasePosX + m_index * kIntervalX;

	DrawRectRotaGraph(posX, kPosY, // ���S���W���w�肷��
		0, 0, kGraphWidth, kGraphHeight,  // �O���t�B�b�N�̐؂�o���ʒu 
		kScale, 0.0,     // �g�嗦�A��]
		m_handle, true);
}

