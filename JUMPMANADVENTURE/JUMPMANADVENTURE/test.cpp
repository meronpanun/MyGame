
// �v���C���[�̎��S���o���I�������Q�[���I�[�o�[���o���n�܂�悤�ɂ��Ă�������
//void Player::JumpOnEnemy()
//{
//    m_move.y = kJumpAcc * 0.5f; // ����Y�������ɃW�����v
//    m_isJump = true;
//    m_isGround = false;
//}
//
//float Player::GetRadius() const
//{
//    return kRadius;
//}
//
//float Player::GetLeft() const
//{
//    return m_pos.x - (kGraphWidth * kScale * 0.5f);
//}
//
//float Player::GetTop() const
//{
//    return m_pos.y - kGraphHeight * kScale;
//}
//
//float Player::GetRigth() const
//{
//    return m_pos.x + (kGraphWidth * kScale * 0.5f);
//}
//
//float Player::GetBottom() const
//{
//    return m_pos.y;
//}
//
//void Player::CheckHitBgStage1(Rect chipRect)
//{
//    // ���̓����蔻��
//    m_pos.x += m_move.x;
//    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
//    {
//        if (m_move.x > 0.0f) // �v���C���[���E�����Ɉړ����Ă���
//        {
//            m_pos.x = chipRect.m_left - kGraphWidth * kScale * 0.5f - 1; // �����̕␳
//        }
//        else if (m_move.x < 0.0f) // �v���C���[���������Ɉړ����Ă���
//        {
//            m_pos.x = chipRect.m_right + kGraphWidth * kScale * 0.5f + 1; // �E���̕␳
//        }
//    }
//
//    // �c�̓����蔻��
//    m_pos.y += m_move.y;
//    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
//    {
//        if (m_move.y > 0.0f) // �v���C���[���������Ɉړ����Ă���
//        {
//            // ���n
//            m_pos.y = chipRect.m_top - 1;
//            m_move.y = 0.0f;
//            m_isJump = false;
//            m_isAnimJump = false;
//            m_isGround = true;
//        }
//        else if (m_move.y < 0.0f) // �v���C���[��������Ɉړ����Ă���
//        {
//            m_pos.y = chipRect.m_bottom + kGraphHeight * kScale + 1; // �߂荞�܂Ȃ��ʒu�ɕ␳
//            m_move.y *= -1.0f; // ������ւ̉������������ɕϊ�
//        }
//    }
//    else
//    {
//        // �n�ʂɂ��瓖�����Ă��Ȃ�
//        m_isJump = true;
//    }
//}
//
//void Player::AddMoveY(float DisY)
//{
//    m_pos.y += DisY;
//}
//
//void Player::OnCollideY()
//{
//    m_move.y = 0;
//}
//
//Rect Player::GetRect() const
//{
//    // �v���C���[�̋�`�����蔻����
//    Rect rect;
//    rect.m_top = GetTop();
//    rect.m_bottom = GetBottom();
//    rect.m_left = GetLeft();
//    rect.m_right = GetRigth();
//    return rect;
//}
//
//float Player::GetMoveY() const
//{
//    return m_move.y;
//}
//
//void Player::UpdateJump()
//{
//    m_jumpFrame++;
//    // �W�����v����
//    if (Pad::IsRelase(PAD_INPUT_1))
//    {
//        //�@�W�����v�̍��������߂�
//        float jumpHeight;
//
//        if (m_jumpFrame < kPressShortJumpFrame)
//        {
//            jumpHeight = kLittleJumpHeight;
//        }
//        else if (m_jumpFrame < kPressMediumJumpFrame)
//        {
//            jumpHeight = kInJumpHeight;
//        }
//        else
//        {
//            jumpHeight = kLittleJumpHeight;
//        }
//        m_move.y *= jumpHeight;
//    }
//}