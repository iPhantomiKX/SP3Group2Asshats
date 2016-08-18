#ifndef SCENE_SP3_H
#define SCENE_SP3_H

#include "../Scene.h"

class SceneSP3 : public Scene
{
    float m_worldHeight;
    float m_worldWidth;

    // Clicking
    bool bLButtonState;

public:
    SceneSP3();
    ~SceneSP3();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
};

#endif