/******************************************************************************/
/*!
\file	LoadFile.h
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Function to read CSV files for game data
*/
/******************************************************************************/
#ifndef LOAD_FILE_H
#define LOAD_FILE_H

enum FILE_TYPE
{
    FILE_MONSTERDATA,
    FILE_SAVEDATA,
    FILE_TOTAL
};

bool LoadFile(const char* file_path, FILE_TYPE file_type);

void LoadMonsterData();
void LoadSaveData();

#endif