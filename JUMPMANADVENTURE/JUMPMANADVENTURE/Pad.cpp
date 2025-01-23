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

    bool IsPress(int key)
    {
        return (nowPad & key);
    }

    bool IsTrigger(int key)
    {
        bool isNow = (nowPad & key);   // ���݂̃t���[�� 
        bool isLast = (lastPad & key); // �ЂƂO�̃t���[��
        if (isNow && !isLast) // ���݂̃t���[����������Ă��ĂЂƂO�̃t���[����������Ă��Ȃ�
        {
            return true;
        }
        return false;
    }

    bool IsRelase(int key)
    {
        bool isNow = (nowPad & key);   // ���݂̃t���[�� 
        bool isLast = (lastPad & key); // �ЂƂO�̃t���[��
        if (!isNow && isLast) // ���݂̃t���[����������Ă��Ȃ��ĂЂƂO�̃t���[����������Ă���
        {
            return true;
        }
        return false;
    }
}






