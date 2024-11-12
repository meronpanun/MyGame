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
	virtual ~Player();

	void Init();
	void Update();
	void Draw();

	// �~�̓����蔻��
	float GetRadius();

	// �v���C���[�̏㉺���E���擾
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();



private:
	Vec2 m_pos;

	enum Dir // �����Ă������	
	{
		kNutral, // �ʏ���
		kWalk,   // ����
		kNo,
		kFall,
		kDash,
	};

	// �O���t�B�b�N�n���h��
	int m_runHandle;
	int m_jumpHandle;

	int m_jumpCount = 0;

	// true : �󒆂ɂ��� false : �n�ʂɗ����Ă���
	bool m_isJump;

	// �E�Ɉړ����Ă��邩�ǂ����̃t���O
	bool m_isRight;

	// ���Ɉړ����Ă��邩�ǂ����̃t���O
	bool m_isLeft;

	// ���삵�Ă��邩�ǂ����̃t���O
	bool m_isCommand;

	// �v���C���[�̑�����������Ƃ������W
	float m_posX;
	float m_posY;

	// �v���C���[�̉����x
	float m_moveX;
	float m_moveY;

	// �����Ă������
	Dir m_dir;

	// �v���C���[���ǂ���������Ă��邩�̃t���O
	bool m_isAnimTrun;
	// �v���C���[���W�����v�`�悳��Ă邩�ǂ����̃t���O
	bool m_isAnimJump;

	// �A�j���[�V�����֘A
	int m_animFrame; // �A�j���[�V�����̃t���[�����𐔂���
	int m_animCount; // �A�j���[�V�����̃J�E���g

	
};

