#pragma once
#include "Vec2.h"

/// <summary>
/// ��`�Ǘ��N���X
/// </summary>
class Rect
{
public:
	Rect();
	virtual ~Rect();

	// �l�p�`�̕`��
	void Draw(unsigned int Color, bool isFill);
	// ������W�ƕ��������w��
	void SetLT(float left, float top, float width, float height);
	// ���S���W�ƕ��������w��
	void SetCenter(float x, float y, float width, float height);

	float GetWidth() const;  // ��`�̕�
	float GetHeight() const; // ��`�̍���
	Vec2 GetCenter() const;  // ��`�̒��S���W
	float GetLeft() const { return m_left; }     // ��`�̍���X���W
	float GetTop() const { return m_top; }       // ��`�̍���Y���W
	float GetRight() const { return m_right; }   // ��`�̉E��X���W
	float GetBottom() const { return m_bottom; } // ��`�̉E��Y���W

	// ��`���m�̓����蔻��
	bool IsCollision(const Rect& rect);

public:
	float m_left;    // �����X���W
	float m_top;     // �����Y���W
	float m_right;   // �E����X���W
	float m_bottom;  // �E����Y���W
};
 
