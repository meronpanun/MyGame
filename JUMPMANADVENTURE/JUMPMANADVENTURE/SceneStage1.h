#pragma once
#include "SceneMain.h"

class BgStage1;

/// <summary>
///  �X�e�[�W1�N���X
/// </summary>
class SceneStage1 : public SceneMain
{
public:
	SceneStage1();
	virtual ~SceneStage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	// �w�i�̃|�C���^
	BgStage1* m_pBg;
};
