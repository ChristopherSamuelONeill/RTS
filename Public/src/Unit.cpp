#include "Unit.h"

Unit::Unit()
{
}

Unit::Unit(string path, int id , Vector2f pos, float rot)
{
	m_bUnitHasATarget = false;
	fstream file;
	string lineData;
	string temp;
	int textureId = 0;
	m_Gametextures = TextureObject::getInstance();
	file.open("Assets/res/units/" + path + ".txt");

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
			else if (temp == "u")
			{
				UnitData >> sid;
				if (sid == id)
				{
					m_iId = id;
					m_bMilitary = false;
				}


			}
			else if (temp == "m")
			{
				
				UnitData >> sid;
				if (sid == id)
				{
					float x = 0;
					float y = 0;
					m_iId = id;
					UnitData >> m_sName >> m_sType >> m_iAgeFrom >> m_iAgeTo >> m_iMaxHealth >> m_iMultiAttack >> m_iAttDmg[0] >> m_sAttackType[0] >> m_fAttackRng[0] >> m_fRateOfAtt[0] >> m_iAttDmg[1] >> m_sAttackType[1] >> m_fAttackRng[1] >> m_fRateOfAtt[1] >> m_iAttDmg[2] >> m_sAttackType[2] >> m_fAttackRng[2] >> m_fRateOfAtt[2] >> m_sArmour >> m_iaDeffFromType[0] >> m_iaDeffFromType[1] >> m_iaDeffFromType[2] >> m_iaDeffFromType[3] >> m_iaDeffFromType[4] >> m_iaDeffFromType[5] >> m_iaDeffFromType[6] >> m_iaDeffFromType[7];
					UnitData >> m_iAbilityID >> m_fMovementSpeed >> m_iCarryCap >> m_fSightRange;
					UnitData >> m_aiPrice[0] >> m_aiPrice[1] >> m_aiPrice[2] >> m_aiPrice[3] >> m_aiPrice[4] >> m_aiPrice[5] >> m_aiPrice[6] >> m_aiPrice[7] >> m_aiPrice[8] >> m_aiPrice[9];
					UnitData >> m_afCost[0] >> m_afCost[1] >> m_afCost[2] >> m_afCost[3] >> m_afCost[4] >> m_afCost[5] >> m_afCost[6] >> m_afCost[7] >> m_afCost[8];
					UnitData >> m_afAttackCost[0] >> m_afAttackCost[1] >> m_afAttackCost[2] >> m_afAttackCost[3] >> m_afAttackCost[4] >> m_afAttackCost[5] >> m_afAttackCost[6] >> m_afAttackCost[7] >> m_afAttackCost[8];
					UnitData >> textureId >> x >> y;
					m_sfSize = Vector2f(x, y);
					m_bMilitary = true;
					cout << "Texture id " << textureId << endl;
				}
				


			}
			

		}
	}


	file.close();

	for (int i = 0; i < 3; i++)
	{
		m_fAttackRng[i] = m_fAttackRng[i] * 100; // 100 pixels is a meter
	}
	
	m_fMovementSpeed = m_fMovementSpeed * 100;
	m_fTimeSinceLastAttack = 0.0f;
	m_bAlive = true;
	m_fSightRange = m_fSightRange * 100; // 100 pixels is a meter

	m_fCurrentHealth = m_iMaxHealth;
	cout << endl;
	cout << "Millitary? : " << m_bMilitary << endl;
	cout << "ID : " << m_iId << endl;
	cout << "Name : " << m_sName << endl;
	cout << "Health : " << m_iMaxHealth << endl;
	cout << "Attack : " << m_iAttDmg[0] << endl;
	cout << "Attack Type : " << m_sAttackType[0] << endl;
	cout << "Attack Range : " << m_fAttackRng[0] << endl;
	cout << "Attack Rate : " << m_fRateOfAtt[0] << endl;
	cout << "Deffence : " << m_sArmour << endl;
	cout << "m_fMovementSpeed " << m_fMovementSpeed << endl;
	cout << "Melle : " << m_iaDeffFromType[0] << endl;
	cout << "Sword : " << m_iaDeffFromType[1] << endl;
	cout << "Spear : " << m_iaDeffFromType[2] << endl;
	cout << "Arrow : " << m_iaDeffFromType[3] << endl;
	cout << "Bullet : " << m_iaDeffFromType[4] << endl;
	cout << "Other : " << m_iaDeffFromType[5] << endl;
	cout << "Carry : " << m_iCarryCap << endl;
	cout << "Sight : " << m_fSightRange << endl;
	cout << "X : " << m_sfSize.x << endl;
	cout << "Y : " << m_sfSize.y << endl;

	m_sfTexture = m_Gametextures->m_vUnitTextures[textureId];
	m_sfPosition = pos;
	
	m_fRotation = rot;

	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfUnitSprite.setPosition(m_sfRect.getPosition());
	m_sfUnitSprite.setTexture(m_sfTexture);
	m_sfUnitSprite.setOrigin(m_sfSize / 2.0f);
	m_sfUnitSprite.setRotation(m_fRotation);





}

