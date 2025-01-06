#pragma once
#include "Vec2.h"
#include "SceneManager.h"

/// <summary>
/// ゲームオーバーのクラス
/// </summary>
class SceneGameOver
{
public:
	SceneGameOver();
	virtual ~SceneGameOver();

	void Init();
	SceneManager::SceneSelect Update();
	void Draw();

	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// シーン選択のフラグ true:シーンに移動
	bool m_isSceneTitle;	// タイトル 

	// フェードイン、アウト
	int m_fadeAlpha;
};

