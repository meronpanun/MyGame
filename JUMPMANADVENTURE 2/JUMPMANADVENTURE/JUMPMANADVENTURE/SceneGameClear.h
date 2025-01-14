#pragma once
#include "SceneManager.h"

/// <summary>
///　ゲームクリアシーンクラス
/// </summary>
class SceneGameClear
{
public:
	SceneGameClear();
	~SceneGameClear();

	void Init();
	// シーンの切り替わり先を戻り値として返す
	// 切り替わらない場合は現在実行中のシーンを返す
	SceneManager::SceneSelect Update();
	void Draw();
	
private:
	// クリアシーンのグラフィックハンドル
	int m_gameClearHandle;
	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;
};

