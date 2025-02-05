#include "ItemHp.h"
#include "Player.h"
#include "BgStage.h"
#include "DxLib.h"
#include "Camera.h"
#include <cmath>
#include <cassert>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


namespace
{
	// ���a
	constexpr int kRadius = 16;

	// �O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 17;
	constexpr int kGraphHeight = 17;

	// �T�C�Y(�g�嗦)
	constexpr double kScale = 2.0;
	constexpr double kScaleAnimRange = 0.5; // �g��k���͈̔�
	constexpr int kAnimCycle = 60; // �A�j���[�V�����̎���
}

ItemHp::ItemHp():
	m_pos(0.0f, 0.0f),
	m_handle(-1),
	m_animFrameCount(0),
	m_isExist(true)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_handle = LoadGraph("data/image/heart.png");
	assert(m_handle != -1);
}

ItemHp::~ItemHp()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_handle);
}

void ItemHp::Init(Camera* camera)
{
	m_pCamera = camera;
}

void ItemHp::Update()
{
	// �A�j���[�V�����t���[���J�E���g���X�V
	m_animFrameCount++;
}

void ItemHp::Draw()
{
	if (!m_isExist) // �A�C�e�������݂��Ȃ��ꍇ�͕`�悵�Ȃ�
	{
		return;
	}

	// �g��k���̃A�j���[�V�����v�Z
	double scaleAnim = kScale + kScaleAnimRange * std::sin(2 * M_PI * m_animFrameCount / kAnimCycle);

	DrawRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y),
		scaleAnim, 0.0f, m_handle, true);

#ifdef _DEBUG
	// �����蔻��̃f�o�b�O�\��
	DrawCircle(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y), kRadius, 0xff0000, false);
#endif // _DEBUG
}

void ItemHp::SetPos(int x, int y)
{
	m_pos.x = x;
	m_pos.y = y;
}

void ItemHp::ItemLost()
{
	// �A�C�e�����擾���ꂽ�ꍇ�͑��݃t���O��false�ɂ���
	m_isExist = false; 
}

float ItemHp::GetRadius()
{
	return kRadius;
}

bool ItemHp::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	float Rlength = kRadius + pPlayer->GetRadius();
	float delX = pPlayer->GetPos().x - m_pos.x;
	float delY = pPlayer->GetPos().y - m_pos.y;

	float del = sqrt(delX * delX + delY * delY);
	if (del <= Rlength)
	{
		return true;
	}

	return false;
}

bool ItemHp::IsExist() const
{
	return m_isExist;
}
