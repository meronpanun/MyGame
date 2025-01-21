#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Player;
class BgStage1;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	void Init();
	void Update();
	void Draw();

	// �G�̏㉺���E���擾
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// ���݂̓G�̋�`���
	Rect GetRect();

	// �v���C���[�Ƃ̓����蔻��
	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	enum Dir
	{
		kRunRight,
		kRunLeft
	};

private:
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;

	Vec2 m_pos;
	// �G�̉����x
	Vec2 m_move;

	bool m_isturnFlag;

	// �����Ă������
	Dir m_dir;
	bool m_isAnimRight;
	bool m_isAnimLeft;

	// �A�j���[�V�����̃t���[��
	int m_animFrame;
	// �A�j���[�V�����̃J�E���g
	int m_animCount;
	// �G�̃O���t�B�b�N�n���h��
	int m_handle;
};

