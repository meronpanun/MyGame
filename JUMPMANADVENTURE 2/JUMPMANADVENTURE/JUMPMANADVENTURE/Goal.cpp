#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "BgStage1.h"
#include "Camera.h"

namespace
{
	// ���a
	constexpr int kRadius = 64;
	
	// �S�[���̕`��T�C�Y
	constexpr int kGraphWidth = 64;
	constexpr int kGraphHeight = 64;

	// �S�[���̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 6;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// �A�j���[�V�����̃R�}��
	constexpr int kLoopAnimNum = 10;

	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 4;

	// �\�����W
	constexpr int kPosX = 250;
	constexpr int kPosY = 605;

	// �g�嗦
	constexpr double kScale = 2.0f;
}

Goal::Goal():
	m_pos(250.0f,600.0f),
	m_animFrame(0),
	m_handle(0),
	m_index(0)
{
}

Goal::~Goal()
{
}

void Goal::Init(Camera* camera)
{
	m_pCamera = camera;
}

void Goal::Update()
{
	// �A�j���[�V�����̐i�s
	m_animFrame++;
	if (m_animFrame >= kLoopAnimNum * kSingleAnimFrame)
	{
		m_animFrame = 0;
	}
}

void Goal::Draw()
{
	// �O���t�B�b�N�̐؂�o���ʒu(X���W)���v�Z�ŋ��߂�
	int animNo = m_animFrame / kSingleAnimFrame;

	// index����\���ʒu�����肷��
	int posX = kPosX + m_index;

	DrawRectRotaGraph(kPosX + m_pCamera->m_drawOffset.x, kPosY, 
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, 
		kScale, 0.0, 
		m_handle, true);
}

float Goal::GetRadius() const
{
	return kRadius;
}

bool Goal::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	float Rlength = kRadius + pPlayer->GetRadius(); // �v���C���[�ƃS�[���̔��a�̍��v
	float delX = pPlayer->GetPos().x - m_pos.x; // X�����̋���
	float delY = pPlayer->GetPos().y - m_pos.y; // Y�����̋���

	float del = sqrt((delX * delX) + (delY * delY));

	if (del <= Rlength)
	{
		return true;
	}

	return false;
}
