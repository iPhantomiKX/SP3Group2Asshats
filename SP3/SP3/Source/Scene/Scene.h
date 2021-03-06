#ifndef SCENE_H
#define SCENE_H


#include "Mtx44.h"
#include "MatrixStack.h"
#include "../Graphics/Mesh/Mesh.h"
#include "../Graphics/Vertex/Vertex.h"
#include "../General/Camera.h"

#include "../Graphics/GraphicsLoader/GraphicsLoader.h"
#include "../GameObject/GameObject.h"

#include <vector>
#include <map>

class Scene
{
public:
    typedef std::map<char, std::pair<GraphicsLoader::GEOMETRY_TYPE, std::vector<COMPONENTS>> > LevelGenerationMap;
    static LevelGenerationMap m_levelGenerationData;
    static void AddToMap(char tileCount, GraphicsLoader::GEOMETRY_TYPE meshType, const std::vector<COMPONENTS>& componentsList);
    static void LoadLevelGenerationData(const char* file_path);
    static void LoadLevelMap(const char* file_path);

    static char** m_levelMap;    // store for pathfinding

    static const int m_rows = 40;
    static const int m_cols = 40;
    static const int tileSize = 5;

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
	float fps;

	// To render
	// ideal case is put objects in a vector; then use for loop to go through the list to render them

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextCentralised(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);

    //Gameobject handlers
    void RenderGameObjects(World* world);
    void UpdateGameObjects(World* world, double dt);
};

#endif