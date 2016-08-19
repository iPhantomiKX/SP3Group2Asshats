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
        if (line[0] == '#' || line == "")   // empty line OR comment
            continue;

        ++numOfLines;
    }

    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);

    switch (file_type)
    {
    case FILE_MONSTERDATA:
        //MonsterFactory::SetMonsterTypesQuantity(numOfLines);
        LoadMonsterData(fileStream);
        break;

    case FILE_LEVELGENERATIONDATA:
        LoadLevelGenerationData(fileStream);
        break;

    case FILE_LEVELMAPDATA:
        LoadLevelMapData(fileStream);
        break;

    case FILE_SAVEDATA:
        LoadSaveData(fileStream);
        break;

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

void LoadMonsterData(std::ifstream& fileStream)
{
    while (!fileStream.eof())
    {
        std::string line;
        std::getline(fileStream, line);

        if (line == "" || line[0] == '#')   // empty line OR comment
            continue;

        std::stringstream dataStream(line);
        std::string data;
        std::getline(dataStream, data, ',');

        // first content is name of monster
        std::string tempName = data;


        int stats[5] = {};
        for (int i = 0; i < 5; ++i)
        {
            std::getline(dataStream, data, ',');
            stats[i] = std::stoi(data);
        }
        //// second content is health
        //std::getline(dataStream, data, ',');
        //stats[0] = std::stoi(data);
        //
        //// third content is capture rate
        //std::getline(dataStream, data, ',');
        //stats[1] = std::stoi(data);
        //
        //// fourth content is aggression
        //std::getline(dataStream, data, ',');
        //stats[2] = std::stoi(data);
        //
        //// fifth content is fear
        //std::getline(dataStream, data, ',');
        //stats[3] = std::stoi(data);
        //
        //// sixth content is strategy enum value
        //std::getline(dataStream, data);
        //stats[4] = std::stoi(data);

        // push into map
        MonsterFactory::AddToMap(tempName, stats);
    }
    
}

void LoadLevelGenerationData(std::ifstream& fileStream)
{

}

void LoadLevelMapData(std::ifstream& fileStream)
{

}

void LoadSaveData(std::ifstream& fileStream)
{

}