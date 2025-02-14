#pragma once
class Life
{
public:
	Life();
	~Life();

	void Init();
	void Update();
	void Draw();

	// �f�[�^�ݒ�
	void SetHandle(int handle) { m_handle = handle; }
	void SetIndex(int index) { m_index = index; }

	int GetHandle() const { return m_handle; } 

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �A�j���[�V�����̐i�s�Ǘ�
	int m_animFrameCount;

	// �ʂ��ԍ�
	int m_index;
};

