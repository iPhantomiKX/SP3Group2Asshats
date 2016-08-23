#include "GL\glew.h"
//#include "../../shader.hpp"

#include "SceneLava.h"
#include "../../General/Application.h"
//#include "../../Graphics/LoadOBJ/LoadTGA.h"
//#include "../../Graphics/Mesh/MeshBuilder.h"
#include "../../General/SharedData.h"

#include <sstream>

SceneLava::SceneLava()
{
}

SceneLava::~SceneLava()
{
}

void SceneLava::Init()
{
    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
    Mtx44 perspective;
    perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
    //perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
    projectionStack.LoadMatrix(perspective);

    camera.Init(Vector3(1, 1, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));

    Application::GetCursorPos(&Application::cursorXPos, &Application::cursorYPos);
    Application::SetCursorPos(Application::GetWindowWidth() / 2.f, Application::GetWindowHeight() / 2.f);

    bLButtonState = false;
    //Set heap(?)
    //memset(&grass, 0, sizeof(grass));

    // Load map
    //Scene::LoadLevelMap("GameData/GrassScene.csv");
    //for (int rows = 0; rows < Scene::m_rows; ++rows)
    //{
    //    for (int cols = 0; cols < Scene::m_cols; ++cols)
    //    {
    //        if (m_levelMap[rows][cols] == '0')
    //            continue;
    //
    //        LevelGenerationMap::iterator it = Scene::m_levelGenerationData.find(m_levelMap[rows][cols]);
    //
    //        // it->first is tileCount
    //        // first in it->second is mesh
    //        // second in it->second is vector of components
    //        //std::cout << m_levelMap[rows][cols] << " ";
    //
    //        GameObject go = createGO(&grass);
    //        grass.mask[go] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE | COMPONENT_HITBOX;
    //        grass.position[go].Set(-100.f + cols * Scene::tileSize, 0.f, -100.f + rows * Scene::tileSize);
    //        grass.hitbox[go].m_origin = grass.position[go];
    //        grass.hitbox[go].m_scale.Set(4.f, 4.f, 4.f);
    //        grass.appearance[go].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh((it->second).first);
    //        grass.appearance[go].scale.Set(1, 1, 1);
    //    }
    //}
    //
    //monster = createGO(&grass);
    //grass.mask[monster] = COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_APPEARANCE | COMPONENT_HITBOX | COMPONENT_AI;
    //grass.position[monster].SetZero();
    //grass.velocity[monster].Set(0, 0, 1);
    //grass.hitbox[monster].m_origin = grass.position[monster] + Vector3(0, 0.75f, -0.3);
    //grass.hitbox[monster].m_scale.Set(1.5f, 1.5f, 1.75f);
    //grass.appearance[monster].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_RABBIT);
    //grass.appearance[monster].scale.Set(1, 1, 1);
    //
    //rock = createGO(&grass);
    //grass.mask[rock] = COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_APPEARANCE | COMPONENT_HITBOX;
    //grass.position[rock].Set(SharedData::GetInstance()->player->GetPositionVector().x, SharedData::GetInstance()->player->GetPositionVector().y, SharedData::GetInstance()->player->GetPositionVector().z);
    //grass.appearance[rock].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE);
    //grass.appearance[rock].scale.Set(1, 1, 1);
    //
    //net = createGO(&grass);
    //grass.mask[net] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE;
    //grass.position[net].SetZero();
    //grass.appearance[net].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_NET);
    //grass.appearance[net].scale.Set(2, 2, 2);
    ////HITBOX.m_origin = Vector3(0, 5, 0);
    ////HITBOX.m_scale = Vector3(10, 10, 10);

    b_capturing = false;
    b_captured = false;
    captureCounter = 0;
    counter = 0;
}
static double counter = 0;

