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
//	///  �L�[�̓��͏�Ԃ̍X�V
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
//// �ÓI�����o�ϐ��̎��ԍ쐬
//int MykeyInput::keyFrame[256];