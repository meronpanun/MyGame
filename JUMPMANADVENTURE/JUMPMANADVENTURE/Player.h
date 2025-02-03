#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>

class Life;
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

	// �Q�[���I�[�o�[���o���J�n����t���O
	bool IsGameOver() const;

	// �������X�|�[��
	void StartRespawn();
	void Respawn();

	// �v���C���[�̑���𖳌���
	void DisableControl();
	bool IsControlDisabled() const;

	// �v���C���[�̈ʒu��ݒ�
	void SetPosX(float x);

	// �v���C���[���n�ʂɂ��邩�ǂ���
	bool IsOnGround() const;

	// �v���C���[��n�ʂ̍����܂ł�����藎�Ƃ�
	void FallToGround(float groundHeight);

	// �v���C���[�̕��s��Ԃ�ݒ肷��
	void SetIsWalking(bool isWalking);

	// �v���C���[�̃A�j���[�V�������X�V����
	void UpdateAnimation();

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
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::vector<Life> m_Life;

	// �v���C���[�̈ʒu
	Vec2 m_pos;
	// �ړ���
	Vec2 m_move;

	// �L�����N�^�[�̃O���t�B�b�N�n���h��
	int m_walkHandle;
	int m_jumpHandle;
	// SE
	int m_seHandle;
	int m_jumpSEHandle;
	int m_damageSEHandle;
	int m_playerDeadSEHandle;

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

	// �Q�[���I�[�o�[���o���J�n����t���O
	bool m_isGameOver;

	// �n�ʂƐڂ��Ă��邩�@true:�ڂ��Ă��� 
	bool m_isGround;

	// �v���C���[�̗̑�
	int m_hp;
	int m_life;

	// �_��
	int m_blinkFrameCount;
	// ���S���o
	int m_deadFrameCount;

	// ���X�|�[���x��
	int m_respawnTimer;

	// ���얳����
	bool m_isControlDisabled;

	// �v���C���[�̍���
	float m_height;
};

