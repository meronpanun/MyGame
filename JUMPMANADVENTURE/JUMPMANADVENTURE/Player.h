#pragma once
#include "Vec2.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBotton() const;

	int GetHp() const { return m_hp; }
	
	// �v���C���[�ƓG���Ԃ�����
	void OnDamage();

private:
	// ��ԕω����鎞�̏���
	void InitDead(); // ���S���o�̏�����

	void UpdateNormal();
	void UpdateDead();

private:
	// �O���t�B�b�N�n���h��
	int m_handleIdle;
	int m_handleRun;

	// �t���[�����𐔂���
	int m_animFrame;
	// true : �����Ă��� false : �ҋ@
	bool m_isRun;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// true : ������ false: �E����
	bool m_isDirLeft;

	// �W�����v����
	bool m_isJump;
	float m_jumpSpeed;

	// �_��
	int m_blinkFrameCount;

	// �v���C���[��HP
	int m_hp;

	// ���S���o
	int m_deadFrameCount;
};

