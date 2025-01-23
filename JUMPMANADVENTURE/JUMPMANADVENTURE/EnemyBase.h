#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>
#include <memory>

class Player;
class BgStage1;
/// <summary>
/// �G�̊��N���X 
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

 	virtual void Init();
	virtual void Update();
	virtual void Draw();

	// �G�̈ʒu�����擾
	Vec2 GetPos() const { return m_pos; }

	// �~�̓����蔻��
	float GetRadius();

	// �G�̏㉺���E���擾
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// �v���C���[�Ƃ̓����蔻��
	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	// ���݂̓G�̋�`���
	Rect GetRect();

	//�w�肵����`�Ɠ������Ă��邩����
	bool IsCollision(Rect rect, Rect& enemyRect);

protected:
	std::shared_ptr<BgStage1> m_pBgStage1;
	std::shared_ptr<Player> m_pPlayer;

	// �\���ʒu
	Vec2 m_pos;

	// �O���t�B�b�N�̃n���h��
	int m_handle;
};

