#pragma once
#include "Vec2.h"
#include <memory>

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();
	~Player();

	// 使用するグラフィックを設定する
//	void SetHandle(int handle) { m_handle = handle; }

	void Init();
	void Update();
	void Draw();


	// プレイヤーの上下左右情報取得
	float GetLeft() const;
	float GetTop() const;
	float GetRigth() const;
	float GetBottom() const;

	// プレイヤーの位置情報を取得する
	Vec2 GetPos() const { return m_pos; }

	void UpdateNormal();  // ゲーム中のUpdate

private:
	//enum Dir
	//{
	//	kDirDown,	// 下方向
	//	kDirLeft,	// 左方向
	//	kDirRight,	// 右方向
	//	kDirUp,		// 上方向
	//};

private:
	// グラフィックハンドル
	int m_runHandle;
	int m_jumpHandle;

	// アニメーション関連
	int m_animFrame;   // フレーム数を数える
	// true:走っている　false:待機
	bool m_isRun;
	// true:左向き　false:右向き
	bool m_isDirLeft;

	// プレイヤーの位置
	Vec2 m_pos;
	//Dir m_dir;

	// ジャンプ処理
	bool m_isJump;
	float m_jumpSpeed;

	int m_walkFrameCount;
};

