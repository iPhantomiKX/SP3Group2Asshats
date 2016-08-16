/******************************************************************************/
/*!
\file	LoadHmap.h
\author Muhammad Amirul Bin Zaol-kefli
\par	email: 150509T@mymail.nyp.edu.sg
\brief
Load Terrain Map
*/
/******************************************************************************/
#ifndef LOAD_HMAP_H
#define LOAD_HMAP_H

#include <vector>
bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap);

float ReadHeightMap(std::vector<unsigned char> &heightMap, float x, float z);

#endif