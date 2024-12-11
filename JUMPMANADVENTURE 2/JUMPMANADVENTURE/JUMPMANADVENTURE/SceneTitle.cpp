#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// 選択カーソルの初期位置
	constexpr int kInitSelectPosX = 480;
	constexpr int kInitSelectPosY = 320;
	// 選択カーソルの移動量
	constexpr int kSlectMoveY = 185;

 	// フェードアウトの時間
	constexpr int kFadeFrame = 8;
	// 初期フェード量
	constexpr int kStartFade = 180;
	// 最大フェード量
	constexpr int kFadeMax = 255;
}

SceneTitle::SceneTitle():
	m_select(kStart),
	m_isSceneStart(false),
	m_fadeAlpha(kStartFade)
{
	m_logoHandle = LoadGraph("data/image/Title.png");
	m_selectHandle = LoadGraph("data/image/0210.png");
	m_charHandle = LoadGraph("data/image/titleChar.png");
}

SceneTitle::~SceneTitle()
{
	DeleteGraph(m_logoHandle);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_charHandle);
}


void SceneTitle::Init()
{
	m_isSceneStart = false;
	m_fadeAlpha = kStartFade;
	m_select = kStart;
	m_selectPos = { kInitSelectPosX,kInitSelectPosY };
}

void SceneTitle::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ↓キーを押したら選択状態を1つ下げる
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSlectMoveY; // 選択カーソルを下に移動

		// 選択カーソルが一番下だったら選択カーソルを一番上に戻す
		if (m_selectPos.y > kInitSelectPosY + kSlectMoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
		return;
	}

	// ↑キーを押したら選択状態を1つ上げる
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select +(kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSlectMoveY; // 選択カーソルを上に移動

		if (m_selectPos.y < kInitSelectPosY)
		{
			m_selectPos.y = kInitSelectPosY + kSlectMoveY * (kSelectNum - 1);
		}
		return;
	}

	if (Pad::IsTrigger(PAD_INPUT_A))
	{
		switch (m_select)
		{
		case kStart:
			m_isSceneStart = true;
			break;
		case kExit:
			DxLib_End();
			break;
		default:
			break;
		}
		return;
	}
}

void SceneTitle::Draw()
{
	// ロゴ表示
	DrawRotaGraph(640, 260,
		1.0f, 0.0f,
		m_logoHandle, true);

	// 文字表示
	DrawRectRotaGraph(640, 380,
		0, 0,
		250, 150,
		1.0f, 0.0f,
		m_charHandle, true, false);

	// 選択カーソルの表示
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y,
		0, 0,
		250, 150,
		1.0f, 0.0f,
		m_selectHandle, true);
}
