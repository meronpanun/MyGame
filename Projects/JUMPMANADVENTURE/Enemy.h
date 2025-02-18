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

/// <summary>
/// 敵クラス
/// </summary>
class Enemy
{
public:
	Enemy();
	 ~Enemy();

	void Init(Camera* camera);
	void Update();
	void Draw();

	/*敵の上下左右情報取得*/
	float GetLeft();
	float GetTop();
	float GetRigth();
	float GetBottom();

	// 現在の敵の矩形情報
	Rect GetRect();

	// 敵の位置情報を取得
	Vec2 GetPos() const { return m_pos; }

	/// <summary>
	///  敵の移動方向を反転
	/// </summary>
	void ReverseDirection();

	/// <summary>
	///  敵の生死フラグ 
	/// </summary>
	/// <param name="isAlive">true:生きている false:死んでいる</param>
	void SetAlive(bool isAlive);

	/// <summary>
	///  敵の位置を設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPos(float x, float y);

	/// <summary>
	/// 敵が生きているかどうかのフラグ
	/// </summary>
	/// <returns> true:生きている false:死んでいる</returns>
	bool IsAlive() const;

	/// <summary>
	///	プレイヤーが範囲内にいるかチェックする 
	/// </summary>
	/// <param name="playerPos">プレイヤーの位置</param>
	/// <param name="range">範囲</param>
	/// <returns>範囲内にいるかどうか</returns>
	bool IsPlayerInRange(const Vec2& playerPos, float range); 

	/// <summary>
	///  敵をアクティブにする
	/// </summary>
	void Activate(); 
	
	/// <summary>
	/// 敵がアクティブかどうかをチェックする
	/// </summary>
	/// <returns>true:アクティブ false:非アクティブ</returns>
	bool IsActive() const;

private:
  	Camera* m_pCamera;

	std::shared_ptr<BgStage> m_pBgStage;
	std::shared_ptr<Player> m_pPlayer;

	// 敵の位置
	Vec2 m_pos;
	// 敵の加速度
	Vec2 m_move; 

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
};
