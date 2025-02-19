#pragma once
#include "Vec2.h"
#include <memory>

class Camera;
class Player;
class BgStage;

/// <summary>
/// �S�[���N���X
/// </summary>
class Goal
{
public:
	Goal();
	virtual ~Goal();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// �����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }
	void SetPoleHandle(int poleHandle) { m_poleHandle = poleHandle; }

	// �S�[���̈ʒu�����擾 
	Vec2 GetPos() const { return m_pos; }

	// �v���C���[�Ƃ̓����蔻��t���O���擾
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	// �|�[���̓����蔻��̃I�t�Z�b�g��ݒ�
	void SetPoleCollisionOffset(float offsetX, float offsetY);

	// �|�[���̓����蔻��T�C�Y
	void SetPoleCollisionSize(float width, float height);

	/// ���̗����鍂����ݒ�
	void SetFlagFallHeight(int height); 

	// �����w��̍����܂ŗ��������ǂ����𔻒�
	bool IsFlagFalling() const;
	
public:
	// �����蔻��̎��Ԃ�ݒ�
	int m_collisionTimer;
	// �v���C���[�������������ǂ���
	bool m_isPlayerCollided;

private:
	// �S�[���̍��W
	Vec2 m_pos;

	// �|�[���̓����蔻��̃I�t�Z�b�g�ƃT�C�Y
	Vec2 m_poleCollisionOffset;
	Vec2 m_poleCollisionSize;

	Camera* m_pCamera;

	std::shared_ptr<BgStage> m_pStage1;
	std::shared_ptr<Player> m_pPlayer;
		
	// �O���t�B�b�N�n���h��
	int m_handle;
	int m_poleHandle;

	// �A�j���[�V����
	int m_animFrame;
	int m_index;

	// ����������t���O
	bool m_isFlagFalling;
	// ���̈ʒu
	int m_flagPosY;
	// ��ʑJ�ڗp�^�C�}�[
	int m_transitionTimer;

	int m_score;
	int m_timer;

	// ���̗����鍂��
	int m_flagFallHeight; 


};

