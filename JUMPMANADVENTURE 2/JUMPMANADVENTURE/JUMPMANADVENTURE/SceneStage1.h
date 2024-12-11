#pragma once
#include "SceneMain.h"

class BgStage1;

/// <summary>
///  ステージ1クラス
/// </summary>
class SceneStage1 : public SceneMain
{
	SceneStage1();
	virtual ~SceneStage1();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;

private:
	BgStage1* m_pBg;
 
};

