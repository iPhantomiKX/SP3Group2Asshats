#ifndef SCENE_H
#define SCENE_H

#include "Mtx44.h"
#include "MatrixStack.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Vertex/Vertex.h"
#include "../General/Camera.h"

class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Camera camera;

	// To render
	// ideal case is put objects in a vector; then use for loop to go through the list to render them

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextCentralised(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
};

#endif