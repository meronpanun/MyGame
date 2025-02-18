#include "Pad.h"
#include "DxLib.h"

namespace
{
    int nowPad = 0;  // 現在のフレームのパッド入力
    int lastPad = 0; // ひとつ前のフレームのパッド入力
}

namespace Pad
{
    void Update()
    {
        // 前のフレームに押されていたパッドの情報を覚えておく
        lastPad = nowPad;
        // 現在のフレームに押されているパッドの情報を取得する
        nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    }

    bool IsPress(int key)
    {
        return (nowPad & key);
    }

    bool IsTrigger(int key)
    {
        bool isNow = (nowPad & key);   // 現在のフレーム 
        bool isLast = (lastPad & key); // ひとつ前のフレーム
        if (isNow && !isLast) // 現在のフレームが押されていてひとつ前のフレームが押されていない
        {
            return true;
        }
        return false;
    }

    bool IsRelase(int key)
    {
        bool isNow = (nowPad & key);   // 現在のフレーム 
        bool isLast = (lastPad & key); // ひとつ前のフレーム
        if (!isNow && isLast) // 現在のフレームが押されていなくてひとつ前のフレームが押されていた
        {
            return true;
        }
        return false;
    }
}






