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

	void Init(Camera* pCamera);
	void Update();
	void Draw();

	// ���݂�HP���擾
	int GetHp() const { return m_hp; }

	// �v���C���[���_���[�W���󂯂����̏���
	void OnDamage();
 
	// �v���C���[���G��|�����㏭���W�����v
	void JumpOnEnemy();

	// �v���C���[�̈ʒu�����擾
	Vec2 GetPos() const { return m_pos; }
	// �v���C���[�̓����蔻����擾
//	Rect GetColRect() const { return m_colRect; }
	
    // �~�̓����蔻��
	float GetRadius() const;
	// �v���C���[�̈ړ��ʂ��擾
	float GetMoveY() const;

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// �}�b�v�`�b�v�Ƃ̓����蔻��
	void CheckHitBgStage1(Rect chipRect);

	// Y�������̈ړ��ʂ�ǉ�
	void AddMoveY(float DisY);

	// Y�������̈ړ��ʂ����Z�b�g
	void OnCollideY();

	// ���݂̃v���C���[�̋�`�����擾
	Rect GetRect() const;

	// �v���C���[���͈͓��ɂ��邩�`�F�b�N����
	bool IsPlayerInRange(float x, float y, float range);

private:
	// �W�����v����
	void UpdateJump();
	// �e��Ԗ���Update����
	void UpdateNormal();  // �Q�[������Update
	void UpdateDead();    // ���S���Update

	// ���S���̏���������
	void InitDead();     

private:
	Camera* m_pCamera;
	SceneMain* m_pMain;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;
	// �����蔻��p�̋�`
//	Rect m_colRect;

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
	int m_jumpFrame;   // �W�����v���̃t���[����
	bool m_isJump;     // �W�����v���Ă��邩�ǂ����t���O
	bool m_isAnimJump; // �v���C���[���W�����v�`�悵�Ă��邩�ǂ����̃t���O
	float m_jumpSpeed;

	// �E�Ɉړ����Ă��邩�ǂ����̃t���O
	bool m_isRightMove; 
	// ���Ɉړ����Ă��邩�ǂ����̃t���O
	bool m_isLeftMove;
	// �����Ă��邩�ǂ����t���O
	bool m_isWalk; // true:�����Ă��� false:�ҋ@
	// �L�������ǂ���������Ă��邩�̃t���O
	bool m_isAnimTurn;

	// �n�ʂƐڂ��Ă��邩�@true:�ڂ��Ă��� 
	bool m_isGround;

	// HP
	int m_hp;
	// �c�@
	int m_life;

	// �_��
	int m_blinkFrameCount;
	// ���S���o
	int m_deadFrameCount;
};

