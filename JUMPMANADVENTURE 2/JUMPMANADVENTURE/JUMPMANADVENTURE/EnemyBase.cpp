#include "EnemyBase.h"
#include "BgStage1.h"
#include "Player.h"
#include "DxLib.h"
#include <cmath>

namespace
{
    // �G�̃T�C�Y
    constexpr int kWidth = 20;
    constexpr int kHeight = 20;

    // �G�̕`��T�C�Y
    constexpr int kGraphWidth = 32;
    constexpr int kGraphHeight = 32;

    // �~�̓����蔻��̔��a
    constexpr int kRadius = 10;
}

EnemyBase::EnemyBase() :
    m_handle(-1),
    m_pos(0.0f, 0.0f)
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
    return kRadius;
}

float EnemyBase::GetLeft() const
{
    return m_pos.x - kWidth * 0.5f;
}

float EnemyBase::GetTop() const
{
    return m_pos.y - kHeight;
}

float EnemyBase::GetRigth() const
{
    return m_pos.x + kWidth * 0.5f;
}

float EnemyBase::GetBottom() const
{
    return m_pos.y;
}

bool EnemyBase::IsGetHitPlayer(std::shared_ptr<Player> pPlayer)
{
    // �v���C���[�ƓG�̔��a�̍��v
    float Rlength = kRadius + pPlayer->GetRadius();
    // X�����̋���
    float delX = pPlayer->GetPos().x - m_pos.x; 
    // Y�����̋���
    float delY = pPlayer->GetPos().y - m_pos.y;
    
    float del = sqrt((delX * delX) + (delY * delY));

    if (del <= Rlength)
    {
        return true;
    }

    return false;
}

Rect EnemyBase::GetRect()
{
    // �G�̋�`�����蔻����
    Rect rect;
    rect.m_top = GetTop();
    rect.m_bottom = GetBottom();
    rect.m_left = GetLeft();
    rect.m_right = GetRigth();
    return rect;
}

bool EnemyBase::IsCollision(Rect rect, Rect& enemyRect)
{
    // �G�̓����蔻��
    int enemyLeft = kWidth;
    int enemyRight = enemyLeft + kWidth;
    int enemyTop = kHeight;
    int enemyBottom = enemyTop + kHeight;

    // ��΂ɓ�����Ȃ��p�^�[�����͂���
    if (enemyLeft > rect.m_right) return false;
    if (enemyTop > rect.m_bottom) return false;
    if (enemyRight < rect.m_left) return false;
    if (enemyBottom < rect.m_top) return false;

    // �Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
    enemyRect.m_left = enemyLeft;
    enemyRect.m_right = enemyRight;
    enemyRect.m_top = enemyTop;
    enemyRect.m_bottom = enemyBottom;

    return true;
}
