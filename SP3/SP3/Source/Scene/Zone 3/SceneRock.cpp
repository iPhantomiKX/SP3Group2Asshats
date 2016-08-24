#include "GL\glew.h"
//#include "../../shader.hpp"

#include "SceneRock.h"
#include "../../General/Application.h"
//#include "../../Graphics/LoadOBJ/LoadTGA.h"
//#include "../../Graphics/Mesh/MeshBuilder.h"
#include "../../General/SharedData.h"

#include <sstream>

SceneRock::SceneRock()
{
}

SceneRock::~SceneRock()
{
}

void SceneRock::Init()
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
    Scene::LoadLevelMap("GameData/GrassScene.csv");
    for (int rows = 0; rows < Scene::m_rows; ++rows)
    {
        for (int cols = 0; cols < Scene::m_cols; ++cols)
        {
            if (m_levelMap[rows][cols] == '0')
                continue;

            LevelGenerationMap::iterator it = Scene::m_levelGenerationData.find(m_levelMap[rows][cols]);

            // it->first is tileCount
            // first in it->second is mesh
            // second in it->second is vector of components
            //std::cout << m_levelMap[rows][cols] << " ";

            GameObject go = createGO(&grass);
            grass.mask[go] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE | COMPONENT_HITBOX;
            grass.position[go].Set(-100.f + cols * Scene::tileSize, 0.f, -100.f + rows * Scene::tileSize);
            grass.hitbox[go].m_origin = grass.position[go] + Vector3(0, 2.5, 0);
            grass.hitbox[go].m_scale.Set(5.f, 5.f, 5.f);
            grass.appearance[go].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh((it->second).first);
            grass.appearance[go].scale.Set(1, 1, 1);
        }
    }

    monster = createGO(&grass);
    grass.mask[monster] = COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_APPEARANCE | COMPONENT_HITBOX | COMPONENT_AI;
    grass.position[monster].SetZero();
    grass.velocity[monster].Set(0, 0, 1);
    grass.hitbox[monster].m_origin = grass.position[monster] + Vector3(0, 0.75f, -0.3);
    grass.hitbox[monster].m_scale.Set(1.5f, 1.5f, 1.75f);
    grass.appearance[monster].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_RABBIT);
    grass.appearance[monster].scale.Set(1, 1, 1);

    rock = createGO(&grass);
    grass.mask[rock] = COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_APPEARANCE | COMPONENT_HITBOX;
    grass.position[rock].Set(SharedData::GetInstance()->player->GetPositionVector().x, SharedData::GetInstance()->player->GetPositionVector().y, SharedData::GetInstance()->player->GetPositionVector().z);
    grass.appearance[rock].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE);
    grass.appearance[rock].scale.Set(1, 1, 1);

    net = createGO(&grass);
    grass.mask[net] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE;
    grass.position[net].SetZero();
    grass.appearance[net].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_NET);
    grass.appearance[net].scale.Set(2, 2, 2);
    //HITBOX.m_origin = Vector3(0, 5, 0);
    //HITBOX.m_scale = Vector3(10, 10, 10);

    b_capturing = false;
    b_captured = false;
    captureCounter = 0;
    counter = 0;
}
static double counter = 0;

