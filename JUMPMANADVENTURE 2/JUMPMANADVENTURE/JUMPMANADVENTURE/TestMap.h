#pragma once
#include "Game.h"
#include "Vec2.h"
#include "Camera.h"

class Player;

struct MapChip
{
	Vec2 pos;
	float w, h;
	int chipKind;
};

class TestMap
{
public:
	TestMap();
	~TestMap();

	void Init();	// ������
	void End();	// �I��
	void Update(Player* player);	// �X�V
	void Draw(Camera* camera);	// �`��

private:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �O���t�B�b�N�Ɋ܂܂��`�b�v��
	int m_graphChipNumX;
	int m_graphChipNumY;

	// �}�b�v�`�b�v��1���̃T�C�Y
	const static int kChipWidth = 16;
	const static int kChipHeight = 16;

	// �}�b�v�ɕ~���l�߂�`�b�v�̐�
	const static int kChipNumX = Game::kScreenWidth / kChipWidth;
	const static int kChipNumY = 54;
};