void SceneLava::Update(double dt)
{
    //===============================================================================================================================//
    //                                                            Updates                                                            //
    //===============================================================================================================================//

    //Update Projectiles
    itemProjectile->UpdateProjectile(dt);

    //Movement update for Gameobjects
    UpdateGameObjects(&grass, dt);

    //Camera Update
    camera.Update(dt);

    //Player Update
    SharedData::GetInstance()->player->Update(dt);

    SharedData::GetInstance()->inputManager->Update();

    //===============================================================================================================================//
    //                                                            Checks                                                             //
    //===============================================================================================================================//

    counter += dt;
}

void SceneLava::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Mtx44 perspective;
    perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
    //perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
    projectionStack.LoadMatrix(perspective);

    // Camera matrix
    viewStack.LoadIdentity();
    viewStack.LookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
        );
    // Model matrix : an identity matrix (model will be at the origin)
    modelStack.LoadIdentity();

    Light light = SharedData::GetInstance()->graphicsLoader->GetLights();

    if (light.type == Light::LIGHT_DIRECTIONAL)
    {
        Vector3 lightDir(light.position.x, light.position.y, light.position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(SharedData::GetInstance()->graphicsLoader->GetParameters(GraphicsLoader::U_LIGHT0_POSITION), 1, &lightDirection_cameraspace.x);
    }

    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_AXES), false);

    for (vector<ItemProjectile*>::iterator it = ItemProjectile::ItemProjectileList.begin(); it != ItemProjectile::ItemProjectileList.end(); ++it){
        modelStack.PushMatrix();
        modelStack.Translate(
            (*it)->position.x,
            (*it)->position.y,
            (*it)->position.z
            );
        modelStack.Scale(0.5, 0.5, 0.5);
        RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_NET), false);
        modelStack.PopMatrix();
    }

    RenderLavaScene();

    //visable hitbox
    /*modelStack.PushMatrix();
    modelStack.Translate(HITBOX.m_origin.x, HITBOX.m_origin.y, HITBOX.m_origin.z);
    modelStack.Scale(HITBOX.m_scale.x * 2, HITBOX.m_scale.y * 2, HITBOX.m_scale.z * 2);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE), false);
    modelStack.PopMatrix();*/

    modelStack.PushMatrix();
    modelStack.Translate(SharedData::GetInstance()->player->PlayerHitBox.m_origin.x, 0.1, SharedData::GetInstance()->player->PlayerHitBox.m_origin.z);
    modelStack.Scale(SharedData::GetInstance()->player->PlayerHitBox.m_scale.x, SharedData::GetInstance()->player->PlayerHitBox.m_scale.y, SharedData::GetInstance()->player->PlayerHitBox.m_scale.z);
    //modelStack.Translate(10,0,0);
    //modelStack.Scale(10,10,10);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_PLAYERBOX), false);
    modelStack.PopMatrix();

    //Trap placing
    double x, y;
    Application::GetCursorPos(&x, &y);
    modelStack.PushMatrix();
    modelStack.Translate(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0.5, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20);
    modelStack.Scale(1, 1, 1);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP), false);
    modelStack.PopMatrix();

    if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_ENTER].isPressed)
        std::cout << "asd" << std::endl;
}

void SceneLava::RenderLavaScene()
{
    //Ground mesh
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Scale(200, 200, 100);
    //RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS), true);
    modelStack.PopMatrix();

    //RenderGameObjects(&grass);

    //Skyplane
    modelStack.PushMatrix();
    modelStack.Translate(500, 2800, -500);
    //modelStack.Rotate(0, 0,0,0);
    //RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASSZONESKYPLANE), false);
    modelStack.PopMatrix();
}

bool SceneLava::ViewCheckPosition(Vector3 pos, float degree)
{
    if (pos != camera.position)
    {
        Vector3 view = (pos - camera.position).Normalized();

        float angleX = Math::RadianToDegree(acos(view.Dot(camera.target)));

        if (angleX <= degree)
        {
            return true;
        }
        if (angleX > degree)
        {
            return false;
        }
    }
}

void SceneLava::Exit()
{

}

//========================
// == OBJECTS TO RENDER
//========================
