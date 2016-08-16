#ifndef SCENE_SP3_H
#define SCENE_SP3_H

#include "../Scene.h"

class SceneSP3 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_BOX_06,
        GEO_BOX_09,
        GEO_TEXTBOX,
        // Text
        GEO_TEXT_IMPACT,
        GEO_TEXT_CENTURYGOTHIC,
        NUM_GEOMETRY
    };

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