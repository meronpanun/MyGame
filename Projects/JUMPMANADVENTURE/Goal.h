#pragma once
#include "Vec2.h"
#include <memory>

class Camera;
class Player;
class BgStage;

/// <summary>
/// ゴールクラス
/// </summary>
class Goal
{
public:
	Goal();
	virtual ~Goal();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// メンバー変数にアクセスする
	void SetHandle(int handle) { m_handle = handle; }
	void SetPoleHandle(int poleHandle) { m_poleHandle = poleHandle; }

	// ゴールの位置情報を取得 
	Vec2 GetPos() const { return m_pos; }

	// プレイヤーとの当たり判定フラグを取得
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	// ポールの当たり判定のオフセットを設定
	void SetPoleCollisionOffset(float offsetX, float offsetY);

	// ポールの当たり判定サイズ
	void SetPoleCollisionSize(float width, float height);

	/// 旗の落ちる高さを設定
	void SetFlagFallHeight(int height); 

	// 旗が指定の高さまで落ちたかどうかを判定
	bool IsFlagFalling() const;
	
public:
	// 当たり判定の時間を設定
	int m_collisionTimer;
	// プレイヤーが当たったかどうか
	bool m_isPlayerCollided;

private:
	// ゴールの座標
	Vec2 m_pos;

	// ポールの当たり判定のオフセットとサイズ
	Vec2 m_poleCollisionOffset;
	Vec2 m_poleCollisionSize;

	Camera* m_pCamera;

	std::shared_ptr<BgStage> m_pStage1;
	std::shared_ptr<Player> m_pPlayer;
		
	// グラフィックハンドル
	int m_handle;
	int m_poleHandle;

	// アニメーション
	int m_animFrame;
	int m_index;

	// 旗が落ちるフラグ
	bool m_isFlagFalling;
	// 旗の位置
	int m_flagPosY;
	// 画面遷移用タイマー
	int m_transitionTimer;

	int m_score;
	int m_timer;

	// 旗の落ちる高さ
	int m_flagFallHeight; 


};

