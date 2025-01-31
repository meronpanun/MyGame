#include "Goal.h"
#include "DxLib.h"
#include "Player.h"
#include "BgStage1.h"
#include "Camera.h"

#ifdef _DEBUG
#define DISP_COLLISON
#endif // _DEBUG

namespace
{	
	// ���̕`��T�C�Y
	constexpr int kGraphWidth = 64;
	constexpr int kGraphHeight = 24;
	// �|�[���̕`��T�C�Y
	constexpr int kPoleGraphWidth = 24;
	constexpr int kPoleGraphHeight = 103;

	// �S�[���̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7,8,9 };
	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 6;
	// �A�j���[�V������1�T�C�N���̃t���[����
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;

	// �S�[���̕\�����W
	constexpr int kFlagPosX = 10000;
	constexpr int kFlagPosY = 300;
	constexpr int kPolePosX = 10034;
	constexpr int kPolePosY = 450;

	// �|�[���̓����蔻��ʒu
	constexpr float kPoleColPosX = 6.0f;
	constexpr float kPoleColPosY = 220.0f;
	// �|�[���̓����蔻��T�C�Y
	constexpr float kPoleColSizeX = 15.0f;
	constexpr float kPoleColSizeY = 600.0f;

	// �g�嗦
	constexpr double kScale = 4.0f; 

	// ���̗������x
	constexpr float kFlagFallSpeed = 2.0f;
	// ���̒n�ʂ̍���
	constexpr float kFlagGroundHeight = 528.0f;
}

Goal::Goal():
	m_pos(10000.0f, 528.0f),
	m_animFrame(0),
	m_handle(0),
	m_index(0),
	m_poleCollisionOffset(-kPoleColPosX, -kPoleColPosY),
	m_poleCollisionSize(kPoleColSizeX, kPoleColSizeY),
	m_flagPosY(kFlagPosY),
	m_flagFallSpeed(kFlagFallSpeed)
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
	if (m_animFrame >= kAnimFrameCycle)
	{
		m_animFrame = 0;
	}

	// ���̗�������
	if (m_isFlagFalling && !m_isFlagFallen)
	{
		m_flagPosY += m_flagFallSpeed;
		if (m_flagPosY >= kFlagGroundHeight)
		{
			m_flagPosY = kFlagGroundHeight;
			m_isFlagFallen = true;
		}
	}
}

void Goal::Draw()
{
	// �O���t�B�b�N�̐؂�o���ʒu(X���W)���v�Z�ŋ��߂�
	int animNo = m_animFrame / kAnimFrameNum;

	DrawRectRotaGraph(kFlagPosX + m_pCamera->m_drawOffset.x, kFlagPosY,
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight, 
		kScale, 0.0, 
		m_handle, true);

	DrawRectRotaGraph(kPolePosX + m_pCamera->m_drawOffset.x, kPolePosY,
		0, 0, kPoleGraphWidth, kPoleGraphHeight,
		kScale, 0.0,
		m_poleHandle, true);

#ifdef DISP_COLLISON
	// �����蔻��̃f�o�b�O�\��
	DrawBox(kPolePosX + m_pCamera->m_drawOffset.x + m_poleCollisionOffset.x, kPolePosY + m_poleCollisionOffset.y,
		kPolePosX + m_pCamera->m_drawOffset.x + m_poleCollisionOffset.x + m_poleCollisionSize.x,
		kPolePosY + m_poleCollisionOffset.y + m_poleCollisionSize.y,
		0xff0000, false);
#endif // DISP_COLLISION
}

bool Goal::GetHitPlayerFlag(std::shared_ptr<Player> pPlayer)
{
	// �v���C���[�ƃ|�[���̓����蔻��
	Rect poleRect;
	poleRect.SetTlSize(Vec2(kPolePosX + m_poleCollisionOffset.x, kPolePosY + m_poleCollisionOffset.y),
		Vec2(m_poleCollisionSize.x, m_poleCollisionSize.y));

	Rect playerRect = pPlayer->GetRect();

	if (poleRect.IsCollision(playerRect))
	{
		return true;
	}

	return false;
}

void Goal::SetPoleCollisionOffset(float offsetX, float offsetY)
{
	m_poleCollisionOffset.SetPos(offsetX, offsetY);
}

void Goal::SetPoleCollisionSize(float width, float height)
{
	m_poleCollisionSize.SetPos(width, height);
}

void Goal::StartFlagFall()
{
	m_isFlagFalling = true;
}

bool Goal::IsFlagFallen() const
{
	return m_isFlagFallen;
}
