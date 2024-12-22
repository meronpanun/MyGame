#include "TestMap.h"
#include"Player.h"
#include "DxLib.h"
#include <cassert>

namespace
{
	bool hitBottom = false;
	float liftX = 0;
}

TestMap::TestMap() :
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_handle(-1)
{
}

TestMap::~TestMap()
{
}

void TestMap::Init()
{
	// �O���t�B�b�N�̓ǂݍ���
	m_handle = LoadGraph("data/image/map.png");
	assert(m_handle != -1);
	// �O���t�B�b�N�Ɋ܂܂��`�b�v���𐔂���
	int graphWidth = 0;
	int GraphHeight = 0;
	GetGraphSize(m_handle, &graphWidth, &GraphHeight);
	//�}�b�v�`�b�v�̐�
	m_graphChipNumX = graphWidth / kChipWidth;
	m_graphChipNumY = GraphHeight / kChipHeight;
	//�z��̃}�b�v�f�[�^���}�b�v�`�b�v�ɓ����B
	for (int wIndex = 0; wIndex < m_graphChipNumX; wIndex++)
	{
		for (int hIndex = 0; hIndex < m_graphChipNumY; hIndex++)
		{
			MapChip& temp = m_map.mapChips[wIndex][hIndex];
			temp.w = kChipWidth;//��
			temp.h = kChipHeight;//����
			temp.chipKind = kChipSetData[kChipNumY][kChipNumX];//���
			//mapChip��pos�����߂�
			float tempX = wIndex * temp.w + temp.w * 0.5f;
			float tempY = hIndex * temp.h + temp.w * 0.5f;
			temp.pos.SetPos(tempX, tempY);
		}
	}
}

void TestMap::End()
{
	// �O���t�B�b�N�̉��
	DeleteGraph(m_handle);
}

void TestMap::Update(Player* player)
{
	for (int h = 0; h < kChipNumY; h++)
	{
		for (int w = 0; w < kChipNumX; w++)
		{
			int chipNo = kChipSetData[h][w];
			if (chipNo < 440 && chipNo >= 0)
			{
				if (player->GetLeft() >= w * kChipWidth && player->GetLeft() <= w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight - m_AllChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight - m_AllChipHeight)
				{
					// �����瓖�������ꍇ
					float chipBottom = h * kChipHeight + kChipHeight - m_AllChipHeight;
					player->AddMoveY(chipBottom - player->GetTop());// �}�b�v�`�b�v�ƃv���C���[�̏d�Ȃ������������ɂ��炷
					player->OnCollideY();// m_velocity.y��0�ɂ���
					if (h * kChipHeight + kChipHeight - m_AllChipHeight == player->GetTop() && player->FallFlag() == false)
					{
						hitBottom = true;
						// �}�b�v�`�b�v����
						kChipSetData[h][w] = -1;
					}
				}

				// �ォ�瓖�������ꍇ
				if (player->GetLeft() >= w * kChipWidth && player->GetLeft() <= w * kChipWidth + kChipWidth
					&& player->GetBottom() >= h * kChipHeight - m_AllChipHeight && player->GetBottom() <= h * kChipHeight + kChipHeight - m_AllChipHeight)
				{
					//printfDx("���n");
					float chipTop = h * kChipHeight - m_AllChipHeight;
					player->Landing(player->GetBottom() - chipTop);// �}�b�v�`�b�v�ƃv���C���[�̏d�Ȃ�����������ɂ��炷
					hitBottom = false;
					player->OnCollideY();
				}

				// �}�b�v�`�b�v�̍������瓖�������ꍇ
				// 1�}�X�̌��Ԃ���}�b�v�`�b�v�̉����瓖����ƍ������瓖���������̏����Ɉ�����������
				// �v���C���[�����ɂ���Ă��܂��@��ʂ�I����Ă��璲������
				if (player->GetRight() >= w * kChipWidth && player->GetRight() < w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight - m_AllChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight - m_AllChipHeight
					&& hitBottom == false)
				{
					float chipLeft = w * kChipWidth;
					player->AddMoveLeft(player->GetRight() - chipLeft);// �}�b�v�`�b�v�ƃv���C���[�̏d�Ȃ������������ɂ��炷
					player->OnCollideX();// m_velocity.x��0�ɂ���
				}

				// �}�b�v�`�b�v�̉E�����瓖�������ꍇ
				/*if (player->GetLeft() > w * kChipWidth && player->GetLeft() < w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight)
				{
					float chipRight = w * kChipWidth + kChipWidth;
					player->AddMoveRight(chipRight - player->GetLeft());
					player->OnCollideX();
				}*/
			}

			if (chipNo == 440 || chipNo == 441 || chipNo == 442)
			{
				// �ォ�瓖�������ꍇ
				if (player->GetLeft() >= w * kChipWidth && player->GetLeft() <= w * kChipWidth + kChipWidth
					&& player->GetBottom() >= h * kChipHeight - m_AllChipHeight && player->GetBottom() <= h * kChipHeight + kChipHeight - m_AllChipHeight
					&& player->FallFlag() == true)
				{
					float chipTop = h * kChipHeight - m_AllChipHeight;
					if (player->PlayerAirPos() < chipTop)
					{
						player->Landing(player->GetBottom() - chipTop);
						player->OnCollideY();
					}
				}

				// �}�b�v�`�b�v�̍������瓖�������ꍇ
				if (player->GetRight() == w * kChipWidth && player->GetRight() < w * kChipWidth + kChipWidth
					&& player->GetTop() >= h * kChipHeight && player->GetTop() <= h * kChipHeight + kChipHeight)
				{
					float chipLeft = w * kChipWidth;
					player->AddMoveLeft(player->GetRight() - chipLeft);
					player->OnCollideX();
				}
			}
		}
	}
}

void TestMap::Draw(Camera* camera)
{
}
