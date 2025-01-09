#include "Camera.h"
#include "Player.h"
#include "Game.h"


namespace
{
	// �J�����͈�
	constexpr float CameraScopeRangeW = 400.0f;
	constexpr float CameraLerpRate = 0.15f;
	constexpr float CameraScopeRangeLeft = 300.0f;
	constexpr float CameraScopeRangeRight = 500.0f;
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
	if (player->GetPos().x > m_pos.x + (CameraScopeRangeW * 0.5f))	// �E�X�N���[��
	{
		aimCameraPos.x = player->GetPos().x - (CameraScopeRangeW * 0.5f);
	}
	else if (player->GetPos().x < m_pos.x - (CameraScopeRangeW * 0.5f)) // ���X�N���[��
	{
		aimCameraPos.x = player->GetPos().x + (CameraScopeRangeW * 0.5f);
	}

	// x���̈����J�������ړ����Ȃ��悤�ɌŒ�
	//if (player->GetPos().x < CameraScopeRangeW)
	//{
	//	aimCameraPos.x = player->GetPos().x + 200;
	//}

	// �ڕW�|�W�V�����ɁALerp���g���ăJ�����|�W�V�������߂Â���
//	m_pos = Lerp(m_pos, aimCameraPos, CameraLerpRate);

	// Draw���ɑ����Ă���camera.pos.x�͔��]������
	m_drawOffset.x = m_pos.x * -1;

	// ���̎��A��ʒ����Ƀv���C���[������悤�ɂ���
	// (camera.pos��ʒ����ɂȂ�悤�ɂ���)
//	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth * 0.5f);
	m_drawOffset.x = m_drawOffset.x + (Game::kScreenWidth - 1155);

}

//Vec2 Camera::Lerp(Vec2 start, Vec2 end, float t)
//{
//	Vec2 ret;
//	ret.x = std::lerp(start.x, end.x, t);
//	ret.y = std::lerp(start.y, end.y, t);
//	return ret;
//}

