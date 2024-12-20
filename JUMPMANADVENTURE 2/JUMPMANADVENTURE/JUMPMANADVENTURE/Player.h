#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Camera;
class BgStage1;
class SceneMain;
/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	 ~Player();

	void Init(Camera* camera);
	void Update();
	void Draw();



	// �v���C���[�̈ʒu�����擾
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾
//	Rect GetColRect() const { return m_colRect; }
	
    // �~�̓����蔻��
	float GetRadius();

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	void CheckHitBgStage1(Rect chipRect);

	// ���݂̃v���C���[�̋�`�����擾
	Rect GetRect();


private:
	// �W�����v����
	void UpdateJump();

private:
	Camera* m_pCamera;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;
	// �����蔻��p�̋�`
//	Rect m_colRect;

//	BgStage1* m_pBgStage1;
	std::shared_ptr<BgStage1> m_pBgStage1;

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
	// �����Ă��邩�ǂ����t���O
	bool m_isWalk; // true:�����Ă��� false:�ҋ@
	// �L�������ǂ���������Ă��邩�̃t���O
	bool m_isAnimTurn;
};

