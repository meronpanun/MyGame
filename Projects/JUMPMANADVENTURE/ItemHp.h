#pragma once
#include "Rect.h"
#include <memory>

class Camera;
class Player;

/// <summary>
/// �A�C�e���N���X
/// </summary>
class ItemHp
{
public:
	ItemHp();
	 ~ItemHp();

	void Init(Camera* camera);
	void Update();
	void Draw() ;

	// �����o�[�ϐ��ɃA�N�Z�X���邽�߂̊֐� 
	void SetHandle(int handle) { m_handle = handle; }

	// �v���C���[�̃|�C���^���擾
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	// �A�C�e���̈ʒu��ݒ�
	void SetPos(float x, float y);

	// �A�C�e���������鏈��
	void ItemLost();

	// �A�C�e���̈ʒu���擾
	Vec2 GetPos() const { return m_pos; }

	// �A�C�e���̔��a���擾
	float GetRadius();

	// �A�C�e���ƃv���C���[�������������ǂ���
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	//  �A�C�e�������݂��邩�ǂ����𔻒�
	bool IsExist() const; 

private:
	// �A�C�e���̈ʒu
	Vec2 m_pos;

	Camera* m_pCamera;
	std::shared_ptr<Player> m_pPlayer;

	// �O���t�B�b�N�n���h��
	int m_handle;
	// �G�t�F�N�g�̃O���t�B�b�N�n���h��
	int m_effectHandle;

	// �A�j���[�V�����̃t���[��
	int m_animFrameCount;

	// �A�C�e���̑��݃t���O��ǉ�
	bool m_isExist;

	// �G�t�F�N�g�̃A�j���[�V�����t���[���J�E���g
	int m_effectAnimFrameCount;
	// �G�t�F�N�g���Đ������ǂ����̃t���O
	bool m_isEffectPlaying;
};

