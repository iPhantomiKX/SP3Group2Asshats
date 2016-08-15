#ifndef SCENE_SP3_H
#define SCENE_SP3_H

#include "Scene.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include "Mesh.h"
#include "Vertex.h"

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

    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHTENABLED,
        U_NUMLIGHTS,
        U_LIGHT0_TYPE,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_COSCUTOFF,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TEXT_ENABLED,
        U_TEXT_COLOR,
        U_TOTAL,
    };

    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];
    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    MS modelStack;
    MS viewStack;
    MS projectionStack;

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

    void RenderText(Mesh* mesh, std::string text, Color color);
    void RenderTextCentralised(Mesh* mesh, std::string text, Color color);
    void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    void RenderMesh(Mesh *mesh, bool enableLight);

    // To render
    // ideal case is put objects in a vector; then use for loop to go through the list to render them
};

#endif