#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>

#include "StatManagerBuilding.h"

using namespace std;
using namespace sf;

class BuildingObject
{
public:
	BuildingObject(); // \brief Default constructor of Texture Obejct

	static bool bInstanceFlag;
	static BuildingObject *buildingObject;
	static BuildingObject* getInstance();

	void loadBuildings();

	bool m_bLoaded = false;

	// 0 England
	// 1 Italy
	vector<vector<StatManagerBuilding>> *m_vBuildings;

};
