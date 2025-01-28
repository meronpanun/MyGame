#include "Camera.h"
#include "Player.h"
#include "Game.h"
#include <cmath> 

namespace
{
	// �J�����͈�
	constexpr float kCameraScopeRangeW = 400.0f;
	// �J������Lerp��
	constexpr float kCameraLerpRate = 0.15f;  

	// �J�����̍��[�ʒu���C���̒���
	constexpr int kAdjustmentX = 100;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update(const Player* player)
{
	// �v���C���[�̈ʒu���J�����̒���������ȏ㗣�ꂽ��
	// �J�����́u�ڕW�v�|�W�V���������͈̔͂ɗ��߂�
	Vec2 aimCameraPos = m_pos;
	if (player->GetPos().x > m_pos.x + (kCameraScopeRangeW * 0.5f))	// �E�X�N���[��
	{
		aimCameraPos.x = player->GetPos().x - (kCameraScopeRangeW * 0.5f);
	}

	// �ڕW�|�W�V�����ɁALerp���g���ăJ�����|�W�V�������߂Â���
	m_pos = Lerp(m_pos, aimCameraPos, kCameraLerpRate);

	// Draw���ɑ����Ă���camera.pos.x�͔��]������
	m_drawOffset.x = m_pos.x * -1;

	// ���̎��A��ʍ����Ƀv���C���[������悤�ɂ���
	// (camera.pos��ʒ����ɂȂ�悤�ɂ���)
	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth - 1155);
}

float Camera::GetLeft() const
{
	return m_pos.x - 100;
}

Vec2 Camera::Lerp(Vec2 start, Vec2 end, float t)
{
	Vec2 ret;
	ret.x = start.x + t * (end.x - start.x); 
	ret.y = start.y + t * (end.y - start.y);
	return ret;
}

