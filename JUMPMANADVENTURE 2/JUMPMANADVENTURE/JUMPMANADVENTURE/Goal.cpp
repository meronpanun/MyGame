#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "BgStage1.h"
#include "Camera.h"

namespace
{
	// ���a
	constexpr int kRadius = 32;
	
	// �S�[���̕`��T�C�Y
	constexpr int kGraphWidth = 64;
	constexpr int kGraphHeight = 64;

	// �S�[���̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 6;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Goal::Goal():
	m_pos(5000.0f,610.0f),
	m_animFrame(0),
	m_handle(0)
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
	m_animFrame++;
	if (m_animFrame >= kAnimFrameCycle)
	{
		m_animFrame = 0;
	}
}

void Goal::Draw()
{
	int animFrame = m_animFrame / kAnimFrameNum;

	int srcX = kUseFrame[animFrame] * kGraphWidth;
	int srcY = kGraphHeight * 0;

	DrawRectRotaGraph(32 + m_pCamera->m_drawOffset.x, 32, srcX, srcY, kGraphWidth, kGraphHeight, 1.0, 0.0, m_handle, true, false);
}

float Goal::GetRadius()
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
