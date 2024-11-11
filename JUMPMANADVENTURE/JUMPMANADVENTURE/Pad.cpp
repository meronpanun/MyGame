#include "Pad.h"
#include "DxLib.h"

namespace
{
    int nowPad = 0;  // ���݂̃t���[���̃p�b�h����
    int lastPad = 0; // �ЂƂO�̃t���[���̃p�b�h����
}

namespace Pad
{
    void Update()
    {
        // �O�̃t���[���ɉ�����Ă����p�b�h�̏����o���Ă���
        lastPad = nowPad;
        // ���݂̃t���[���ɉ�����Ă���p�b�h�̏����擾����
        nowPad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
    }

    bool IsPress(int button)
    {
        if (nowPad & button)
        {
            return true; // ������Ă���
        }
        else
        {
            return false; // ������Ă��Ȃ�
        }
    }

    bool IsTrigger(int button)
    {
        // ���݂̃t���[���Ń{�^����������Ă��Ȃ�
        if (!(nowPad & button))
        {
            return false;
        }

        // �O�̃t���[���Ń{�^����������Ă��Ȃ����Trigger�Ɣ���
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






