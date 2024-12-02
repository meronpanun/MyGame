#pragma once
#include "SceneMain.h"

class BgStage1;
class TestMap;

/// <summary>
///  ステージ1クラス
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
	// 背景のポインタ
	BgStage1* m_pBg;
//	TestMap* m_pTestMap;
};

