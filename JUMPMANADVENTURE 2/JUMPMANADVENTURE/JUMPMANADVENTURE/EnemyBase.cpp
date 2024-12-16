#include "EnemyBase.h"

EnemyBase::EnemyBase()
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
}

void EnemyBase::Draw()
{
}

float EnemyBase::GetRadius()
{
    return 0.0f;
}

float EnemyBase::GetLeft()
{
    return 0.0f;
}

float EnemyBase::GetTop()
{
    return 0.0f;
}

float EnemyBase::GetRigth()
{
    return 0.0f;
}

float EnemyBase::GetBottom()
{
    return 0.0f;
}

bool EnemyBase::IsGetHitPlayer(std::shared_ptr<Player> pPlayer)
{
    return false;
}

bool EnemyBase::IsCollision(Rect rect, Rect& enemyRect)
{
    return false;
}
