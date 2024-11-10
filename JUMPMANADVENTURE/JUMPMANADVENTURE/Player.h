#pragma once
#include "Vec2.h"

/// <summary>
/// �v���C���[�N���X
/// </summary>
class Player
{
public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();

	// �v���C���[�̏㉺���E���擾
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBotton() const;

	int GetHp() const { return m_hp; }


private:
	// �v���C���[��HP
	int m_hp;
};

