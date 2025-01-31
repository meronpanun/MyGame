#pragma once
#include "SceneBase.h"
#include <memory>

class FontManager;
/// <summary>
///　ゲームクリアシーンクラス
/// </summary>
class SceneGameClear : public SceneBase
{
public:
	SceneGameClear();
	~SceneGameClear();

	void Init() override;
	SceneBase* Update() override;
	void Draw() override;

	bool IsSceneTitle() const { return m_isSceneTitle; }

private:
	// フォント管理
	std::shared_ptr<FontManager> m_pFont;
	// クリアシーンのグラフィックハンドル
	int m_gameClearHandle;

	// 点滅させるためのフレームカウント
	int m_blinkFrameCount;

	// ゲームクリア演出に使用するフレーム
	int m_gameClearFrameCount;

	// フェード処理
	int m_fadeFrameCount;
	
	// シーン選択フラグ true:シーン遷移
	bool m_isSceneTitle;// タイトル

	// 背景のスクロール
	int m_bgScrollY;
};

