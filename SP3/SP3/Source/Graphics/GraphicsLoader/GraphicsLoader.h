#ifndef GRAPHICS_LOADER_H
#define GRAPHICS_LOADER_H

#include "../Mesh/Mesh.h"
#include "MatrixStack.h"
#include "../Lighting/Light.h"
#include "../Lighting/DepthFBO.h"
#include "../Mesh/LoadHmap.h"
#include "../ParticleManager/Particle.h"
#include <math.h>

#include <vector>

class GraphicsLoader
{
public:
	GraphicsLoader();
	~GraphicsLoader();

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		// BASE NUMBER + OFFSET = RESULT
		// U_COLOR_TEXTURE_ENABLED + i
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,

		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLE,

		U_LIGHT_DEPTH_MVP_GPASS,
		U_LIGHT_DEPTH_MVP,
		U_SHADOW_MAP,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_BOX_06,
		GEO_BOX_09,
		GEO_TEXTBOX,
		// Text
		GEO_TEXT,
		GEO_TEXT_IMPACT,
		GEO_TEXT_CENTURYGOTHIC,
		NUM_GEOMETRY
	};

	enum RENDER_PASS
	{
		RENDER_PASS_PRE,
		RENDER_PASS_MAIN,
	};

	void Init();
	void Exit();

	Mesh* GetMesh(GEOMETRY_TYPE m_geotype);
	unsigned GetParameters(UNIFORM_TYPE m_parameters);

	unsigned GetProgramID();
	unsigned GetGPassShaderID();
	DepthFBO GetLightDepthFBO();

	Light GetLights();
	RENDER_PASS GetRenderPass();

	/*Mtx44*/

private:
	
	unsigned m_vertexArrayID;
	Mesh* m_meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	std::vector<unsigned char> m_heightMap;

	unsigned m_gPassShaderID;
	DepthFBO m_lightDepthFBO;

	Mtx44 m_lightDepthProj;
	Mtx44 m_lightDepthView;

	Light m_lights;

	RENDER_PASS m_renderPass;
};

#endif