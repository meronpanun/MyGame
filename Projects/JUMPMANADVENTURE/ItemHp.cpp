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
	constexpr int kRadius = 28;

	// �O���t�B�b�N�̃T�C�Y
	constexpr int kGraphWidth = 17;
	constexpr int kGraphHeight = 17;

	// �T�C�Y(�g�嗦)
	constexpr double kScale = 2.0;
	constexpr double kScaleAnimRange = 0.5; // �g��k���͈̔�
	constexpr int kAnimCycle = 60; // �A�j���[�V�����̎���

	// �G�t�F�N�g�̕`��T�C�Y
	constexpr int kEffectGraphWidth = 64; 
	constexpr int kEffectGraphHeight = 62;

	// �G�t�F�N�g�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 6;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

ItemHp::ItemHp():
	m_pCamera(nullptr),
	m_pos(0.0f, 0.0f),
	m_handle(-1),
	m_effectHandle(-1),
	m_animFrameCount(0),
	m_isExist(true),
	m_effectAnimFrameCount(0),
	m_isEffectPlaying(false)
{
	// �O���t�B�b�N�̓ǂݍ���
	m_handle = LoadGraph("data/image/heart.png");
	assert(m_handle != -1);

	// �G�t�F�N�g�̓ǂݍ���
	m_effectHandle = LoadGraph("data/image/itemHpEffect.png");
	assert(m_effectHandle != -1);
}

ItemHp::~ItemHp()
{
	// �O���t�B�b�N�̊J��
	DeleteGraph(m_handle);

	// �G�t�F�N�g�̊J��
	DeleteGraph(m_effectHandle);
}

void ItemHp::Init(Camera* camera)
{
	m_pCamera = camera;
}

void ItemHp::Update()
{
	// �A�j���[�V�����t���[���J�E���g���X�V
	m_animFrameCount++;

	// �G�t�F�N�g�̃A�j���[�V�������Đ����̏ꍇ�A�t���[���J�E���g���X�V
	if (m_isEffectPlaying)
	{
		m_effectAnimFrameCount++;
		if (m_effectAnimFrameCount >= kAnimFrameCycle)
		{
			m_isEffectPlaying = false; // �A�j���[�V�������I��������Đ��t���O���I�t�ɂ���
		}
	}
}

void ItemHp::Draw()
{
	// �A�C�e�������݂����A�G�t�F�N�g���Đ����łȂ��ꍇ�͕`�悵�Ȃ�
	if (!m_isExist && !m_isEffectPlaying)
	{
		return;
	}

	// �g��k���̃A�j���[�V�����v�Z
	double scaleAnim = kScale + kScaleAnimRange * std::sin(2 * M_PI * m_animFrameCount / kAnimCycle);

	if (m_isExist)
	{
		DrawRotaGraph(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y),
			scaleAnim, 0.0f, m_handle, true);
	}

	// �G�t�F�N�g�̃A�j���[�V������`��
	if (m_isEffectPlaying)
	{
		int frameIndex = m_effectAnimFrameCount / kAnimFrameNum;
		// �G�t�F�N�g�̕`��ʒu
		int effectX = static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x - kEffectGraphWidth); // ���S�ɕ`�悷�邽�߂ɕ��̔���������
		int effectY = static_cast<int>(m_pos.y - kEffectGraphHeight); // ��[�ɕ`�悷�邽�߂ɍ���������
		DrawRectExtendGraph(effectX, effectY, effectX + 2 * kEffectGraphWidth, effectY + 2 * kEffectGraphHeight,
			kUseFrame[frameIndex] * kEffectGraphWidth, 0, kEffectGraphWidth, kEffectGraphHeight, m_effectHandle, true);
	}

#ifdef _DEBUG
	// �����蔻��̃f�o�b�O�\��
	DrawCircle(static_cast<int>(m_pos.x + m_pCamera->m_drawOffset.x), static_cast<int>(m_pos.y), kRadius, 0xff0000, false);
#endif // _DEBUG
}

/// <summary>
/// �A�C�e���̈ʒu��ݒ�
/// </summary>
/// <param name="x">X���W</param>
/// <param name="y">Y���W</param>
void ItemHp::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
}

/// <summary>
/// �A�C�e���������鏈��
/// </summary>
void ItemHp::ItemLost()
{
	// �A�C�e�����擾���ꂽ�ꍇ�͑��݃t���O��false�ɂ���
	m_isExist = false; 

	// �G�t�F�N�g�̃A�j���[�V�������J�n
	m_isEffectPlaying = true;
	m_effectAnimFrameCount = 0;
}

/// <summary>
/// �A�C�e���̔��a���擾
/// </summary>
/// <returns>���a</returns>
float ItemHp::GetRadius()
{
	return kRadius;
}

/// <summary>
/// �A�C�e���ƃv���C���[�������������ǂ���
/// </summary>
/// <param name="pPlayer">�v���C���[�̃|�C���^</param>
/// <returns>�����������ǂ���</returns>
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

/// <summary>
///  �A�C�e�������݂��邩�ǂ����𔻒�
/// </summary>
/// <returns>���݃t���O</returns>
bool ItemHp::IsExist() const
{
	return m_isExist;
}
