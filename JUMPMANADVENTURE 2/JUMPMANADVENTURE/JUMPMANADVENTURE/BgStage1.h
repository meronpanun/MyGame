#pragma once
#include "Bg.h"
#include "Rect.h"
#include "Player.h"

class Camera;
class Player;
class BgStage1
{
public:
	BgStage1();
	virtual ~BgStage1();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// �v���C���[�̈ʒu����X�N���[���ʂ����肷��
//	int GetScrollX();

	//�w�肵����`�Ɠ������Ă��邩����
	bool IsCollision(Rect rect, Rect& ChipRect);

private:
	Camera* m_pCamera;

	Player m_pPlayer;

	// �}�b�v�̃O���t�B�b�N�n���h��
    int m_handle001;
};

