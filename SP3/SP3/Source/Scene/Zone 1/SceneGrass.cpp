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
    monsterPos.Set(0, 0, 20);
    //monsterVel.Set(0,0,-1);
    monsterVel.SetZero();
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	camera.Init(Vector3(1, 1, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Application::GetCursorPos(&Application::cursorXPos, &Application::cursorYPos);
	Application::SetCursorPos(Application::GetWindowWidth() / 2.f, Application::GetWindowHeight() / 2.f);

	bLButtonState = false; 

    hitbox.m_origin = monsterPos;
	hitbox.m_scale = Vector3(1.5f,3.5f,1.75f);

    monsterState = true;

    GameObject lol;
    grass->mask[lol] = createGO(grass);
    grass->mask[lol] = COMPONENT_HITBOX | COMPONENT_DISPLACEMENT | COMPONENT_VELOCITY | COMPONENT_HEALTH;
}
static double counter = 0;

void SceneGrass::Update(double dt)
{
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//double x, y;
	//Application::GetCursorPos(&x, &y);
	//x = x / Application::GetWindowWidth();
	//y = 1.f - y / Application::GetWindowHeight();

	//if (!bLButtonState && Application::IsMousePressed(0))
	//{
	//    bLButtonState = true;
	//}
	//else if (bLButtonState && !Application::IsMousePressed(0))
	//{
	//    bLButtonState = false;
	//    // do stuff
	//}

	itemProjectile->UpdateProjectile(dt);

	if (Application::IsKeyPressed('X'))
	{
		ItemProjectile::ItemProjectileList.push_back(new ItemProjectile(
			Vector3(camera.position.x, camera.position.y, camera.position.z),
			Vector3(SharedData::GetInstance()->player->GetViewVector().x, SharedData::GetInstance()->player->GetViewVector().y, SharedData::GetInstance()->player->GetViewVector().z),
			50,
			50,
			10
			));
	}

	if (ItemProjectile::ItemProjectileList.size())
	{
		if (hitbox.CheckCollision(ItemProjectile::ItemProjectileList[0]->position))
		{
            monsterVel = (monsterPos - camera.position).Normalized();
            monsterVel.y = 0;
		}
	}
	

    SharedData::GetInstance()->player->Update(dt);

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

    if (Application::IsKeyPressed('G'))
    {
        placedTraps.push_back(Vector3(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20));
    }

    for (unsigned i = 0; i < placedTraps.size(); ++i)
    {
        if ((monsterPos - placedTraps[i]).LengthSquared() < 2.5f)
        {
            monsterVel.SetZero();
            //placedTraps.;
        }
    }

	camera.Update(dt);

    monsterPos += monsterVel * 5 * dt;
    hitbox.m_origin = monsterPos;

    counter += dt;
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

	//RenderStuff();

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
		modelStack.Scale(1, 1, 1);
		RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS1), false);
		modelStack.PopMatrix();
	}

	RenderGrassScene();

	modelStack.PushMatrix();
	modelStack.Translate(hitbox.m_origin.x, hitbox.m_origin.y, hitbox.m_origin.z);
	modelStack.Scale(hitbox.m_scale.x, hitbox.m_scale.y, hitbox.m_scale.z);
	//RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_CUBE), false);
	modelStack.PopMatrix();

    double x, y;
    Application::GetCursorPos(&x, &y);

    if (counter > 1.f)
    {
        std::cout << x / 20 << " " << y / 20 << std::endl;
        counter = 0;
    }
    modelStack.PushMatrix();
    modelStack.Translate(SharedData::GetInstance()->player->GetPositionVector().x + SharedData::GetInstance()->player->GetViewVector().x * 20, 0.5, SharedData::GetInstance()->player->GetPositionVector().z + SharedData::GetInstance()->player->GetViewVector().z * 20);
    modelStack.Scale(1,1,1);
    RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_Traps), false);
    modelStack.PopMatrix();

    //trap update
    if (placedTraps.size())
    {
        for (unsigned i = 0; i < placedTraps.size(); ++i)
        {
            modelStack.PushMatrix();
            modelStack.Translate(placedTraps[i].x, placedTraps[i].y, placedTraps[i].z);
            modelStack.Scale(2, 2, 2);
            RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_Traps), false);
            modelStack.PopMatrix();
        }
    }
}

void SceneGrass::RenderGrassScene()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 100);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
    modelStack.Translate(monsterPos.x, monsterPos.y, monsterPos.z);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_RABBIT), true);
	modelStack.PopMatrix();
    /*
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

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_TRAP), true);
	modelStack.PopMatrix();

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

void SceneGrass::Exit()
{
}

//========================
// == OBJECTS TO RENDER
//========================
