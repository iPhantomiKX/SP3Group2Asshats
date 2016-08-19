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
}

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

	camera.Update(dt);

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

	RenderGrassScene();
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
	modelStack.Translate(-6, 2, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_RABBIT), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-3, 2, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_BIRD), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(12, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS1), true);
	modelStack.PopMatrix();
    
	modelStack.PushMatrix();
	modelStack.Translate(12, 0, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GRASS2), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 6);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_ROCKS1), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 2);
	modelStack.Scale(1, 1, 1);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_Traps), true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(500, 2800, -500);
	//modelStack.Rotate(0, 0,0,0);
	RenderMesh(SharedData::GetInstance()->graphicsLoader->GetMesh(GraphicsLoader::GEO_GASSZONESKYPLANE), false);
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
