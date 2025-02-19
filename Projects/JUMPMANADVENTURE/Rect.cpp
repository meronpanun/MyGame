#include "Rect.h"

Rect::Rect() :
    m_left(0.0f),
    m_top(0.0f),
    m_right(0.0f),
    m_bottom(0.0f)
{
}

Rect::Rect(Vec2 posTL, Vec2 size)
{
    SetTopLeftSize(posTL, size);
}

Rect::~Rect()
{
}

/// <summary>
/// ���S���W�擾
/// </summary>
/// <returns>���S���W</returns>
Vec2 Rect::GetCenter()
{
    return Vec2((m_left + m_right) / 2, (m_top + m_bottom) / 2);
}

/// <summary>
/// ������(�d�Ȃ�)����
/// </summary>
/// <param name="rect">���肷���`</param>
/// <returns>�d�Ȃ��Ă��邩�ǂ���</returns>
bool Rect::IsCollision(const Rect& rect)
{
    if (m_top > rect.m_bottom) return false;
    if (m_bottom < rect.m_top) return false;
    if (m_left > rect.m_right) return false;
    if (m_right < rect.m_left) return false;

    return true;
}

/// <summary>
/// ������W�ƃT�C�Y����Rest�f�[�^��ݒ�
/// </summary>
/// <param name="posTL">������W</param>
/// <param name="size">�T�C�Y</param>
void Rect::SetTopLeftSize(Vec2 posTL, Vec2 size)
{
    m_top = posTL.y;
    m_bottom = posTL.y + size.y;
    m_left = posTL.x;
    m_right = posTL.x + size.x;
}
