#include "DxLib.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Pad.h"
#include "_baseSceneh.h"
#include "SceneTitle.h"
#include "GameScene.h"
#include "ResultScene.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// フルスクリーンではなく、ウインドウモードで開くようにする
	ChangeWindowMode(Game::kDefaultWindowMode);
	// 画面のサイズを変更する
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game:: kColorBitNum);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	Map* pScene = new Map();
	pScene->Inti();

	Player* pMove = new Player();
	pMove->Init();

	/*シーン変数*/
	/*_baseScene::_sceneList[0] = new SceneTitle;
	_baseScene::_sceneList[1] = new GameScene;
	_baseScene::_sceneList[2] = new ResultScene;*/

	/*シーン管理用の変数*/
	//_baseScene::_nowScene = _baseScene::_sceneList[0];

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

		/*_baseScene::_nowScene->Update();
		_baseScene::_nowScene->Draw();*/

		Pad::Update();

		pMove->Update();
		pMove->Draw();
		

		// 画面の切り替わりを待つ必要がある
		ScreenFlip();	// 1/60秒経過するまで待つ

		// FPS(Frame Per Second)60に固定
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}