void SceneRock::Update(double dt)
{
    fps = (float)(1.f / dt);

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

    //Inputmanager Update
    SharedData::GetInstance()->inputManager->Update();

    //===============================================================================================================================//
    //                                                            Checks                                                             //
    //===============================================================================================================================//

    //Projectile checks
    if (ItemProjectile::ItemProjectileList.size())
    {
        for (unsigned i = 0; i < ItemProjectile::ItemProjectileList.size(); ++i)
        {
            if (grass.hitbox[monster].CheckCollision(ItemProjectile::ItemProjectileList[i]->position))
            {
                b_capturing = true;
                ItemProjectile::ItemProjectileList[i]->deleteBullet;
                grass.position[net] = grass.position[monster];
            }
            if (b_capturing == true)
            {
                int v1 = rand() % 100;
                std::cout << v1 << std::endl;
                if (v1 < 20)
                {
                    b_captured = true;
                }
                b_capturing = false;//fail capture
                grass.position[net] = 0;//set net to false
            }
            if (b_captured == true)
            {
                grass.velocity[monster] = 0;
                grass.position[net] = grass.position[monster];
                break;
            }
        }
    }

    if (Application::IsKeyPressed('C') && SharedData::GetInstance()->player->inventory[Item::TYPE_BAIT].Use() && counter > 0.5)
    {
        ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
            Vector3(SharedData::GetInstance()->player->GetPositionVector().x, SharedData::GetInstance()->player->GetPositionVector().y, SharedData::GetInstance()->player->GetPositionVector().z),
            Vector3(SharedData::GetInstance()->player->GetViewVector().x, SharedData::GetInstance()->player->GetViewVector().y, SharedData::GetInstance()->player->GetViewVector().z),
            500,
            50,
            10
            ));
        counter = 0;
    }
    //////////////////////////////////////////////
    ////Projectile checks//////////////NET////////
    //////////////////////////////////////////////
    if (ItemProjectile::ItemProjectileList.size())
    {
        for (unsigned i = 0; i < ItemProjectile::ItemProjectileList.size(); ++i)
        {
            for (GameObject ai = 0; ai < grass.GAMEOBJECT_COUNT; ++ai)
            {
                if ((grass.mask[ai] & COMPONENT_AI) == COMPONENT_AI)
                {
                    if (grass.hitbox[ai].CheckCollision(ItemProjectile::ItemProjectileList[i]->position))
                    {
                        ItemProjectile::ItemProjectileList[i]->deleteBullet;
                        net = createGO(&grass);
                        grass.mask[net] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE;
                        grass.capture[net].capturingMonster = true;
                        grass.capture[net].capturedMonster = false;
                        grass.capture[net].timeBeforeCapture = 3;
                        grass.appearance[net].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_NET);
                        grass.appearance[net].scale.Set(2, 2, 2);
                        if (grass.capture[net].capturingMonster == true)
                        {
                            grass.position[net] = grass.position[ai];
                            int v1 = rand() % 100;
                            std::cout << v1 << std::endl;
                            if (v1 < 20)
                            {
                                grass.capture[net].capturedMonster = true;//Captured!
                            }
                            grass.capture[net].capturingMonster = false;//fail capture
                        }
                        if (grass.capture[net].capturedMonster == true)
                        {
                            grass.velocity[ai] = 0;
                            grass.position[net] = grass.position[ai];
                        }
                    }
                }
            }
        }
    }
    //////////////////////////////////////////////
    ////////BAIT /////////////////////////////////
    //////////////////////////////////////////////
    //if (ItemProjectile::ItemProjectileList.size())
    //{
    //	for (unsigned i = 0; i < ItemProjectile::ItemProjectileList.size(); ++i)
    //	{
    //		if (ItemProjectile::ItemProjectileList[i]->position.y <= 1)
    //		{
    //			Vector3 tempo = ItemProjectile::ItemProjectileList[i]->position;
    //			ItemProjectile::ItemProjectileList[i]->deleteBullet;

    //			bait = createGO(&grass);
    //			grass.mask[bait] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE | COMPONENT_BAIT;
    //			grass.position[bait] = tempo;
    //			grass.appearance[bait].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE);
    //			grass.appearance[bait].scale.Set(1, 1, 1);
    //			grass.bait[bait].scentRadius = 200;
    //			grass.bait[bait].foundRadius = 5;
    //			grass.bait[bait].eattingBait = false;
    //			grass.bait[bait].foundBait = false;
    //			grass.bait[bait].timeEatting = 3.0f;
    //		}
    //	} 
    //}

    //for (GameObject ai = 0; ai < grass.GAMEOBJECT_COUNT; ++ai)
    //{
    //	if ((grass.mask[ai] & COMPONENT_AI) == COMPONENT_AI)
    //	{
    //		for (GameObject bait = 0; bait < grass.GAMEOBJECT_COUNT; ++bait)
    //		{
    //			if ((grass.mask[bait] & COMPONENT_BAIT) == COMPONENT_BAIT)
    //			{
    //				if ((grass.position[ai] - grass.position[bait]).LengthSquared() < grass.bait[bait].scentRadius && grass.bait[bait].eattingBait == false)
    //				{
    //					grass.bait[bait].foundBait = true;
    //					std::cout << " FOUND BAIT " + grass.bait[bait].foundBait << std::endl;
    //					if (grass.bait[bait].foundBait == true)
    //					{
    //						grass.velocity[ai] = (grass.position[ai] - grass.position[bait]).Normalized();
    //						grass.velocity[ai].y = 0;
    //						grass.velocity[ai] *= -1;
    //					}
    //				}
    //				if ((grass.position[ai] - grass.position[bait]).LengthSquared() < grass.bait[bait].foundRadius)
    //				{
    //					std::cout << "EATTING BAIT " + grass.bait[bait].foundBait << std::endl;
    //					grass.bait[bait].foundBait = false;
    //					grass.bait[bait].eattingBait = true;
    //					grass.velocity[ai] = 0;
    //					grass.velocity[ai].y = 0;
    //				}
    //				if (grass.bait[bait].eattingBait == true)
    //				{
    //					grass.bait[bait].timeEatting -= dt;
    //					std::cout << grass.bait[bait].timeEatting << std::endl;
    //					if (grass.bait[bait].timeEatting <= 0)
    //					{
    //						grass.bait[bait].eattingBait == false;
    //						destroyGO(&grass, bait);
    //						std::cout << "Done Eatting" << std::endl;
    //						//PUT WHATEVER THE RABBIT DO NORMALLY HERE :D (DONE EATTING BAIT)
    //						grass.velocity[ai] = 2;
    //						grass.velocity[ai].y = 0;
    //					}
    //				}
    //			}
    //		}
    //	}
    //}


    //Trap check (radius)
    for (GameObject trap = 0; trap < grass.GAMEOBJECT_COUNT; ++trap)
    {
        if ((grass.mask[trap] & COMPONENT_TRAP) == COMPONENT_TRAP)
        {
            if (!grass.trap[trap].activated)
            {
                for (GameObject ai = 0; ai < grass.GAMEOBJECT_COUNT; ++ai)
                {
                    if ((grass.mask[ai] & COMPONENT_AI) == COMPONENT_AI)
                    {
                        if ((grass.position[trap] - grass.position[ai]).LengthSquared() < grass.trap[trap].radius)
                        {
                            grass.trap[trap].caughtMonsterVel = grass.velocity[ai];
                            grass.trap[trap].caughtMonster = ai;
                            grass.trap[trap].activated = true;
                            grass.velocity[ai].SetZero();
                        }
                    }
                }
            }
            else
            {
                if (grass.trap[trap].triggerTimer < grass.trap[trap].triggerDuration)
                {
                    grass.trap[trap].triggerTimer += dt;
                }
                else
                {
                    grass.velocity[grass.trap[trap].caughtMonster] = grass.trap[trap].caughtMonsterVel;
                    destroyGO(&grass, trap);
                }
            }
        }
    }

    for (GameObject tallGrass = 0; tallGrass < grass.GAMEOBJECT_COUNT; ++tallGrass)
    {
        if ((grass.mask[tallGrass] & COMPONENT_HITBOX) == COMPONENT_HITBOX)
        {
            if (grass.hitbox[tallGrass].CheckCollision(SharedData::GetInstance()->player->GetPositionVector()))
            {
                SharedData::GetInstance()->player->m_bHiding = true;
            }
        }
    }

    //===============================================================================================================================//
    //                                                            Key Inputs                                                         //
    //===============================================================================================================================//

    //Place trap
    if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_G].isPressed && SharedData::GetInstance()->player->inventory[Item::TYPE_TRAP_ONE].Use())
    {
        GameObject trap = createGO(&grass);

        grass.mask[trap] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE | COMPONENT_TRAP;

        grass.position[trap].Set(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20);
        grass.appearance[trap].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP);
        grass.appearance[trap].scale.Set(3, 3, 3);

        grass.trap[trap].triggerDuration = 3.0f;
        grass.trap[trap].triggerTimer = 0.f;
        grass.trap[trap].radius = 2.5f;
        grass.trap[trap].activated = false;
        grass.trap[trap].caughtMonster = 0;
        grass.trap[trap].caughtMonsterVel.SetZero();

        counter = 0;
    }

    //Shoot projectile
    if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_X].isPressed && SharedData::GetInstance()->player->inventory[Item::TYPE_NET].Use())
    {
        ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
            Vector3(SharedData::GetInstance()->player->GetPositionVector().x, SharedData::GetInstance()->player->GetPositionVector().y, SharedData::GetInstance()->player->GetPositionVector().z),
            Vector3(SharedData::GetInstance()->player->GetViewVector().x, 0.5, SharedData::GetInstance()->player->GetViewVector().z),
            500,
            15,
            10
            ));

        counter = 0;
    }

    //Spawn monster at origin
    if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_E].isPressed)
    {
        monster = createGO(&grass);
        grass.mask[monster] = COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_APPEARANCE | COMPONENT_HITBOX | COMPONENT_AI;
        grass.position[monster].SetZero();
        grass.velocity[monster].Set(0, 0, 1);
        grass.hitbox[monster].m_origin = grass.position[monster] + Vector3(0, 0.75f, -0.3f);
        grass.hitbox[monster].m_scale.Set(1.5f, 1.5f, 1.75f);
        grass.appearance[monster].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_RABBIT);
        grass.appearance[monster].scale.Set(1, 1, 1);

        counter = 0;
    }

    //Shoot projectile
    /*if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_1].IsPressed() && counter > 0.2)
    {
    ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
    Vector3(camera.position.x, camera.position.y, camera.position.z),
    Vector3(SharedData::GetInstance()->player->GetViewVector().x, SharedData::GetInstance()->player->GetViewVector().y, SharedData::GetInstance()->player->GetViewVector().z),
    500,
    25,
    400
    ));

    counter = 0;
    }*/

    // for buffer time between projectile launches
    counter += dt;
}

