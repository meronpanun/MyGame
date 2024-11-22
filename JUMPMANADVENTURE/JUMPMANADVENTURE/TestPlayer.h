#pragma once
#include <memory>
#include "Rect.h"

class BgStage1;
/// <summary>
/// �e�X�g�v���C���[�N���X
/// </summary>
class TestPlayer
{
public:
	TestPlayer();
	virtual ~TestPlayer();

	void Init();
	void Update();
	void Draw();

	// �v���C���[�̈ʒu�����擾
	float GetX() const { return m_posX; }
	float GetY() const { return m_posY; }
	
	// �~�̓����蔻��
	float GetRadius();

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// ���݂̃v���C���[�̋�`�����擾
	Rect getRect();

private:
	// �v���C���[�n���h��
	int m_playerHandle01;
	int m_playerHandle02;

	// �v���C���[�̑�����������Ƃ������W
	float m_posX;
	float m_posY;

};

