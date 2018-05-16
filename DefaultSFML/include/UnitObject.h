#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "StatManagerUnit.h"

using namespace std;
using namespace sf;

class UnitObject
{
public:
	UnitObject(); // \brief Default constructor of Texture Obejct

	static bool bInstanceFlag;
	static UnitObject *unitObject;
	static UnitObject* getInstance();

	void loadUnits();

	bool m_bLoaded = false;

	// 0 England
	// 1 Italy
	vector<vector<StatManagerUnit>> m_vUnits;

};
