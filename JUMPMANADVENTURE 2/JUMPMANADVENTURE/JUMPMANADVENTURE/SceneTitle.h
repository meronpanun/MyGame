#pragma once
#include "SceneManager.h"

/// <summary>
/// タイルシーンクラス
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	// シーンの切り替わり先を戻り値として返す
	// 切り替わらない場合は現在実行中のシーンを返す
	 SceneManager::SceneSelect Update();
	void Draw();

private:
	// タイトルのグラフィックハンドル
	int m_titleHandle;
	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;
};

