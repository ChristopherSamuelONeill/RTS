#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>
#include <math.h>

#include "Unit.h"
#include "Building.h"


using namespace sf;
using namespace std;

class TeamPlayer
{

private:

	string m_sName;
	string m_sNation;

public:

	TeamPlayer();
	TeamPlayer(int team, string nation, int id);

	vector<Unit> m_vUnits; // the TeamPlayers Units
	vector<Building> m_vBuildings; // the players buildings


	int m_iTeam;
	int m_iId;

	void spawnUnit(string path, int id, Vector2f pos, float rot);
	void spawnBuilding(string path, int id, Vector2f pos, float rot);

	void update(float dt);

	void findTarget(vector<Unit> otherPlayersUnits, int otherPlayerId);
	void DecisionOnTarget(vector<Unit> &otherPlayersUnits, int otherPlayerId, float dt);

};




