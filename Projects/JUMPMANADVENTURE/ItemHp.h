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

	// メンバー変数にアクセスするための関数 
	void SetHandle(int handle) { m_handle = handle; }

	// プレイヤーのポインタを取得
	void SetPlayer(std::shared_ptr<Player> pPlayer) { m_pPlayer = pPlayer; }

	// アイテムの位置を設定
	void SetPos(float x, float y);

	// アイテムが消える処理
	void ItemLost();

	// アイテムの位置を取得
	Vec2 GetPos() const { return m_pos; }

	// アイテムの半径を取得
	float GetRadius();

	// アイテムとプレイヤーが当たったかどうか
	bool GetHitPlayerFlag(std::shared_ptr<Player> pPlayer);

	//  アイテムが存在するかどうかを判定
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

