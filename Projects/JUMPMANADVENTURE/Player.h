#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>

class Life;
class Camera;
class BgStage;
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

	/// <summary>
	/// ���݂�HP���擾
	/// </summary>
	/// <returns>HP</returns>
	int GetHp() const { return m_hp; }

	/// <summary>
	/// �v���C���[���_���[�W���󂯂����̏���
	/// </summary>
	void OnDamage();
 
	/// <summary>
	/// �v���C���[���G��|�����㏭���W�����v
	/// </summary>
	void JumpOnEnemy();

	/// <summary>
	/// �v���C���[�̈ʒu�����擾
	/// </summary>
	/// <returns></returns>
	Vec2 GetPos() const { return m_pos; }
	
	/// <summary>
	///  �~�̓����蔻��
	/// </summary>
	/// <returns>���a</returns>
	float GetRadius() const;

	/*�v���C���[�̏㉺���E���擾*/
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	/// <summary>
	/// �}�b�v�`�b�v�Ƃ̓����蔻��
	/// </summary>
	/// <param name="chipRect"></param>
	void CheckHitBgStage(Rect chipRect);
	
	/// <summary>
	/// �v���C���[�̈ړ��ʂ��擾
	/// </summary>
	/// <returns>Y�������̈ړ��ʂ��擾</returns>
	float GetMoveY() const;

	/// <summary>
	/// Y�������̈ړ��ʂ�ǉ� 
	/// </summary>
	/// <param name="DisY">Y�������̈ړ���</param>
	void AddMoveY(float DisY);

	/// <summary>
	/// Y�������̈ړ��ʂ����Z�b�g
	/// </summary>
	void OnCollideY();
	
	/// <summary>
	/// ���݂̃v���C���[�̋�`�����擾
	/// </summary>
	/// <returns>�v���C���[�̋�`���</returns>
	Rect GetRect() const;

	/// <summary>
	/// �Q�[���I�[�o�[���o���J�n����t���O
	/// </summary>
	/// <returns>true:�Q�[���I�[�o�[ false:�Q�[���I�[�o�[�łȂ�</returns>
	bool IsGameOver() const;

	/// <summary>
	///  �v���C���[�̑���𖳌���S
	/// </summary>
	void DisableControl();
	
	/// <summary>
	/// �v���C���[�̑��삪�������ǂ��� 
	/// </summary>
	/// <returns>true:���� false:�L��</returns>
	bool IsControlDisabled() const;

	/// <summary>
	/// �v���C���[�̈ʒu��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	void SetPosX(float x);

	/// <summary>
	/// �v���C���[���n�ʂɂ��邩�ǂ��� 
	/// </summary>
	/// <returns>true:�n�ʂɂ��� false:�n�ʂɂ��Ȃ�</returns>
	bool IsOnGround() const;

	/// <summary>
	/// �v���C���[��n�ʂ̍����܂ł�����藎�Ƃ�
	/// </summary>
	/// <param name="groundHeight"></param>
	void FallToGround(float groundHeight);
	
	/// <summary>
	/// �v���C���[�̕��s��Ԃ�ݒ肷��
	/// </summary>
	/// <param name="isWalking"></param>
	void SetIsWalking(bool isWalking);

	/// <summary>
	/// �v���C���[�̃A�j���[�V�������X�V����
	/// </summary>
	void UpdateAnimation();
	
	/// <summary>
	///  �_���[�W���󂯂����ǂ����������t���O
	/// </summary>
	/// <returns>true:�_���[�W���󂯂� false:�_���[�W���󂯂Ă��Ȃ�</returns>
	bool HasTakenDamage() const; 

	/// <summary>
	/// HP���񕜂���
	/// </summary>
	void RecoverHp(); 

private:
	/// <summary>
	///  �W�����v����
	/// </summary>
	void UpdateJump();

	/*�e��Ԗ���Update����*/
	/// <summary>
	/// �Q�[������Update
	/// </summary>
	void UpdateNormal(); 
	/// <summary>
	/// ���S���Update
	/// </summary>
	void UpdateDead();   

	/// <summary>
	///  ���S���̏���������
	/// </summary>
	void InitDead();

	/// <summary>
	///  �������X�|�[��
	/// </summary>
	void StartRespawn();
	/// <summary>
	/// ���X�|�[��
	/// </summary>
	void Respawn();

private:
	Camera* m_pCamera;
	SceneMain* m_pMain;
	std::shared_ptr<BgStage> m_pBgStage;
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
	int m_itemHpSEHandle;

	// �A�j���[�V�����̃t���[��
	int m_animFrame;
	// �A�j���[�V�����̃J�E���g
	int m_animCount;

	// �W�����v����
	int m_jumpCount;   // �W�����v�̃J�E���g
	int m_jumpFrame;   // �W�����v���̃t���[����
	bool m_isJump;     // �W�����v���Ă��邩�ǂ����t���O
	bool m_isAnimJump; // �v���C���[���W�����v�`�悵�Ă��邩�ǂ����̃t���O
	float m_jumpSpeed; // �W�����v���x

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

	// �_���[�W���󂯂����ǂ����������t���O
	bool m_hasTakenDamage;
};

