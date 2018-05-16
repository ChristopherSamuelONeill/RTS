#pragma once


#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>

#define _USE_MATH_DEFINES

#include "Sound.h"
#include "TextureObject.h"
#include <math.h>
#include "StatManagerUnit.h"
#include "UnitObject.h"



using namespace sf;
using namespace std;

class Unit : public Drawable 
{

private:

	RectangleShape m_sfRect;
	Texture m_sfTexture;
	Sprite m_sfUnitSprite; // \brief Sprite for the Car


public:

	// Attack stuff
	bool m_bUnitHasATarget;
	int m_iPlayerIdOfTarget;
	int m_iUnitIdOfTarget;
	float m_fDistanceToTarget;
	float m_fRotation;
	float m_fTimeSinceLastAttack;

	bool m_bAlive;
	float m_fCurrentHealth; // \ breif current health of Unit (only int val will be displayed)


	Vector2f m_sfPosition;
	


	Unit(); // \brief Default constructor of game object

	// \brief Overloaded constructor of game object
	// \param Path to the file
	// \param the id of the Unit
	Unit(int nation, int id, Vector2f pos,float rot);

	void draw(RenderTarget& target, RenderStates states) const;

	void update(float dt);

	void checkforAi(vector<Unit> otherPlayersUnits, int otherPlayerId);

	TextureObject *m_Gametextures;// \brief handle to all game textures
	UnitObject *m_GameUnits;// \brief handle to all game units
	
	StatManagerUnit m_UnitStats;

	void moveForwards(float dt);
	void turnTowards(float angle, float dt);

	void attack(Unit &otherPlayersUnit,int id);
	void takeDamage(float amount, string type);
};
