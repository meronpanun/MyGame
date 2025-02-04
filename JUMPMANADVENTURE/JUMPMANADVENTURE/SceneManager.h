#pragma once
#include "SceneBase.h"

class SceneStage1;
class SceneTitle;
class SceneMain;
class SceneGameClear;
/// <summary>
/// シーン管理クラス
/// </summary>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();

	// ゲームクリア画面への遷移を開始
	void StartGameClear();

private:
	SceneBase* m_pCurrentScene;
	SceneBase* m_pNextScene;

	// SceneManagerで管理するシーン
	SceneTitle* m_pTitle;
	SceneMain* m_pSceneMain;
	SceneGameClear* m_pGameClear;
	
	// ゲームクリアしたかどうか
	bool m_isGameClear;

	// スコアタイマー
	int m_score;
	int m_timer;
	int m_bonusTimer;

	// プレイヤーがダメージを一回も食らわなかったかどうかのフラグ
	bool m_isNoDamage;
};

