#include "GL\glew.h"
//#include "../../shader.hpp"

#include "SceneGrass.h"
#include "../../General/Application.h"
//#include "../../Graphics/LoadOBJ/LoadTGA.h"
//#include "../../Graphics/Mesh/MeshBuilder.h"
#include "../../General/SharedData.h"

#include <sstream>

SceneGrass::SceneGrass()
{
}

SceneGrass::~SceneGrass()
{
}

void SceneGrass::Init()
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

    memset(&grass, 0, sizeof(grass));

    monster = createGO(&grass);
    grass.mask[monster] = COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_APPEARANCE | COMPONENT_HITBOX;
    grass.position[monster].SetZero();
    grass.velocity[monster].Set(1,0,0);
    grass.hitbox[monster].m_origin = grass.position[monster] + Vector3(0, 0.75, -0.3);
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

	Capturing = false;
	captureCounter = 0;
	cd = 0;
}
static double counter = 0;

void SceneGrass::Update(double dt)
{
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

    //Update projectiles
	itemProjectile->UpdateProjectile(dt);

    //Shoot projectile
	if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_1].IsPressed())
	{
		ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
			Vector3(camera.position.x, camera.position.y, camera.position.z),
			Vector3(SharedData::GetInstance()->player->GetViewVector().x, SharedData::GetInstance()->player->GetViewVector().y, SharedData::GetInstance()->player->GetViewVector().z),
			500,
			25,
			400
			));
	}

	//if (HITBOX.CheckCollision(SharedData::GetInstance()->player->PlayerHitBox))
	//{
	//	std::cout << "COLLISION!" << std::endl;
	//}

    //Projectile checks
	//if (ItemProjectile::ItemProjectileList.size())
	//{
	//

 //       for (unsigned i = 0; i < ItemProjectile::ItemProjectileList.size(); ++i)
 //       {
	//	if (HITBOX.CheckCollision(ItemProjectile::ItemProjectileList[i]->position))
	//	{
	//		std::cout << "COLLISION!" << std::endl;
	//	}
 //       //    if (grass.hitbox[monster].CheckCollision(ItemProjectile::ItemProjectileList[i]->position))
 //       //    {
 //       //        grass.velocity[monster] = (grass.position[monster] - camera.position).Normalized();
 //       //        grass.velocity[monster].y = 0;
 //       //    }
 //       }
	//}

	//Projectile checks
	if (ItemProjectile::ItemProjectileList.size())
	{
		for (unsigned i = 0; i < ItemProjectile::ItemProjectileList.size(); ++i)
		{
			if (grass.hitbox[monster].CheckCollision(ItemProjectile::ItemProjectileList[i]->position))
			{
				Capturing = true;
				ItemProjectile::ItemProjectileList[i]->deleteBullet;
				grass.position[net] = grass.position[monster];
			}
			if (Capturing == true)
			{	
				int v1 = rand() % 100;
				std::cout << v1 << std::endl;
				if (v1 < 20)
				{
					Captured = true;
				}
				Capturing = false;//fail capture
				grass.position[net] = 0;//set net to false
			}
			if (Captured == true)
			{
				grass.velocity[monster] = 0;
				grass.position[net] = grass.position[monster];
				break;
			}
		}
	}
	
    //Move Gameobjects
    UpdateGameObjects(&grass, dt);

    //Camera Update
    camera.Update(dt);
    SharedData::GetInstance()->player->Update(dt);

    static int counter = 0;
    //Place trap
    if (Application::IsKeyPressed('G') && SharedData::GetInstance()->player->inventory[Item::TYPE_TRAP_ONE].Use() && counter < 10)
    {
        //placedTraps.push_back(Vector3(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20));
        GameObject trap = createGO(&grass);
        grass.mask[trap] = COMPONENT_DISPLACEMENT | COMPONENT_APPEARANCE;
        grass.position[trap].Set(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20);
        grass.appearance[trap].mesh = SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP);
        grass.appearance[trap].scale.Set(1, 1, 1);
        //grass.trap[trap].effectTimer = 3.0f;
        grass.trap[trap].radius = 50.0f;
        counter++;
    }

	//if (Application::IsKeyPressed('X') && SharedData::GetInstance()->player->inventory[Item::TYPE_ROCK].Use() )
	//{
	//	ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
	//		Vector3(SharedData::GetInstance()->player->GetPositionVector().x, SharedData::GetInstance()->player->GetPositionVector().y, SharedData::GetInstance()->player->GetPositionVector().z),
	//		Vector3(SharedData::GetInstance()->player->GetViewVector().x, SharedData::GetInstance()->player->GetViewVector().y, SharedData::GetInstance()->player->GetViewVector().z),
	//		500,
	//		100,
	//		10
	//		));		
	//}


	if (cd > 0)
	{
		cd -= dt;
	}

	//std::cout << cd << std::endl;
	if (Application::IsKeyPressed('X') && SharedData::GetInstance()->player->inventory[Item::TYPE_NET].Use() && cd < 0.5)
	{
		ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
			Vector3(SharedData::GetInstance()->player->GetPositionVector().x, SharedData::GetInstance()->player->GetPositionVector().y, SharedData::GetInstance()->player->GetPositionVector().z),
			Vector3(SharedData::GetInstance()->player->GetViewVector().x, 0.5, SharedData::GetInstance()->player->GetViewVector().z),
			500,
			15,
			10
			));
		cd = 1;
	}

    //Trap radius
    for (unsigned i = 0; i < placedTraps.size(); ++i)
    {
        if ((grass.position[monster] - placedTraps[i]).LengthSquared() < 2.5f)
        {
            grass.velocity[monster].SetZero();
            //Find a way to remove trap;
        }
    }

    if (Application::IsKeyPressed('Q'))
    {
        camera.position.y += (float)(10.f * dt);
        camera.target.y += (float)(10.f * dt);
    }
    if (Application::IsKeyPressed('E'))
    {
        camera.position.y -= (float)(10.f * dt);
        camera.target.y -= (float)(10.f * dt);
    }

}

