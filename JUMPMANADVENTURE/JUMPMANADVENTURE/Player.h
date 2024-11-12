#pragma once
#include "Vec2.h"
#include <memory>

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	// �g�p����O���t�B�b�N��ݒ肷��
//	void SetHandle(int handle) { m_handle = handle; }

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

	void UpdateNormal();  // �Q�[������Update

private:
	//enum Dir
	//{
	//	kDirDown,	// ������
	//	kDirLeft,	// ������
	//	kDirRight,	// �E����
	//	kDirUp,		// �����
	//};

private:
	// �O���t�B�b�N�n���h��
	int m_runHandle;
	int m_jumpHandle;

	// �A�j���[�V�����֘A
	int m_animFrame;   // �t���[�����𐔂���
	// true:�����Ă���@false:�ҋ@
	bool m_isRun;
	// true:�������@false:�E����
	bool m_isDirLeft;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	//Dir m_dir;

	// �W�����v����
	bool m_isJump;
	float m_jumpSpeed;

	int m_walkFrameCount;
};

