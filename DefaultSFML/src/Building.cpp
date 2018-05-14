#include "Building.h"

Building::Building()
{
}

Building::Building(int id , Vector2f pos, float rot, string path)
{
	fstream file;
	string lineData;
	string temp;
	int textureId = 0;
	m_Gametextures = TextureObject::getInstance();
	file.open("Assets/res/Buildings/" + path + ".txt");

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
				UnitData >> sid;
				if (sid == id)
				{
					float x = 0;
					float y = 0;

					UnitData >> m_sName >> m_iMaxHitPoints >> x >> y >> textureId;
					m_sfRelativeUnitSpawnPos = Vector2f(x, y);
					m_iId = id;
					m_bMilitary = false;
					m_fCurrentHitPoints = m_iMaxHitPoints;
				}


			}
			else if (temp == "m")
			{

				UnitData >> sid;
				if (sid == id)
				{
					float ox = 0;
					float oy = 0;

					float sx = 0;
					float sy = 0;

					UnitData >> m_bMilitary >>  m_sName >> m_iMaxHitPoints >> sx >> sy >> ox >> oy >> textureId;
					m_sfRelativeUnitSpawnPos = Vector2f(ox, oy);
					m_sfSize = Vector2f(sx, sy);

					m_iId = id;
					m_bMilitary = true;
				}

			}
		}
	}


	file.close();

	

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


	cout << endl << "Spawned " << m_sName << endl;


}

void Building::spawnUnit(int unitId)
{
}

void Building::update(float dt)
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
}

void Building::draw(RenderTarget & target, RenderStates states) const
{
	target.draw(m_sfBuildingSprite);
}
