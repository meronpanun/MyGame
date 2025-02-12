#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>
#include <string> 

class FontManager;
class Camera;
class Player;
class BgStage;
class Enemy
{
public:
	Enemy();
	 ~Enemy();

	void Init(Camera* camera);
	void Update();
	void Draw();

	// 敵の上下左右情報取得
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// 現在の敵の矩形情報
	Rect GetRect();

	// 敵の位置情報を取得
	Vec2 GetPos() const { return m_pos; }

	// 敵の移動方向を反転
	void ReverseDirection();

	// 敵の生死フラグ
	void SetAlive(bool isAlive);

	// 敵の位置を設定
	void SetPos(float x, float y);

	// 敵が生きているかどうかのフラグ
	bool IsAlive() const;

	// プレイヤーが範囲内にいるかチェックする
	bool IsPlayerInRange(const Vec2& playerPos, float range); 

	// 敵をアクティブにする
	void Activate(); 
	// 敵がアクティブかどうかをチェックする
	bool IsActive() const;

private:
  	Camera* m_pCamera;

	std::shared_ptr<BgStage> m_pBgStage;
	std::shared_ptr<Player> m_pPlayer;

	// 敵の位置
	Vec2 m_pos;
	// 敵の加速度
	Vec2 m_move; 

	bool m_isTurnFlag;

	// エネミーが生きているかどうかのフラグ
	bool m_isAlive;

	// 向いている方向
	bool m_isAnimRight;
	bool m_isAnimLeft;
	bool m_isFacingRight; // 敵が右を向いているかどうか

	// 敵がアクティブかどうかを管理するフラグ
	bool m_isActive; 

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;
	// 敵のグラフィックハンドル
	int m_handle;
	int m_hitHandle;

	// 動画ハンドル
	int m_videoHandle;
	// 動画の再生状態
	bool m_isVideoPlaying;
	// フェードアウトフレームカウント
	int m_videoFadeFrameCount;
	// フェードインフレームカウント
	int m_videoFadeInFrameCount;

	int m_hitFrame;
};
