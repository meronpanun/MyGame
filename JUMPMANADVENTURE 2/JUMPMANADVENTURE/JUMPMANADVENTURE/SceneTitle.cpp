#include "SceneTitle.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// �I���J�[�\���̏����ʒu
	constexpr int kInitSelectPosX = 480;
	constexpr int kInitSelectPosY = 320;
	// �I���J�[�\���̈ړ���
	constexpr int kSlectMoveY = 185;

 	// �t�F�[�h�A�E�g�̎���
	constexpr int kFadeFrame = 8;
	// �����t�F�[�h��
	constexpr int kStartFade = 180;
	// �ő�t�F�[�h��
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

	// ���L�[����������I����Ԃ�1������
	if (Pad::IsTrigger(pad & PAD_INPUT_DOWN))
	{
		m_select = (m_select + 1) % kSelectNum;
		m_selectPos.y += kSlectMoveY; // �I���J�[�\�������Ɉړ�

		// �I���J�[�\������ԉ���������I���J�[�\������ԏ�ɖ߂�
		if (m_selectPos.y > kInitSelectPosY + kSlectMoveY * (kSelectNum - 1))
		{
			m_selectPos.y = kInitSelectPosY;
		}
		return;
	}

	// ���L�[����������I����Ԃ�1�グ��
	if (Pad::IsTrigger(pad & PAD_INPUT_UP))
	{
		m_select = (m_select +(kSelectNum - 1)) % kSelectNum;
		m_selectPos.y -= kSlectMoveY; // �I���J�[�\������Ɉړ�

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
	// ���S�\��
	DrawRotaGraph(640, 260,
		1.0f, 0.0f,
		m_logoHandle, true);

	// �����\��
	DrawRectRotaGraph(640, 380,
		0, 0,
		250, 150,
		1.0f, 0.0f,
		m_charHandle, true, false);

	// �I���J�[�\���̕\��
	DrawRectRotaGraph(m_selectPos.x, m_selectPos.y,
		0, 0,
		250, 150,
		1.0f, 0.0f,
		m_selectHandle, true);
}
