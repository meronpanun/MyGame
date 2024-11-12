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

	void SetHandle(int handle) { m_handle = handle; }

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;

private:
	// �O���t�B�b�N�n���h��
	int m_handle;

	// true : �����Ă��� false : �ҋ@
	bool m_isRun;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// true : ������ false: �E����
	bool m_isDirLeft;

	// �W�����v����
	bool m_isJump;
	float m_jumpSpeed;

	int m_walkFrameCount;
};

