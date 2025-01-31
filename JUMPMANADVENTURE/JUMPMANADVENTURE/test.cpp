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
//// 敵の初期化
//for (auto& enemy : m_pEnemy)
//{
//	if (enemy)
//	{
//		enemy->Init(m_pCamera.get());
//	}
//}
//
//// 体力の初期化
//m_life.resize(kMaxHp);
//for (int i = 0; i < m_life.size(); i++)
//{
//	m_life[i].Init();
//	m_life[i].SetHandle(m_lifeHandle);
//	m_life[i].SetIndex(i);
//}
//
//// BGMの再生開始（ループ再生）
//PlaySoundMem(m_bgmHandle, DX_PLAYTYPE_LOOP);
//
//// スコアとタイマーの初期化
//m_score = 0;
//m_timer = kInitialTimer;

//サウンドの大きさ設定
//ChangeVolumeSoundMem(kVolumeBGM, m_bgmHandle);
//ChangeVolumeSoundMem(kVolumeSE, m_seHandle);
//
//// ゴールに当たったかどうか
//m_isGoalHit = m_pGoal->GetHitPlayerFlag(m_pPlayer);
//
//if (m_isGameEnd)
//{
//	// ゲームオーバーになった後1ボタンを押したらフェードアウト
//	m_fadeFrameCount--;
//	if (m_fadeFrameCount < 0)
//	{
//		m_fadeFrameCount = 0;
//		return new SceneTitle();
//	}
//}
//else
//{
//	// フェードイン処理
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

// プレイヤーが死亡状態でない場合のみ敵の更新とタイマーの更新を行う
//if (m_pPlayer->GetHp() > 0)
//{
//	// 敵の更新
//	Vec2 playerPos = m_pPlayer->GetPos();
//	for (auto& enemy : m_pEnemy)
//	{
//		if (enemy && enemy->IsAlive())
//		{
//			if (enemy->IsPlayerInRange(playerPos, kEnemyActivationRange))
//			{
//				enemy->Activate(); // 敵をアクティブにする
//			}
//			if (enemy->IsActive())
//			{
//				enemy->Update();   // アクティブな敵を更新
//			}
//		}
//	}
//
//	// タイマーのカウントダウン
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
//	// 体力の更新
//	for (int i = 0; i < m_life.size(); i++)
//	{
//		m_life[i].Update();
//	}
//
//	// プレイヤーと敵の当たり判定
//	for (auto& enemy : m_pEnemy)
//	{
//		if (enemy && enemy->IsAlive())
//		{
//			bool isPlayerHit = true;
//			// 絶対に当たらないパターン
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
//			// isPlayerHit = trueなら当たっている、falseなら当たっていない
//			if (isPlayerHit)
//			{
//				if (m_pPlayer->GetBottom() < enemy->GetTop() + 50 && m_pPlayer->GetMoveY() > 0) // プレイヤーが敵の上に当たった場合
//				{
//					enemy->SetAlive(false);    // 敵を消す
//					m_pPlayer->JumpOnEnemy();  // プレイヤーが少しジャンプ
//					m_score += 100;            // 敵を倒すとスコアを100ポイント増加
//					// SEを再生
//				//	PlaySoundMem(m_seHandle, DX_PLAYTYPE_BACK);
//				}
//				else
//				{
//					m_pPlayer->OnDamage();	   // プレイヤーがダメージを受ける
//				}
//			}
//		}
//	}
//}
//
//// 1秒サイクルで表示、非表示切り替えす
//m_blinkFrameCount++;
//if (m_blinkFrameCount >= kBlinkCycleFrame)
//{
//	m_blinkFrameCount = 0;
//}