#include "SceneGameOver.h"
#include "Game.h"
#include "Pad.h"
#include "DxLib.h"

namespace
{
	// Gameover�̕����\���ʒu
	constexpr int kGameOverPosX = 960;
	constexpr int kGameOverPosY = 280;
	// Gameover�̕����T�C�Y
	constexpr int kGameOverSizeX = 1592;
	constexpr int kGameOverSizeY = 174;
	// Gameover�̕����g�嗦
	constexpr float kGameOverScale = 0.8f;

	// �����\���ʒu
	constexpr int kCharPosX = 960;
	constexpr int kCharPosY = 720;

	//�t�F�[�h
	constexpr int kFadeFrame = 8;
	// �ő�t�F�[�h��
	constexpr int kFadeMax = 255;

}
SceneGameOver::SceneGameOver():
	m_isSceneTitle(false),
	m_fadeAlpha(kFadeMax)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
}

SceneManager::SceneSelect SceneGameOver::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ZorA�L�[����������^�C�g���V�[���Ɉڍs
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneSelect::kSceneTitle;
	}
	// �������Ȃ���΃V�[���J�ڂ��Ȃ�(�Q�[���I�[�o�[��ʂ̂܂�)
	return SceneManager::SceneSelect::kSceneGameOver;
}

void SceneGameOver::Draw()
{
	DrawString(10, 10, "TitleScene", 0xffffff);
}
