//#pragma once
//#include "DxLib.h"
//
///// <summary>
///// 
///// </summary>
//class MykeyInput
//{
//public:
//	/// <summary>
//	///  キーの入力状態の更新
//	/// </summary>
//	static void Update()
//	{
//		char tmpkey[256];
//
//		GetHitKeyStateAll(tmpkey);
//
//		for (int i = 0; i < 256; i++)
//		{
//			if (tmpkey[i] != 0) {
//				keyFrame[i]++;
//			}
//			else
//			{
//				keyFrame[i] = 0;
//			}
//		}
//	}
//
//private:
//	static int keyFrame[];
//};
//// 静的メンバ変数の実態作成
//int MykeyInput::keyFrame[256];