#pragma once
#include "Vec2.h"

/// <summary>
/// ��`�̃f�[�^�Ǘ�
/// </summary>
class Rect
{
public:
	Rect();
	virtual ~Rect();

public:
	float m_left;   // �����X���W
	float m_top;    // �����Y���W
	float m_right;  // �E����X���W
	float m_bottom; // �E����Y���W

	float GetWidth() const { return m_right - m_left; }
	float GetHeight() const { return m_bottom - m_top; }

	// �e���W�擾
	Vec2 GetCenter();

	// ������(�d�Ȃ�)����
	bool IsCollision(const Rect& Rect);

	/// <summary>
	/// ������W�ƃT�C�Y����Rest�f�[�^��ݒ�
	/// </summary>
	/// <param name="posTL">������W</param>
	/// <param name="size">�T�C�Y</param>
	void SetTlSize(Vec2 posTL, Vec2 size);
};


