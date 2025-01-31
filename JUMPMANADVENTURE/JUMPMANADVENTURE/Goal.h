#pragma once
#include "Vec2.h"
#include <memory>

class Camera;
class Player;
class BgStage1;
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

	// �S�[���̔��a���擾
	float GetRadius() const;

	// �v���C���[�Ƃ̓����蔻��t���O
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

private:
	// �S�[���̍��W
	Vec2 m_pos;

	Camera* m_pCamera;

	std::shared_ptr<BgStage1> m_pStage1;
	std::shared_ptr<Player> m_pPlayer;
		
	// �O���t�B�b�N�n���h��
	int m_handle;
	int m_poleHandle;

	// �A�j���[�V����
	int m_animFrame;

	int m_index;
};

