#include "BuildingObject.h"


bool BuildingObject::bInstanceFlag = false;
BuildingObject* BuildingObject::buildingObject = nullptr;

BuildingObject::BuildingObject()
{

}

BuildingObject * BuildingObject::getInstance()
{
	if (!bInstanceFlag) // return the singleton window class
	{
		buildingObject = new BuildingObject();
		bInstanceFlag = true;
		return buildingObject;
	}
	else
	{
		return buildingObject;
	}
}

void BuildingObject::loadBuildings()
{
	fstream file;
	string lineData;
	string temp;

	m_vBuildings->push_back(vector<StatManagerBuilding>()); // empty team
	file.open("Assets/res/Buildings/England.txt");

	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream UnitData(lineData);
			UnitData.str(lineData);
			int sid;
			UnitData >> temp;

			if (temp == "#")
			{
				//ingore . this line is a comment
			}
			else if (temp == "b")
			{
				

			}
			else if (temp == "m")
			{
				StatManagerBuilding temp;
				UnitData >> sid;
				

			}
		}
	}


	file.close();
}
