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
	int m_uiHandle;
	// フォントハンドル
	int m_fontHandle;
	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;

	// タイトル演出に使用するフレーム
	int m_gameTitleFrameCount;

	// フェード処理
	int m_fadeFrameCount;

	// 動画ハンドル
	int m_videoHandle;
	// 動画の再生状態
	bool m_isVideoPlaying;
	// フェードアウトフレームカウント
	int m_videoFadeFrameCount;
	// フェードインフレームカウント
	int m_videoFadeInFrameCount;
};

