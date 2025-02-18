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

	/// <summary>
	/// �����o�[�ϐ��ɃA�N�Z�X���邽�߂̊֐� 
	/// </summary>
	/// <param name="handle">�O���t�B�b�N�n���h��</param>
	void SetHandle(int handle) { m_handle = handle; }

	/// <summary>
	/// �v���C���[�̃|�C���^���擾
	/// </summary>
	/// <returns>�v���C���[�̃|�C���^</returns>
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	/// <summary>
	/// �A�C�e���̈ʒu��ݒ�
	/// </summary>
	/// <param name="x">X���W</param>
	/// <param name="y">Y���W</param>
	void SetPos(float x, float y);

	/// <summary>
	/// �A�C�e���������鏈��
	/// </summary>
	void ItemLost();

	/// <summary>
	/// �A�C�e���̈ʒu���擾
	/// </summary>
	//// <returns>�A�C�e���̈ʒu</returns>
	Vec2 GetPos() const { return m_pos; }

	//�A�C�e���̔��a���擾

	/// <summary>
	/// �A�C�e���̔��a���擾
	/// </summary>
	/// <returns>���a</returns>
	float GetRadius();

	/// <summary>
	/// �A�C�e���ƃv���C���[�������������ǂ���
	/// </summary>
	/// <param name="pPlayer">�v���C���[�̃|�C���^</param>
	/// <returns>�����������ǂ���</returns>
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	/// <summary>
	///  �A�C�e�������݂��邩�ǂ����𔻒�
	/// </summary>
	/// <returns></returns>
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

