#pragma once

/// <summary>
/// シーンの基底クラス
/// </summary>
class SceneBase
{
public:
    virtual ~SceneBase() = default;

    virtual void Init() = 0;
    virtual SceneBase* Update() = 0;
    virtual void Draw() = 0;
};

