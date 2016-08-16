/******************************************************************************/
/*!
\file	Vertex.h
\author Wen Sheng Tang
\par	email: tang_wen_sheng\@nyp.edu.sg
\brief
Get Position, Color, Texcoord of obj
*/
/******************************************************************************/
#ifndef VERTEX_H
#define VERTEX_H

#include "Vector3.h"

/******************************************************************************/
/*!
\brief
Position struct
*/
/******************************************************************************/
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) { Set(x, y, z); }
	void Set(float x, float y, float z) { this->x = x; this->y = y; this->z = z; }
};

/******************************************************************************/
/*!
\brief
Color struct
*/
/******************************************************************************/
struct Color
{
	float r, g, b, a;
	Color(float r = 1, float g = 1, float b = 1, float a = 1) { Set(r, g, b, a); }
    void Set(float r, float g, float b, float a = 1) { this->r = r; this->g = g; this->b = b; this->a = a; }
};

/******************************************************************************/
/*!
\brief
Texcoord struct
*/
/******************************************************************************/
struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) { Set(u, v); }
	void Set(float u, float v) { this->u = u; this->v = v; }
};

/******************************************************************************/
/*!
\brief
Vertex struct
*/
/******************************************************************************/
struct Vertex 
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
	Vertex(){}
};

#endif