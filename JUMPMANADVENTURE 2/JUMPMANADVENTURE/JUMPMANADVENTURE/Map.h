#pragma once
#include <memory>
#include "Rect.h"

class Camera;
class Player;
class Map
{
public:
	Map();
	virtual ~Map();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle001 = handle; }
	//	void SetHandle02(int handle) { m_handle002 = handle; }

	//�v���C���[�̃|�C���^��ݒ肷��
//	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	void Init();
	void Update();
	void Draw(Camera* camera);

	//�v���C���[�̈ʒu����X�N���[���ʂ��擾����
//	int GetScrollX();

	//�w�肵����`�Ɠ������Ă��邩����
	//�Q�Ƃ��g�p���ĂԂ������}�b�v�`�b�v�̋�`�����擾����
	bool IsCollision(Rect rect, Rect& ChipRect);

private:
	// �X�N���[���ʂ����肷�邽�߂Ƀv���C���[�̈ʒu��񂪕K�v
//	Player* m_pPlayer;

	// �}�b�v�̃O���t�B�b�N�n���h��
	int m_handle001;
	//	int m_handle002;
};

