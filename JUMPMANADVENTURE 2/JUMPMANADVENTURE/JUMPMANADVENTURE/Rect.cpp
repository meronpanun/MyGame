#include "Rect.h"

Rect::Rect() :
    m_left(0.0f),
    m_top(0.0f),
    m_right(0.0f),
    m_bottom(0.0f)
{
}

Rect::~Rect()
{
}

Vec2 Rect::GetCenter()
{
    return Vec2((m_left + m_right) / 2, (m_top + m_bottom) / 2);
}

bool Rect::IsCollision(const Rect& Rect)
{
    if (m_top > Rect.m_bottom) return false;
    if (m_bottom > Rect.m_top) return false;
    if (m_left > Rect.m_right) return false;
    if (m_right > Rect.m_left) return false;

    return true;
}

void Rect::SetTlSize(Vec2 posTL, Vec2 size)
{
    m_top = posTL.y;
    m_bottom = posTL.y + size.y;
    m_left = posTL.x;
    m_right = posTL.x + size.x;
}
