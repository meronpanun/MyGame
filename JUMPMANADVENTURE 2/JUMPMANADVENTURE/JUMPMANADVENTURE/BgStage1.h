#pragma once
#include "Bg.h"
#include "Rect.h"

class Player;
class BgStage1 /* : public Bg*/
{
public:
	BgStage1();
	virtual ~BgStage1();

//	virtual void Init() override;
//	virtual void Update() override;
//	virtual void Draw(/*Camera* camera*/) override;

	void Init();
	void Update();
	void Draw();

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
//	virtual int GetScrollX() override;
//	int GetScrollX();

	//�w�肵����`�Ɠ������Ă��邩����
//	virtual bool IsCollision(Rect rect, Rect& ChipRect) override;
	bool IsCollision(Rect rect, Rect& ChipRect);


	//�����o�[�ϐ��ɃA�N�Z�X����
 //	void SetHandle(int handle) { m_handle001 = handle; }
 //	void SetHandle02(int handle) { m_handle002 = handle; }

	//�v���C���[�̃|�C���^��ݒ肷��
//	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

private:
	Player* m_pPlayer;

	// �}�b�v�̃O���t�B�b�N�n���h��
	  int m_handle001;
	//	int m_handle002;
};

