/******************************************************************************/
/*!
\file	AABB.h
\author Chua Yunzhen Randall
\par	155106R
\brief
Struct to define an AABB
*/
/******************************************************************************/

#ifndef AABB_H
#define AABB_H

#include "Vector3.h"

/******************************************************************************/
/*!
Class AABB:
\brief	Defines an AABB and its methods
*/
/******************************************************************************/
struct AABB
{
	Vector3 m_origin;
	Vector3 m_scale;

	bool CheckCollision(const Vector3& vecPoint);
	bool CheckCollision(const AABB& rhsBox);

	AABB(Vector3 pos, Vector3 scale);
	AABB();
	~AABB();
};

/******************************************************************************/
/*!
\brief	AABB collision check of AABB against Vector3 point

\param	hitbox
AABB hitbox to test for collision
\param	vecPoint
Vector3 point to test for collision

*/
/******************************************************************************/
static bool CheckCollision(const AABB& hitbox, const Vector3& vecPoint)
{
	Vector3 max = hitbox.m_origin + hitbox.m_scale * 0.5;
	Vector3 min = hitbox.m_origin - hitbox.m_scale * 0.5;
	//Check if the point is less than max and greater than min
	if (vecPoint.x > min.x && vecPoint.x < max.x &&
		vecPoint.y > min.y && vecPoint.y < max.y &&
		vecPoint.z > min.z && vecPoint.z < max.z)
		return true;
	//If not, then return false
	else
		return false;
}
/******************************************************************************/
/*!
\param	lhsBox
First AABB hitbox to test for collision

\param rhsBox
Second AABB hitbox to test for collision

*/
/******************************************************************************/
static bool CheckCollision(const AABB& lhsBox, const AABB& rhsBox)
{
	Vector3 LhsMax = lhsBox.m_origin + lhsBox.m_scale * 0.5;
	Vector3 LhsMin = lhsBox.m_origin - lhsBox.m_scale * 0.5;
	Vector3 RhsMax = rhsBox.m_origin + rhsBox.m_scale * 0.5;
	Vector3 RhsMin = rhsBox.m_origin - rhsBox.m_scale * 0.5;

	//Check if lhsBox's max is greater than rhsBox's min and lhsBox's min is less than rhsBox's max
	if (LhsMax.x > LhsMin.x &&
		LhsMin.x < RhsMax.x &&
		LhsMax.y > LhsMin.y &&
		LhsMin.y < RhsMax.y &&
		LhsMax.z > LhsMin.z &&
		LhsMin.z < RhsMax.z)
		return true;
	//If not, then return false
	else		
		return false;	
}


#endif;