void Unit::draw(RenderTarget & target, RenderStates states) const
{
	
	target.draw(m_sfRect);
	target.draw(m_sfUnitSprite);
}

void Unit::update(float dt)
{

	//do we have a target ? 
	if (m_bUnitHasATarget)
	{
		//cout << "Attacking PLayer " << m_iPlayerIdOfTarget << " unit " << m_iUnitIdOfTarget << endl;
	}

	//ensure all emements are up to date
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfUnitSprite.setPosition(m_sfRect.getPosition());
	m_sfUnitSprite.setTexture(m_sfTexture);
	m_sfUnitSprite.setRotation(m_fRotation);

	m_fTimeSinceLastAttack += dt;
}

void Unit::checkforAi(vector<Unit> otherPlayersUnits, int otherPlayerId)
{
	
	float closestEnemy = 999999.0f;
	m_fDistanceToTarget = 999999.0f;
	int idOfClostEnemy = -1;

	for (int i = 0; i < otherPlayersUnits.size(); i++)
	{
		//check distance
		float x = (m_sfPosition.x - otherPlayersUnits[i].m_sfPosition.x);
		float y = (m_sfPosition.y - otherPlayersUnits[i].m_sfPosition.y);
		float dist = sqrt((x * x) + (y * y));
		if (dist <= m_fSightRange && otherPlayersUnits[i].m_bAlive)
		{
			if (dist < closestEnemy)
			{
				closestEnemy = dist;
				idOfClostEnemy = i;
			}
		}
		else
		{
			// to far ignore
		}
	}

	if (idOfClostEnemy != -1)
	{
		// we have found an ememy
		m_bUnitHasATarget = true;
		if (closestEnemy < m_fDistanceToTarget)
		{
			m_iPlayerIdOfTarget = otherPlayerId;
			m_iUnitIdOfTarget = idOfClostEnemy;

		}

	}
	else
	{
		m_bUnitHasATarget = false;
		m_fDistanceToTarget = 999999999.0f;
		m_iPlayerIdOfTarget = 0;
		m_iUnitIdOfTarget = 0;
	}
	

}

void Unit::moveForwards(float dt)
{
	float currentAngleOfRotation = m_fRotation * (M_PI / 180);
	m_sfPosition.x += dt * m_fMovementSpeed * sinf(currentAngleOfRotation);
	m_sfPosition.y -= dt * m_fMovementSpeed * cosf(currentAngleOfRotation);

}

void Unit::turnTowards(float angle , float dt)
{
	// find unit orientatian
	if (m_fRotation < 0)//negative
	{
		m_fRotation = 360 + m_fRotation;
	}
	else if (m_fRotation > 360)
	{
		m_fRotation = m_fRotation - 360;
	}
	int unitAngle = m_fRotation;


	
	// find unit orientatian
	if (angle < 0)//negative
	{
		angle = 360 + angle;
	}
	else if (angle > 360)
	{
		angle = angle - 360;
	}

	//find the difference between the angles
	float angleDiff = abs(m_fRotation - angle);

	//if the difference is greaten than 180 reverse the direction steering
	if (angleDiff > 180)
	{
		//decide how to drive
		if (unitAngle + 5 < angle)m_fRotation = m_fRotation + (dt * -(m_fMovementSpeed / 2));
		else if (angle + 5 < unitAngle)m_fRotation = m_fRotation + (dt *  (m_fMovementSpeed / 2));
		else m_fRotation = angle;
	}
	else
	{
		//decide how to drive
		if (unitAngle + 5 < angle)m_fRotation = m_fRotation + (dt * (m_fMovementSpeed / 2));
		else if (angle + 5 < unitAngle)m_fRotation = m_fRotation + (dt - (m_fMovementSpeed / 2));
		else m_fRotation = angle;
	}

}

void Unit::attack(Unit &otherPlayersUnit, int id)
{
	

	if (m_fTimeSinceLastAttack >= (1 / m_fRateOfAtt[0]))
	{
		cout << "Player : " << id << " " << m_sName << " Attacking !" << endl;
		otherPlayersUnit.takeDamage(m_iAttDmg[0], m_sAttackType[0]);
		m_fTimeSinceLastAttack = 0.0f;
	}
}
	

void Unit::takeDamage(float amount, string type)
{
	int iType = 0;
	if (type == "melee")iType = 0;
	if (type == "sword")iType = 1;
	if (type == "spear")iType = 2;
	if (type == "brute")iType = 3;
	if (type == "arrow")iType = 4;
	if (type == "bullet")iType = 5;
	if (type == "explosion")iType = 6;
	if (type == "other")iType = 7;

	amount = amount - m_iaDeffFromType[iType];
	if (amount < 0) amount = 0;
	
	m_fCurrentHealth -= amount;

	if (m_fCurrentHealth <= 0)m_bAlive = false;

	cout << m_sName << " health : " << m_fCurrentHealth << endl;
}
 