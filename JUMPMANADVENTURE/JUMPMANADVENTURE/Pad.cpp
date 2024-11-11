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

    bool IsPress(int button)
    {
        if (nowPad & button)
        {
            return true; // 押されている
        }
        else
        {
            return false; // 押されていない
        }
    }

    bool IsTrigger(int button)
    {
        // 現在のフレームでボタンが押されていない
        if (!(nowPad & button))
        {
            return false;
        }

        // 前のフレームでボタンが押されていなければTriggerと判定
        if (lastPad & button)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    

    bool IsRelase(int button)
    {
        return false;
    }
}






