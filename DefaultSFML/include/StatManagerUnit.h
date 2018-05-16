#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>




using namespace sf;
using namespace std;

class StatManagerUnit 
{

private:

	
	


public:


	StatManagerUnit(); // \brief Default constructor of game object

	void applyUpgrade(string type, string upgrade, float val);

	//Unit attributes
	bool m_bMilitary; //\weather this Unit can be captured or not
	int m_iId; // \breif the id of the Unit from the docs
	string m_sName; // \breif displayed name of the Unit
	int m_iMaxHealth; // \breif the health of the Unit when made ( can be alterted by upgrades)
	int m_iMultiAttack; // \Does this unit have more than 1 weapon 1 - 3
	int m_iAttDmg[3]; // \breif damage per successful attack
	string m_sAttackType[3]; // \breif the type of attack this Unit has (melle / sword / arrow)
	float m_fAttackRng[3]; // \breif the range from which this uni can deal damage
	float m_fRateOfAtt[3]; // \breif attacks per second
	string m_sArmour; // \breif type of armour (used for upgrades)
	float m_fMovementSpeed; // \brief movement speed of the uni in (m/s)
	int m_iaDeffFromType[8]; // melle , sword , spear , brute arrow , bullet , explosive , other
	int m_iCarryCap; //\breif the carry capacity of this Unit
	float m_fSightRange;
	int m_aiPrice[10]; //wood , stone , coin , gold , iron , steel , goal , gunpowder , food , time
	float m_afCost[9]; //wood , stone , coin , gold , iron , steel , goal , gunpowder , food
	float m_afAttackCost[9]; //wood , stone , coin , gold , iron , steel , goal , gunpowder , food
	int m_iAgeFrom;
	int m_iAgeTo;
	string m_sType;
	int m_iAbilityID;
	Vector2f m_sfSize;


};
