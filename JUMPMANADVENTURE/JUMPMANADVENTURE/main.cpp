#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"
#include "Player.h"
#include "BgStage.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// �t���X�N���[���ł͂Ȃ��A�E�C���h�E���[�h�ŊJ���悤�ɂ���
	ChangeWindowMode(Game::kDefaultWindowMode);
	// ��ʂ̃T�C�Y��ύX����
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);
	SetWindowTextA("JumpmanAdventure");

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pScene = new SceneManager();
	pScene->Init();

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

		// ��ʂ̐؂�ւ���҂K�v������
		ScreenFlip();	// 1/60�b�o�߂���܂ő҂�

		// FPS(Frame Per Second)60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	// �������̉��
	delete pScene;

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}