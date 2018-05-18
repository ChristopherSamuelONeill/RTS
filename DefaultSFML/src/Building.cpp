#include "Building.h"

Building::Building()
{
	
}

Building::Building(int id , Vector2f pos, float rot, string path)
{

	m_bSpawningUnit = false;
	m_fTimeofSpawn = 0;


	//cal here
	m_sfUnitSpawnPos = Vector2f(-1000, -1000);
	

	//stuffs for rencering
	m_sfBuildingTexture = m_Gametextures->m_vBuildPaceHolders[textureId];
	m_sfPosition = pos;
	m_fRotation = rot;

	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfBuildingSprite.setPosition(m_sfRect.getPosition());
	m_sfBuildingSprite.setTexture(m_sfBuildingTexture);
	m_sfBuildingSprite.setOrigin(m_sfSize / 2.0f);
	m_sfBuildingSprite.setRotation(m_fRotation);


	//Clicking bound box
	m_sfCollisionRect = m_sfRect.getGlobalBounds();


	cout << "Spawned " << m_stats.m_sName << endl;


}

void Building::spawnUnit(int nation, int id)
{
	if (!m_bSpawningUnit)
	{
		m_bSpawningUnit = true;
		m_iIdOfSpawningUnit = id;
	}
	else
	{
		//add to queue

		//perhaps make it an object
	}
	
}

string Building::update(float dt)
{
	//ensure all emements are up to date
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	//m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfBuildingSprite.setPosition(m_sfRect.getPosition());
	m_sfBuildingSprite.setTexture(m_sfBuildingTexture);
	m_sfBuildingSprite.setRotation(m_fRotation);

	if (m_bSpawningUnit)
	{
		m_fTimeofSpawn += dt;
		if (m_fTimeofSpawn >= 1)
		{
			m_bSpawningUnit = false;
			m_fTimeofSpawn = 0;
			return "spawnUnit";
		}
	}

	return "";
}

void Building::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfBuildingSprite);
}
