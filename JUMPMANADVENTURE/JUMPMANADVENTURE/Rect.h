#pragma once
#include "Vec2.h"

/// <summary>
/// ��`�Ǘ��N���X
/// </summary>
class Rect
{
public:
	Rect();
	float GetWidth() const { return right - left; }
	float GetHeigth() const { return bottom - top; }

	// �e���W�擾
	Vec2 GetCenter();

	// �����蔻��
	bool isCol(const Rect& rect);
	/// <summary>
	/// ������W�ƃT�C�Y����Rect�f�[�^��ݒ�
	/// </summary>
	/// <param name="posTL">������W</param>
	/// <param name="size">�T�C�Y</param>
	void set_TL_Size(Vec2 posTL, Vec2 size);
public:
	float top;
	float bottom;
	float left;
	float right;



};

