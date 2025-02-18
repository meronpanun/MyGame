#pragma once
#include "Rect.h"
#include <memory>

class Camera;
class Player;

/// <summary>
/// アイテムクラス
/// </summary>
class ItemHp
{
public:
	ItemHp();
	 ~ItemHp();

	void Init(Camera* camera);
	void Update();
	void Draw() ;

	/// <summary>
	/// メンバー変数にアクセスするための関数 
	/// </summary>
	/// <param name="handle">グラフィックハンドル</param>
	void SetHandle(int handle) { m_handle = handle; }

	/// <summary>
	/// プレイヤーのポインタを取得
	/// </summary>
	/// <returns>プレイヤーのポインタ</returns>
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	/// <summary>
	/// アイテムの位置を設定
	/// </summary>
	/// <param name="x">X座標</param>
	/// <param name="y">Y座標</param>
	void SetPos(float x, float y);

	/// <summary>
	/// アイテムが消える処理
	/// </summary>
	void ItemLost();

	/// <summary>
	/// アイテムの位置を取得
	/// </summary>
	//// <returns>アイテムの位置</returns>
	Vec2 GetPos() const { return m_pos; }

	//アイテムの半径を取得

	/// <summary>
	/// アイテムの半径を取得
	/// </summary>
	/// <returns>半径</returns>
	float GetRadius();

	/// <summary>
	/// アイテムとプレイヤーが当たったかどうか
	/// </summary>
	/// <param name="pPlayer">プレイヤーのポインタ</param>
	/// <returns>当たったかどうか</returns>
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	/// <summary>
	///  アイテムが存在するかどうかを判定
	/// </summary>
	/// <returns></returns>
	bool IsExist() const; 

private:
	// アイテムの位置
	Vec2 m_pos;

	Camera* m_pCamera;
	std::shared_ptr<Player> m_pPlayer;

	// グラフィックハンドル
	int m_handle;
	// エフェクトのグラフィックハンドル
	int m_effectHandle;

	// アニメーションのフレーム
	int m_animFrameCount;

	// アイテムの存在フラグを追加
	bool m_isExist;

	// エフェクトのアニメーションフレームカウント
	int m_effectAnimFrameCount;
	// エフェクトが再生中かどうかのフラグ
	bool m_isEffectPlaying;
};

