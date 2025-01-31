#pragma once
#include "Vec2.h"
#include <memory>

class Camera;
class Player;
class BgStage1;
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

	// プレイヤーとの当たり判定フラグ
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	// ポールの当たり判定のオフセットとサイズを設定
	void SetPoleCollisionOffset(float offsetX, float offsetY);
	void SetPoleCollisionSize(float width, float height);

	// 旗の落下処理を開始
	void StartFlagFall();
	// 旗が落ちきったかどうかを取得
	bool IsFlagFallen() const;

private:
	// ゴールの座標
	Vec2 m_pos;

	// ポールの当たり判定のオフセットとサイズ
	Vec2 m_poleCollisionOffset;
	Vec2 m_poleCollisionSize;

	Camera* m_pCamera;

	std::shared_ptr<BgStage1> m_pStage1;
	std::shared_ptr<Player> m_pPlayer;
		
	// グラフィックハンドル
	int m_handle;
	int m_poleHandle;

	// アニメーション
	int m_animFrame;
	int m_index;

	// 旗の落下処理
	bool m_isFlagFalling;
	bool m_isFlagFallen;
	float m_flagPosY;
	float m_flagFallSpeed;
};

