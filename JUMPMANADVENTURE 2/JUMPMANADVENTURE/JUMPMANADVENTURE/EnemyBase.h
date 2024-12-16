#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>
#include <memory>

class Player;
class SceneMain;

/// <summary>
/// �G�̊��N���X 
/// </summary>
class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();

	void Init();
	void Update();
	void Draw();

	// �~�̓����蔻��
	float GetRadius();

	// �G�̏㉺���E���擾
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// �v���C���[�Ƃ̓����蔻��
	bool IsGetHitPlayer(std::shared_ptr<Player> pPlayer);

	// ���݂̓G�@�̋�`���
	Rect GetRect;

	//�w�肵����`�Ɠ������Ă��邩����
	bool IsCollision(Rect rect, Rect& enemyRect);

protected:
	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// �\���ʒu
	Vec2 m_pos;
};

