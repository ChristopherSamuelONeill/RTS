#include "TeamPlayer.h"

TeamPlayer::TeamPlayer()
{
}

TeamPlayer::TeamPlayer(int team, string nation, int id)
{
	m_sNation = nation;
	m_iTeam = team;
	m_sName = "Player";
	m_iId = id;
}

void TeamPlayer::spawnUnit(string path, int id,  Building &targetBuilding)
{
	targetBuilding.spawnUnit(path, id);


}

void TeamPlayer::spawnBuilding(string path, int id, Vector2f pos, float rot)
{
	m_vBuildings.push_back(Building(id, pos, rot, path));
}

void TeamPlayer::update(float dt)
{
	for (int i = 0; i < m_vBuildings.size(); i++)
	{
		string buildingTest = m_vBuildings[i].update(dt);

		if (buildingTest == "spawnUnit")
		{
			cout << "spawned Unit" << endl;
			m_vUnits.push_back(Unit(m_vBuildings[i].m_sUnitPath, m_vBuildings[i].m_iIdOfSpawningUnit, m_vBuildings[i].m_sfUnitSpawnPos, m_vBuildings[i].m_fRotation));
		}

	}
	for (int i = 0; i < m_vUnits.size(); i++)
	{
		m_vUnits[i].update(dt);
	}
}

void TeamPlayer::findTarget(vector<Unit> otherPlayersUnits, int otherPlayerId)
{

	//loop each of our units
	for (int i = 0; i < m_vUnits.size(); i++)
	{
		m_vUnits[i].checkforAi(otherPlayersUnits, otherPlayerId);
	}
}

void TeamPlayer::DecisionOnTarget(vector<Unit> &otherPlayersUnits, int otherPlayerId,float dt)
{
	//loop each of our units
	for (int i = 0; i < m_vUnits.size(); i++)
	{
		if (m_vUnits[i].m_bAlive)
		{
			if (m_vUnits[i].m_bUnitHasATarget)
			{
				if (m_vUnits[i].m_iPlayerIdOfTarget == otherPlayerId)
				{
					for (int x = 0; x < otherPlayersUnits.size(); x++)
					{
						if (x == m_vUnits[i].m_iUnitIdOfTarget)
						{
							// this is this units target
							float xPos = (m_vUnits[i].m_sfPosition.x - otherPlayersUnits[x].m_sfPosition.x);
							float y = (m_vUnits[i].m_sfPosition.y - otherPlayersUnits[x].m_sfPosition.y);
							float dist = sqrt((xPos * xPos) + (y * y));

							//find angle between
							float angle = atan2((otherPlayersUnits[x].m_sfPosition.y - m_vUnits[i].m_sfPosition.y), (otherPlayersUnits[x].m_sfPosition.x - m_vUnits[i].m_sfPosition.x))*(180 / M_PI);
							angle += 90;
							if (angle < 0) angle = 360 + angle;
							else if (angle > 360) angle = angle - 360;


							if (dist > m_vUnits[i].m_fAttackRng[0])
							{

								// need to walk towards

								m_vUnits[i].turnTowards(angle, dt);
								//if(m_iId == 0) cout << angle << "  " << m_vUnits[i].m_fRotation << endl;
								if (m_vUnits[i].m_fRotation == angle) m_vUnits[i].moveForwards(dt);
							}
							else
							{
								m_vUnits[i].turnTowards(angle, dt);
								m_vUnits[i].attack(otherPlayersUnits[x], m_iId);
							}
							

						}
					}

				}
			}
		}
		
		
	}
}



