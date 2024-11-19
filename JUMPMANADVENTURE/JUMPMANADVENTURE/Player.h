#pragma once
#include "Vec2.h"
#include "Rect.h"

class SceneMain;
class Bg;

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	 ~Player();

	void Init(Bg* bg, SceneMain* pMain, Vec2 initPos);
	void Update();
	void Draw();


	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	void CheckHitMap(Rect chipRect);

public:
	void UpdateJump();
	// �v���C���[�̈ʒu�����擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻��̎擾
	Rect GetColRect() const { return m_colRect; }

private:
	// �w�i
	Bg* m_pBg;
	SceneMain* m_pMain;

	// �O���t�B�b�N�n���h��
	int m_runHandle;
	int m_jumpHandle;

	// �����֘A
	int m_animFrame;   // �t���[�����𐔂���
	int m_walkFrameCount;

	// true:�����Ă���@false:�ҋ@
	bool m_isRun;
	// true:�������@false:�E����
	bool m_isDirLeft;
	// �n�ʂƐڂ��Ă��邩�ǂ���
	bool m_isGround; // true : �ڂ��Ă��� 

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;
	// �����蔻��p�̋�`
	Rect m_colRect;

	//Dir m_dir;

	// �W�����v����
	bool m_isJump;	   // true : �W�����v�� false : �W�����v���Ă��Ȃ�
	bool m_isAnimJump; // true :  �`�悷��  false : �`�悵�Ȃ�
	float m_jumpSpeed;
	int m_jumpFrame;
};