void SceneRock::Render()
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

    //Lights are currently set to directional
    Light light = SharedData::GetInstance()->graphicsLoader->GetLights();

    if (light.type == Light::LIGHT_DIRECTIONAL)
    {
        Vector3 lightDir(light.position.x, light.position.y, light.position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(SharedData::GetInstance()->graphicsLoader->GetParameters(GraphicsLoader::U_LIGHT0_POSITION), 1, &lightDirection_cameraspace.x);
    }

    //Axes
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_AXES), false);

    //Render pojectiles
    for (vector<ItemProjectile*>::iterator it = ItemProjectile::ItemProjectileList.begin(); it != ItemProjectile::ItemProjectileList.end(); ++it)
    {
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

    RenderRockScene();

    //Trap placing
    double x, y;
    Application::GetCursorPos(&x, &y);
    modelStack.PushMatrix();
    modelStack.Translate(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0.5, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20);
    modelStack.Scale(1, 1, 1);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP), false);
    modelStack.PopMatrix();

    std::stringstream ss;
    ss << "FPS: " << fps;
    RenderTextOnScreen(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TEXT_IMPACT), ss.str(), Color(1, 1, 0), 3, 0, 3);

    std::stringstream ss1;
    ss1 << "Noise: " << SharedData::GetInstance()->player->GetNoiseFactor();
    RenderTextOnScreen(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TEXT_IMPACT), ss1.str(), Color(1, 1, 0), 3, 0, 6);
}

