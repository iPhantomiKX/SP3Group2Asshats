/******************************************************************************/
/*!
\file	Material.h
\author Muhammad Amirul Bin Zaol-kefli
\par	email: 150509T@mymail.nyp.edu.sg
\brief
Load Materials of obj
*/
/******************************************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H

/******************************************************************************/
/*!
\brief
Component struct
*/
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f) {Set(r, g, b);}
	void Set(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
};

/******************************************************************************/
/*!
\brief
Material struct
*/
/******************************************************************************/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

	Material()
	{
		//some default values
		kAmbient.Set(0.1f, 0.1f, 0.1f);
		kDiffuse.Set(0.6f, 0.6f, 0.6f);
		kSpecular.Set(0.3f, 0.3f, 0.3f);
		kShininess = 5.f;
	}
};

#endif