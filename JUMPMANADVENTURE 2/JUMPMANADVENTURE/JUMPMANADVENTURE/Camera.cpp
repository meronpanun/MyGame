//#include "Camera.h"
//#include "DxLib.h"
//#include "Player.h"
//#include "Game.h"
//
//namespace
//{
//	// カメラ範囲	
//	constexpr float CameraScopeRangeW = 400.0f;
//	constexpr float CameraScopeRangeH = 300.0f;
//	constexpr float CameraScopeRangeTop = 200.0f;
//	constexpr float CameraScopeRangeBottom = 320.0f;
//}
//
//Camera::Camera()
//{
//}
//
//void Camera::Init(Camera& camera)
//{
//	camera.pos = VGet(0, 0, 0);
//}
//
//void Camera::Update(Camera& camera, const Player& player)
//{
//	// プレイヤーの位置が、カメラの中央から一定以上離れたら
//	// カメラの「目標」ポジションをその範囲に留める
//	VECTOR aimCameraPos = camera.pos;
//	if (player.pos.x > camera.pos.x + (CameraScopeRangeW * 0.5f))
//	{
//		aimCameraPos.x = player.pos.x - (CameraScopeRangeW * 0.5f);
//	}
//	else if (player.pos.x < camera.pos.x - (CameraScopeRangeW * 0.5))
//	{
//		aimCameraPos.x = player.pos.x + (CameraScopeRangeW * 0.5f);
//	}
//
//	camera.drawOffset.x = camera.pos.x * -1;
//
//	camera.drawOffset.x = camera.drawOffset.x + (Game::kScreenWidth * 0.5f);
//}