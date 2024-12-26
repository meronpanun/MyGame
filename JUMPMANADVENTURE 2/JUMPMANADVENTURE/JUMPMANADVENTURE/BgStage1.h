#pragma once
#include "Rect.h"
#include "Vec2.h"


class Camera;
class Player;
class BgStage1
{
public:
	BgStage1();
	virtual ~BgStage1();

	void Init(Camera* camera);
	void Update();
	void Draw();

	//�w�肵����`�Ɠ������Ă��邩����
	bool IsCollision(Rect rect, Rect& ChipRect);

private:
	Vec2 m_pos;

	Camera* m_pCamera;

	// �}�b�v�̃O���t�B�b�N�n���h��
    int m_handle001;
};

