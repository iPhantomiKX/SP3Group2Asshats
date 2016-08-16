/******************************************************************************/
/*!
\file	LoadOBJ.h
\author Muhammad Amirul Bin Zaol-kefli
\par	email: 150509T@mymail.nyp.edu.sg
\brief
Load OBJ into scenes
*/
/******************************************************************************/
#ifndef LOAD_OBJ_H
#define LOAD_OBJ_H

#include <vector>
#include "../Vertex/Vertex.h"
#include "Vector3.h"

/******************************************************************************/
/*!
\brief
LoadOBJ bool
*/
/******************************************************************************/
bool LoadOBJ(
	const char *file_path, 
	std::vector<Position> & out_vertices, 
	std::vector<TexCoord> & out_uvs, 
	std::vector<Vector3> & out_normals
);

/******************************************************************************/
/*!
\brief
IndexVBO void
*/
/******************************************************************************/
void IndexVBO(
	std::vector<Position> & in_vertices,
	std::vector<TexCoord> & in_uvs,
	std::vector<Vector3> & in_normals,

	std::vector<unsigned> & out_indices,
	std::vector<Vertex> & out_vertices
);

#endif