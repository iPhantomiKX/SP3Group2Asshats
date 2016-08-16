/******************************************************************************/
/*!
\file	Mesh.h
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Initialise mesh
*/
/******************************************************************************/
#ifndef MESH_H
#define MESH_H

#include <string>
#include "Material.h"

/******************************************************************************/
/*!
\brief
Mesh class
*/
/******************************************************************************/
class Mesh
{
public:
	enum DRAW_MODE
	{
		DRAW_TRIANGLES, //default mode
		DRAW_TRIANGLE_STRIP,
		DRAW_LINES,
		DRAW_MODE_LAST,
	};
	Mesh(const std::string &meshName);
	~Mesh();
	void Render();
	void Render(unsigned offset, unsigned count);

	const std::string name;
	DRAW_MODE mode;
	unsigned vertexBuffer;
	unsigned indexBuffer;
	unsigned indexSize;

	Material material;
	unsigned textureID;

    // Font Data
    bool LoadFontData(const char *file_path);
    int fontSize[256];
};

#endif