#pragma once
#include "SceneBase.h"
#include <memory>

class FontManager;
/// <summary>
/// タイルシーンクラス
/// </summary>
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	~SceneTitle();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

private:
	// フォント管理
	std::shared_ptr<FontManager> m_pFont;
	// タイトルのグラフィックハンドル
	int m_titleHandle; 
	// タイトル用BGMハンドル
	int m_bgmHandle;
	// タイトル用SEハンドル
	int m_seHandle;

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

