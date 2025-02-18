#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>

class Life;
class Camera;
class BgStage;
class SceneMain;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player	
{
public:
	Player();
	 ~Player();

	void Init(Camera* pCamera);
	void Update();
	void Draw();

	/// <summary>
	/// 現在のHPを取得
	/// </summary>
	/// <returns>HP</returns>
	int GetHp() const { return m_hp; }

	/// <summary>
	/// プレイヤーがダメージを受けた時の処理
	/// </summary>
	void OnDamage();
 
	/// <summary>
	/// プレイヤーが敵を倒した後少しジャンプ
	/// </summary>
	void JumpOnEnemy();

	/// <summary>
	/// プレイヤーの位置情報を取得
	/// </summary>
	/// <returns></returns>
	Vec2 GetPos() const { return m_pos; }
	
	/// <summary>
	///  円の当たり判定
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius() const;

	/*プレイヤーの上下左右情報取得*/
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	/// <summary>
	/// マップチップとの当たり判定
	/// </summary>
	/// <param name="chipRect"></param>
	void CheckHitBgStage(Rect chipRect);
	
	/// <summary>
	/// プレイヤーの移動量を取得
	/// </summary>
	/// <returns>Y軸方向の移動量を取得</returns>
	float GetMoveY() const;

	/// <summary>
	/// Y軸方向の移動量を追加 
	/// </summary>
	/// <param name="DisY">Y軸方向の移動量</param>
	void AddMoveY(float DisY);

	/// <summary>
	/// Y軸方向の移動量をリセット
	/// </summary>
	void OnCollideY();
	
	/// <summary>
	/// 現在のプレイヤーの矩形情報を取得
	/// </summary>
	/// <returns>プレイヤーの矩形情報</returns>
	Rect GetRect() const;

	/// <summary>
	/// ゲームオーバー演出を開始するフラグ
	/// </summary>
	/// <returns>true:ゲームオーバー false:ゲームオーバーでない</returns>
	bool IsGameOver() const;

	/// <summary>
	///  プレイヤーの操作を無効化S
	/// </summary>
	void DisableControl();
	
	/// <summary>
	/// プレイヤーの操作が無効かどうか 
	/// </summary>
	/// <returns>true:無効 false:有効</returns>
	bool IsControlDisabled() const;

	/// <summary>
	/// プレイヤーの位置を設定
	/// </summary>
	/// <param name="x">X座標</param>
	void SetPosX(float x);

	/// <summary>
	/// プレイヤーが地面にいるかどうか 
	/// </summary>
	/// <returns>true:地面にいる false:地面にいない</returns>
	bool IsOnGround() const;

	/// <summary>
	/// プレイヤーを地面の高さまでゆっくり落とす
	/// </summary>
	/// <param name="groundHeight"></param>
	void FallToGround(float groundHeight);
	
	/// <summary>
	/// プレイヤーの歩行状態を設定する
	/// </summary>
	/// <param name="isWalking"></param>
	void SetIsWalking(bool isWalking);

	/// <summary>
	/// プレイヤーのアニメーションを更新する
	/// </summary>
	void UpdateAnimation();
	
	/// <summary>
	///  ダメージを受けたかどうかを示すフラグ
	/// </summary>
	/// <returns>true:ダメージを受けた false:ダメージを受けていない</returns>
	bool HasTakenDamage() const; 

	/// <summary>
	/// HPを回復する
	/// </summary>
	void RecoverHp(); 

private:
	/// <summary>
	///  ジャンプ処理
	/// </summary>
	void UpdateJump();

	/*各状態毎のUpdate処理*/
	/// <summary>
	/// ゲーム中のUpdate
	/// </summary>
	void UpdateNormal(); 
	/// <summary>
	/// 死亡後のUpdate
	/// </summary>
	void UpdateDead();   

	/// <summary>
	///  死亡時の初期化処理
	/// </summary>
	void InitDead();

	/// <summary>
	///  初期リスポーン
	/// </summary>
	void StartRespawn();
	/// <summary>
	/// リスポーン
	/// </summary>
	void Respawn();

private:
	Camera* m_pCamera;
	SceneMain* m_pMain;
	std::shared_ptr<BgStage> m_pBgStage;
	std::vector<Life> m_Life;

	// プレイヤーの位置
	Vec2 m_pos;
	// 移動量
	Vec2 m_move;

	// キャラクターのグラフィックハンドル
	int m_walkHandle;
	int m_jumpHandle;

	// SE
	int m_seHandle;
	int m_jumpSEHandle;
	int m_damageSEHandle;
	int m_playerDeadSEHandle;
	int m_itemHpSEHandle;

	// アニメーションのフレーム
	int m_animFrame;
	// アニメーションのカウント
	int m_animCount;

	// ジャンプ処理
	int m_jumpCount;   // ジャンプのカウント
	int m_jumpFrame;   // ジャンプ中のフレーム数
	bool m_isJump;     // ジャンプしているかどうかフラグ
	bool m_isAnimJump; // プレイヤーがジャンプ描画しているかどうかのフラグ
	float m_jumpSpeed; // ジャンプ速度

	// 右に移動しているかどうかのフラグ
	bool m_isRightMove; 
	// 左に移動しているかどうかのフラグ
	bool m_isLeftMove;
	// 歩いているかどうかフラグ
	bool m_isWalk; // true:歩いている false:待機
	// キャラがどちらを向いているかのフラグ
	bool m_isAnimTurn;

	// ゲームオーバー演出を開始するフラグ
	bool m_isGameOver;

	// 地面と接しているか　true:接している 
	bool m_isGround;

	// プレイヤーの体力
	int m_hp;
	int m_life;

	// 点滅
	int m_blinkFrameCount;
	// 死亡演出
	int m_deadFrameCount;

	// リスポーン遅延
	int m_respawnTimer;

	// 操作無効化
	bool m_isControlDisabled;

	// プレイヤーの高さ
	float m_height;

	// ダメージを受けたかどうかを示すフラグ
	bool m_hasTakenDamage;
};

