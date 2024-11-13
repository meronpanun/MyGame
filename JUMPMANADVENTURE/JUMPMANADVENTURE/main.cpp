#include "DxLib.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Pad.h"
#include "_baseSceneh.h"
#include "SceneTitle.h"
#include "GameScene.h"
#include "ResultScene.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �t���X�N���[���ł͂Ȃ��A�E�C���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(Game::kDefaultWindowMode);
	// ��ʂ̃T�C�Y��ύX����
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game:: kColorBitNum);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	Map* pScene = new Map();
	pScene->Inti();

	Player* pMove = new Player();
	pMove->Init();

	/*�V�[���ϐ�*/
	/*_baseScene::_sceneList[0] = new SceneTitle;
	_baseScene::_sceneList[1] = new GameScene;
	_baseScene::_sceneList[2] = new ResultScene;*/

	/*�V�[���Ǘ��p�̕ϐ�*/
	//_baseScene::_nowScene = _baseScene::_sceneList[0];

	// �Q�[�����[�v
	while (ProcessMessage() == 0)	// Windows���s��������҂K�v������
	{
		// ����̃��[�v���n�܂������Ԃ��o���Ă���
		LONGLONG time = GetNowHiPerformanceCount();

		// ��ʑS�̂��N���A����
		ClearDrawScreen();

		// �����ɃQ�[���̏���������
		pScene->Update();
		pScene->Draw();

		/*_baseScene::_nowScene->Update();
		_baseScene::_nowScene->Draw();*/

		Pad::Update();

		pMove->Update();
		pMove->Draw();
		

		// ��ʂ̐؂�ւ���҂K�v������
		ScreenFlip();	// 1/60�b�o�߂���܂ő҂�

		// FPS(Frame Per Second)60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}