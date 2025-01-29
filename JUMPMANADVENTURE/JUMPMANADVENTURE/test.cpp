
// プレイヤーの死亡演出が終わった後ゲームオーバー演出が始まるようにしてください
//void Player::JumpOnEnemy()
//{
//    m_move.y = kJumpAcc * 0.5f; // 少しY軸方向にジャンプ
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
//    // 横の当たり判定
//    m_pos.x += m_move.x;
//    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
//    {
//        if (m_move.x > 0.0f) // プレイヤーが右方向に移動している
//        {
//            m_pos.x = chipRect.m_left - kGraphWidth * kScale * 0.5f - 1; // 左側の補正
//        }
//        else if (m_move.x < 0.0f) // プレイヤーが左方向に移動している
//        {
//            m_pos.x = chipRect.m_right + kGraphWidth * kScale * 0.5f + 1; // 右側の補正
//        }
//    }
//
//    // 縦の当たり判定
//    m_pos.y += m_move.y;
//    if (m_pBgStage1->IsCollision(GetRect(), chipRect))
//    {
//        if (m_move.y > 0.0f) // プレイヤーが下方向に移動している
//        {
//            // 着地
//            m_pos.y = chipRect.m_top - 1;
//            m_move.y = 0.0f;
//            m_isJump = false;
//            m_isAnimJump = false;
//            m_isGround = true;
//        }
//        else if (m_move.y < 0.0f) // プレイヤーが上方向に移動している
//        {
//            m_pos.y = chipRect.m_bottom + kGraphHeight * kScale + 1; // めり込まない位置に補正
//            m_move.y *= -1.0f; // 上方向への加速を下方向に変換
//        }
//    }
//    else
//    {
//        // 地面にすら当たっていない
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
//    // プレイヤーの矩形当たり判定情報
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
//    // ジャンプ処理
//    if (Pad::IsRelase(PAD_INPUT_1))
//    {
//        //　ジャンプの高さを決める
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