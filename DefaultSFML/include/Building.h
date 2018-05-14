#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>

#include "Sound.h"
#include "TextureObject.h"
#include "Selectable.h"
#include "Unit.h"

using namespace sf;
using namespace std;


class Building : public Drawable , public Selectable
{

private :

	Texture m_sfBuildingTexture;
	Sprite m_sfBuildingSprite;
	RectangleShape m_sfRect;

	Vector2f m_sfPosition;
	Vector2f m_sfSize;


	Vector2f m_sfRelativeUnitSpawnPos; // base read from file

	TextureObject *m_Gametextures;// \brief handle to all game textures

	

public:

	Building();

	Building(int id, Vector2f pos, float rot, string path);

	int m_iMaxHitPoints;
	float m_fCurrentHitPoints;
	int m_iId;
	bool m_bMilitary;
	string m_sName;

	void spawnUnit(string path, int id);

	string update(float dt);

	void draw(RenderTarget& target, RenderStates states) const;

	//spawning unit stuff
	bool m_bSpawningUnit;
	int m_iIdOfSpawningUnit;
	string m_sUnitPath;
	float m_fTimeofSpawn;
	Vector2f m_sfUnitSpawnPos; //actual
	float m_fRotation;



};