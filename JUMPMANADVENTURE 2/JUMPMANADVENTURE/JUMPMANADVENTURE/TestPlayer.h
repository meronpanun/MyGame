#pragma once
#include "Vec2.h"

class Camera;
class TestPlayer
{
	TestPlayer();
	~TestPlayer();

	void Init(Camera* camera);	// 初期化
	void End();	// 終了
	void Update();	// 更新
	void Draw();	// 描画

	// プレイヤーの情報を取得する
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;
	float PlayerAirPos();
	bool FallFlag();
	void OnDamage();
	int GetPlayerHp();
	void AddMove(Vec2 move);
	void AddMoveY(float DisY);
	void AddMoveLeft(float left);
	void AddMoveRight(float right);
	void SetVelocity(Vec2 velocity);
	void OnCollideY();
	void OnCollideX();
	void Landing(float DisY);
	Vec2 GetPos() const;

private:
	// グラフィックハンドル
	int m_handleIdle;
	int m_handleRun;

	// アニメーション関連
	int m_animFrame;	// フレーム数を数える
	// 現在再生中のアニメーション
	// true:走っている　false:待機
	bool m_isRun;

	int m_invincibleCount;

	int m_hp;

	Vec2 m_pos;
	Vec2 m_velocity;
	bool m_isDirLeft;

	// ジャンプ処理
	bool m_isJump;
	float m_jumpSpeed;

	Camera* m_camera;
};

