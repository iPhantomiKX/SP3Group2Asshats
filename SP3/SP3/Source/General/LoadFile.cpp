/******************************************************************************/
/*!
\file	LoadFile.cpp
\author Foo Jing Ting
\par	email: 152856H@mymail.nyp.edu.sg
\brief
Function to read CSV files for game data
*/
/******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include "LoadFile.h"

#include "../GameObject/MonsterFactory.h"

bool LoadFile(const char* file_path, FILE_TYPE file_type)
{
    std::ifstream fileStream(file_path, std::ios::binary);
    if (!fileStream.is_open()) {
        std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
        return false;
    }

    int numOfLines = 0;

    std::string line;
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        ++numOfLines;
    }

    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);

    switch (file_type)
    {
    case FILE_MONSTERDATA:
    {
                             MonsterFactory::SetMonsterTypesQuantity(numOfLines);
                             LoadMonsterData();
                             break;
    }

    case FILE_SAVEDATA:
    {
                          break;
    }

    }

    //unsigned int allocateCount = 0;
    //while (!fileStream.eof())
    //{
    //    std::getline(fileStream, line);
    //
    //    std::stringstream dataStream(line);
    //    std::string data;
    //    std::getline(dataStream, data, ',');
    //
    //    // first content is name
    //    string tempName = data;
    //
    //    // second content is elixir cost
    //    std::getline(dataStream, data, ',');
    //    int tempElixirCost = std::stoi(data);
    //
}

void LoadMonsterData()
{

}

void LoadSaveData()
{

}