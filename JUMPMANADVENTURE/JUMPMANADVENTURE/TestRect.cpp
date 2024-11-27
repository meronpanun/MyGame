#include "TestRect.h"

Vec2 TestRect::getCenter()
{
    return Vec2((left + right) / 2, (top + bottom) / 2);
}

bool TestRect::isCol(const TestRect& testRect)
{
    if (top > testRect.bottom) return false;
    if (bottom > testRect.top) return false;
    if (left > testRect.right) return false;
    if (right > testRect.left) return false;

    return true;
}

void TestRect::set_TL_Size(Vec2 posTL, Vec2 size)
{
    top = posTL.y;
    bottom = posTL.y + size.y;
    left = posTL.x;
    right = posTL.x + size.x;
}
