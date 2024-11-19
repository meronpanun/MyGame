#pragma once
#include "Bg.h"
/// <summary>
/// �X�e�[�W1�̔w�i�N���X
/// </summary>
class BgStage1: public Bg
{
	BgStage1();
	virtual ~BgStage1();

	void Init();
	void Update();
	void Draw();

	// �w�i�`��
	void DrawBg();
	// �v���C���[�̈ʒu����X�N���[���ʂ��v�Z
	virtual int GetScrollX() override;
	virtual int GetScrollY() override;
	// �v���C���[�Ɠ������Ă��邩���肷��
	virtual bool IsColPlayer() override;
	// �w�肵����`�Ɠ������Ă��邩���肷��
	virtual bool IsCollision(Rect rect, Rect& chipRect) override;
};

