#pragma once
class Map
{
public:
	Map();
	~Map();

	void Inti();
	void Update();
	void Draw();

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;
	// �O���t�B�b�N�Ƀ`�b�v�������܂܂�Ă��邩
	int m_graphChipNumX;
	int m_graphChipNumY;

};

