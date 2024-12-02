#pragma once
#include <memory>
#include "Rect.h"

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
//	void SetPlayer(std::shared_ptr<TestPlayer>pTestPlayer) { m_pPlayer = pTestPlayer; }

	void Update();
	void Draw();

	//�v���C���[�̈ʒu����X�N���[���ʂ��擾����
//	int GetScrollX();

	//�w�肵����`�Ɠ������Ă��邩����
	//�Q�Ƃ��g�p���ĂԂ������}�b�v�`�b�v�̋�`�����擾����
	bool IsCollision(Rect rect, Rect& testChipRect);

private:
	// �X�N���[���ʂ����肷�邽�߂Ƀv���C���[�̈ʒu��񂪕K�v
	std::shared_ptr<Player>m_pPlayer;


	int m_handle001;
	//	int m_handle002;
};

