#pragma once
#include <memory>
#include "Rect.h"
#include "Vec2.h"

class Map;
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

	// �v���C���[�̈ʒu�����擾
//	Vec2 GetPos() const { return m_pos; }

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	void CheckHitMap(Rect chipRect);

	// ���݂̃v���C���[�̋�`�����擾
	Rect getRect();


private:
	// �W�����v����
	void UpdateJump();

private:
	//  �X�N���[���ʂ��擾���邽�߂�Map�N���X���̎擾
	std::shared_ptr<Map> m_pMap;

	// �v���C���[�̈ʒu
	Vec2 m_pos;

	// �ړ���
	Vec2 m_move;

	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_walkHandle;
	int m_jumpHandle;

	// �A�j���[�V�����̃t���[��
	int m_animFrame;
	// �A�j���[�V�����̃J�E���g
	int m_animCount;

	// �W�����v����
	int m_jumpCount; 
	int m_jumpFrame;
	bool m_isJump;     // �W�����v���Ă��邩�ǂ����t���O
	bool m_isAnimJump; // �v���C���[���W�����v�`�悵�Ă��邩�ǂ����̃t���O

	// �E�Ɉړ����Ă��邩�ǂ����̃t���O
	bool m_isRight; 
	// ���Ɉړ����Ă��邩�ǂ����̃t���O
	bool m_isLeft;
	// �n�ʂɂ��Ă��邩�ǂ����t���O
	bool m_isGround;
	// �����Ă��邩�ǂ����t���O
	bool m_isWalk; // true:�����Ă��� false:�ҋ@
	// �L�������ǂ���������Ă��邩�̃t���O
	bool m_isAnimTurn;
};