void SceneRock::RenderRockScene()
{
    //Ground mesh
    modelStack.PushMatrix();
    modelStack.Translate(0, 0, 0);
    modelStack.Rotate(-90, 1, 0, 0);
    modelStack.Scale(200, 200, 100);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS), true);
    modelStack.PopMatrix();

    //Gameobjects
    if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_ENTER].isHeldDown)
        RenderGameObjects(&grass);

    //Skyplane
    modelStack.PushMatrix();
    modelStack.Translate(500, 2800, -500);
    //modelStack.Rotate(0, 0,0,0);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASSZONESKYPLANE), false);
    modelStack.PopMatrix();

    for (GameObject tallGrass = 0; tallGrass < grass.GAMEOBJECT_COUNT; ++tallGrass)
    {
        if ((grass.mask[tallGrass] & COMPONENT_HITBOX) == COMPONENT_HITBOX)
        {

            modelStack.PushMatrix();
            modelStack.Translate(grass.hitbox[tallGrass].m_origin.x, grass.hitbox[tallGrass].m_origin.y, grass.hitbox[tallGrass].m_origin.z);
            modelStack.Scale(grass.hitbox[tallGrass].m_scale.x, grass.hitbox[tallGrass].m_scale.y, grass.hitbox[tallGrass].m_scale.z);
            //modelStack.Rotate(0, 0, 0, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE), false);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            modelStack.PopMatrix();
        }
    }
}

bool SceneRock::ViewCheckPosition(Vector3 pos, float degree)
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

void SceneRock::Exit()
{

}

//========================
// == OBJECTS TO RENDER
//========================
