#include "DxLib.h"
#include "Game.h"
#include "SceneManager.h"
#include "Player.h"
#include "BgStage.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// フルスクリーンではなく、ウインドウモードで開くようにする
	ChangeWindowMode(Game::kDefaultWindowMode);
	// 画面のサイズを変更する
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorBitNum);
	SetWindowTextA("JumpmanAdventure");

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pScene = new SceneManager();
	pScene->Init();

	// ゲームループ
	while (ProcessMessage() == 0)	// Windowsが行う処理を待つ必要がある
	{
		// 今回のループが始まった時間を覚えておく
		LONGLONG time = GetNowHiPerformanceCount();

		// 画面全体をクリアする
		ClearDrawScreen();

		// ここにゲームの処理を書く
		pScene->Update();
		pScene->Draw();

		// 画面の切り替わりを待つ必要がある
		ScreenFlip();	// 1/60秒経過するまで待つ

		// FPS(Frame Per Second)60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	// メモリの解放
	delete pScene;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}