void SceneGrass::Render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Mtx44 perspective;
	//perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	////perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	//projectionStack.LoadMatrix(perspective);
	//
	//// Camera matrix
	//viewStack.LoadIdentity();
	//viewStack.LookAt(
	//	camera.position.x, camera.position.y, camera.position.z,
	//	camera.target.x, camera.target.y, camera.target.z,
	//	camera.up.x, camera.up.y, camera.up.z
	//	);
	//// Model matrix : an identity matrix (model will be at the origin)
	//modelStack.LoadIdentity();

	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Application::GetWindowWidth(), Application::GetWindowHeight());
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(SharedData::GetInstance()->graphicsLoader->GetProgramID());*/
	//pass light depth texture
	//m_lightDepthFBO.BindForReading(GL_TEXTURE8);
	//glUniform1i(m_parameters[U_SHADOW_MAP], 8);
	//... old stuffs

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

	RenderGrassScene();

    //visable hitbox
	modelStack.PushMatrix();
	modelStack.Translate(HITBOX.m_origin.x, HITBOX.m_origin.y, HITBOX.m_origin.z);
	modelStack.Scale(HITBOX.m_scale.x * 2, HITBOX.m_scale.y * 2, HITBOX.m_scale.z * 2);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE), false);
	modelStack.PopMatrix();

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
    modelStack.Scale(1,1,1);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP), false);
    modelStack.PopMatrix();

    //trap update
   /* if (placedTraps.size())
    {
        for (unsigned i = 0; i < placedTraps.size(); ++i)
        {
            modelStack.PushMatrix();
            modelStack.Translate(placedTraps[i].x, placedTraps[i].y, placedTraps[i].z);
            modelStack.Scale(2, 2, 2);
            RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP), false);
            modelStack.PopMatrix();
        }
    }*/

    if (SharedData::GetInstance()->inputManager->keyState[InputManager::KEY_ENTER].IsPressed())
        destroyGO(&grass, monster);
}

void SceneGrass::RenderGrassScene()
{
    //Ground mesh
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 100);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS), true);
	modelStack.PopMatrix();

    RenderGameObjects(&grass);

    /*
    modelStack.PushMatrix();
    modelStack.Translate(monsterPos.x, monsterPos.y, monsterPos.z);
    modelStack.Scale(1, 1, 1);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_RABBIT), true);
    modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-3, 2, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_BIRD), true);
	modelStack.PopMatrix();*/

	/*modelStack.PushMatrix();
	modelStack.Translate(12, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS1), true);
	modelStack.PopMatrix();
    
	modelStack.PushMatrix();
	modelStack.Translate(12, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS2), true);
	modelStack.PopMatrix();*/
    /*
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 6);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS1), true);
	modelStack.PopMatrix();*/

    //Skyplane
	modelStack.PushMatrix();
	modelStack.Translate(500, 2800, -500);
	//modelStack.Rotate(0, 0,0,0);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASSZONESKYPLANE), false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(0, 0, 300);
	modelStack.Scale(10, 10, 10);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS2), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS3), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -300);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS4), false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -600);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS5), false);
	modelStack.PopMatrix();*/
}

bool SceneGrass::ViewCheckPosition(Vector3 pos, float degree)
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

void SceneGrass::Exit()
{

}

//========================
// == OBJECTS TO RENDER
//========================
