#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Camera;
class Player;
class BgStage1;
class Enemy
{
public:
	Enemy();
	 ~Enemy();

	void Init(Camera* camera);
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
//	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	// �G�̐����t���O
	void SetAlive(bool isAlive);

	// �G�̈ʒu��ݒ�
	void SetPos(float x, float y);

	// �G�������Ă��邩�ǂ����̃t���O
	bool IsAlive() const;

	enum Dir
	{
		kRunRight,
		kRunLeft
	};

private:
	Camera* m_pCamera;

	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;

	// �G�̈ʒu
	Vec2 m_pos;
	// �G�̉����x
	Vec2 m_move;

	bool m_isturnFlag;

	// �G�l�~�[�������Ă��邩�ǂ����̃t���O
	bool m_isAlive;

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


//class Enemy
//{
//public:
//	Enemy();
//	~Enemy();
//
//	void Init(Camera* camera);
//	void Update();
//	void Draw();
//	void SetAlive(bool alive);
//	bool IsAlive() const;
//
//	// �V�������\�b�h��ǉ�
//	void SetPos(float x, float y);
//
//	float GetLeft() const;
//	float GetRight() const;
//	float GetTop() const;
//	float GetBottom() const;
//
//private:
//	Vec2 m_pos;
//	bool m_isAlive;
//	Camera* m_pCamera;
//};

