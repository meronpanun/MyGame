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

	void SetPos(float x, float y);

	// �A�C�e���������鏈��
	void ItemLost();

	// �A�C�e���̈ʒu
	Vec2 GetPos() const { return m_pos; }

	//�A�C�e���̔��a���擾
	float GetRadius();

	// �A�C�e���ƃv���C���[�������������ǂ���
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	// �A�C�e�������݂��邩�ǂ����𔻒�
	bool IsExist() const; 

private:
	// �A�C�e���̈ʒu
	Vec2 m_pos;

	Camera* m_pCamera;
	std::shared_ptr<Player> m_pPlayer;

	// �A�j���[�V�����̃t���[��
	int m_animFrameCount;
	
	// �O���t�B�b�N�n���h��
	int m_handle;

	// �A�C�e���̑��݃t���O��ǉ�
	bool m_isExist;
};

