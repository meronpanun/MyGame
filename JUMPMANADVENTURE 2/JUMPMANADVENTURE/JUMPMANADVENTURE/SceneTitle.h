#pragma once
#include "Vec2.h"

/// <summary>
/// タイルシーンクラス
/// </summary>
class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	void Init();
	void Update();
	void Draw();

	bool IsSceneStart() const { return m_isSceneStart; }

private:
	enum Select
	{
		kStart,    // ゲームスタート
		kOption,   // オプション
		kExit,	   //	ゲーム終了
		kSelectNum // 項目数
	};

	// 現在の状態
	int m_select;

private:
	// シーン選択フラグ　true:シーン移動
	bool m_isSceneStart;

	// 選択カーソルの表示位置
	Vec2 m_selectPos;

	// フェードイン、アウト
	int m_fadeAlpha;

	// 画像
	int m_logoHandle;   // タイトルロゴ
	int m_selectHandle; // 選択カーソル 
	int m_charHandle;   // 文字
};

