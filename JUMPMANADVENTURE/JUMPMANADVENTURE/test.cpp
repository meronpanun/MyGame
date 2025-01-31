//m_pPlayer = std::make_shared<Player>();
//m_pBgStage1 = std::make_shared<BgStage1>();
//m_pCamera = std::make_shared<Camera>();
//m_pFont = std::make_shared<FontManager>();
//
//m_pPlayer->Init(m_pCamera.get());
//m_pBgStage1->Init(m_pCamera.get());
//m_pCamera->Init();
//m_pGoal->Init(m_pCamera.get());
//
//// �G�̏�����
//for (auto& enemy : m_pEnemy)
//{
//	if (enemy)
//	{
//		enemy->Init(m_pCamera.get());
//	}
//}
//
//// �̗͂̏�����
//m_life.resize(kMaxHp);
//for (int i = 0; i < m_life.size(); i++)
//{
//	m_life[i].Init();
//	m_life[i].SetHandle(m_lifeHandle);
//	m_life[i].SetIndex(i);
//}
//
//// BGM�̍Đ��J�n�i���[�v�Đ��j
//PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
//
//// �X�R�A�ƃ^�C�}�[�̏�����
//m_score = 0;
//m_timer = kInitialTimer;

//�T�E���h�̑傫���ݒ�
//ChangeVolumeSoundMem(kVolumeBGM, m_bgmHandle);
//ChangeVolumeSoundMem(kVolumeSE, m_seHandle);
//
//// �S�[���ɓ����������ǂ���
//m_isGoalHit = m_pGoal->GetHitPlayerFlag(m_pPlayer);
//
//if (m_isGameEnd)
//{
//	// �Q�[���I�[�o�[�ɂȂ�����1�{�^������������t�F�[�h�A�E�g
//	m_fadeFrameCount--;
//	if (m_fadeFrameCount < 0)
//	{
//		m_fadeFrameCount = 0;
//		return new SceneTitle();
//	}
//}
//else
//{
//	// �t�F�[�h�C������
//	m_fadeFrameCount++;
//	if (m_fadeFrameCount > 30)
//	{
//		m_fadeFrameCount = 30;
//	}
//}
//
//m_pPlayer->Update();
//m_pBgStage1->Update(m_pPlayer.get());
//m_pCamera->Update(m_pPlayer.get());
//m_pGoal->Update();

// �v���C���[�����S��ԂłȂ��ꍇ�̂ݓG�̍X�V�ƃ^�C�}�[�̍X�V���s��
//if (m_pPlayer->GetHp() > 0)
//{
//	// �G�̍X�V
//	Vec2 playerPos = m_pPlayer->GetPos();
//	for (auto& enemy : m_pEnemy)
//	{
//		if (enemy && enemy->IsAlive())
//		{
//			if (enemy->IsPlayerInRange(playerPos, kEnemyActivationRange))
//			{
//				enemy->Activate(); // �G���A�N�e�B�u�ɂ���
//			}
//			if (enemy->IsActive())
//			{
//				enemy->Update();   // �A�N�e�B�u�ȓG���X�V
//			}
//		}
//	}
//
//	// �^�C�}�[�̃J�E���g�_�E��
//	static int timerFrameCount = 0;
//	timerFrameCount++;
//	if (timerFrameCount >= kTimerCountdownInterval)
//	{
//		timerFrameCount = 0;
//		if (m_timer > 0)
//		{
//			m_timer--;
//		}
//	}
//
//	// �̗͂̍X�V
//	for (int i = 0; i < m_life.size(); i++)
//	{
//		m_life[i].Update();
//	}
//
//	// �v���C���[�ƓG�̓����蔻��
//	for (auto& enemy : m_pEnemy)
//	{
//		if (enemy && enemy->IsAlive())
//		{
//			bool isPlayerHit = true;
//			// ��΂ɓ�����Ȃ��p�^�[��
//			if (m_pPlayer->GetLeft() > enemy->GetRigth())
//			{
//				isPlayerHit = false;
//			}
//			if (m_pPlayer->GetTop() > enemy->GetBottom())
//			{
//				isPlayerHit = false;
//			}
//			if (m_pPlayer->GetRigth() < enemy->GetLeft())
//			{
//				isPlayerHit = false;
//			}
//			if (m_pPlayer->GetBottom() < enemy->GetTop())
//			{
//				isPlayerHit = false;
//			}
//
//			// isPlayerHit = true�Ȃ瓖�����Ă���Afalse�Ȃ瓖�����Ă��Ȃ�
//			if (isPlayerHit)
//			{
//				if (m_pPlayer->GetBottom() < enemy->GetTop() + 50 && m_pPlayer->GetMoveY() > 0) // �v���C���[���G�̏�ɓ��������ꍇ
//				{
//					enemy->SetAlive(false);    // �G������
//					m_pPlayer->JumpOnEnemy();  // �v���C���[�������W�����v
//					m_score += 100;            // �G��|���ƃX�R�A��100�|�C���g����
//					// SE���Đ�
//				//	PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
//				}
//				else
//				{
//					m_pPlayer->OnDamage();	   // �v���C���[���_���[�W���󂯂�
//				}
//			}
//		}
//	}
//}
//
//// 1�b�T�C�N���ŕ\���A��\���؂�ւ���
//m_blinkFrameCount++;
//if (m_blinkFrameCount >= kBlinkCycleFrame)
//{
//	m_blinkFrameCount = 0;
//}