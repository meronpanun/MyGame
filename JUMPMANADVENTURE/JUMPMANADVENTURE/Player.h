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
	// �v���C���[�̈ʒu�����擾����
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻��̎擾
	Rect GetColRect() const { return m_colRect; }

private:
	// �W�����v����
	void UpdateJump();

	// �v���C���[�̃A�j���[�V����
	void UpdatePlayerAnim();

	// �v���C���[�̕`��
	void DrawPlayer(int x, int y);

private:
	// �w�i
	Bg* m_pBg;
	SceneMain* m_pMain;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;
	// �����蔻��p�̋�`
	Rect m_colRect;

	// �O���t�B�b�N�n���h��
	int m_walkHandle;  // ����
	int m_jumpHandle; // �W�����v
	
	// �A�j���[�V�����̎�� 
	enum Anim
	{
		kWalk, // �ړ�
		kJump  // �W�����v
	};
	// ���݂̃A�j���[�V�������
	Anim m_animation;
	// �ړ��A�j���[�V����
	int m_walkAnimFrame;

	// �����֘A
	int m_animFrame;   // �t���[�����𐔂���
	int m_walkFrameCount;

	// true:�����Ă���@false:�ҋ@
	bool m_isWalk;
	// true:�������@false:�E����
	bool m_isDirLeft;
	// �n�ʂƐڂ��Ă��邩�ǂ���
	bool m_isGround; // true : �ڂ��Ă��� 

	//Dir m_dir;

	// �W�����v����
	bool m_isJump;	   // true : �W�����v�� false : �W�����v���Ă��Ȃ�
	bool m_isAnimJump; // true :  �`�悷��  false : �`�悵�Ȃ�
	float m_jumpSpeed;
	int m_jumpFrame;

	// �{�^���̏�Ԃ��擾����
	int m_keyState;
	// �{�^�������������ꂽ����
	int m_pressTime;
	// �{�^�����������ė����܂ł̎���
	int m_nowPressTime;

};

