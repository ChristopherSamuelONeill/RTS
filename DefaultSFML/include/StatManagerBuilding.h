#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class StatManagerBuilding
{
private:

public:

	StatManagerBuilding();

	int m_iNumOfWeapons; // number of attack 0 - 3

	int m_iAttDmg[3]; // \breif damage per successful attack
	string m_sAttackType[3]; // \breif the type of attack this building has (melle / sword / arrow)
	float m_fAttackRng[3]; // \breif the range from which this building can deal damage
	float m_fRateOfAtt[3]; // \breif attacks per second

	int m_aiPrice[10]; //wood , stone , coin , gold , iron , steel , goal , gunpowder , food , time
	float m_afCost[9]; //wood , stone , coin , gold , iron , steel , goal , gunpowder , food
	float m_afAttackCost[9]; //wood , stone , coin , gold , iron , steel , goal , gunpowder , food

	Vector2f m_sfRelativeUnitSpawnPos;
	int m_iMaxHitPoints; // total health
	int m_iId; // id from data base
	bool m_bMilitary; // is this buidling miltary or not
	string m_sName; // name of buidling
};