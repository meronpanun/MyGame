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


}

void EnemyRock::Draw()
{
}