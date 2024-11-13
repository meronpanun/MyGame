#pragma once
#include "Vec2.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Update();
	void Draw();


	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// �v���C���[�̈ʒu�����擾����
	Vec2 GetPos() const { return m_pos; }


private:
	// �O���t�B�b�N�n���h��
	int m_runHandle;
	int m_jumpHandle;

	// �A�j���[�V�����֘A
	int m_animFrame;   // �t���[�����𐔂���
	int m_walkFrameCount;

	// true:�����Ă���@false:�ҋ@
	bool m_isRun;
	// true:�������@false:�E����
	bool m_isDirLeft;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	
	//Dir m_dir;

	// �W�����v����
	bool m_isJump;	   // true : �W�����v�� false : �n�ʂɂ���
	bool m_isAnimJump; // true :  �`�悷��  false : �`�悵�Ȃ�
	float m_jumpSpeed;
};

