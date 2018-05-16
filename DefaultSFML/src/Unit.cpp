#include "Unit.h"

Unit::Unit()
{
}

Unit::Unit(int nation, int id , Vector2f pos, float rot)
{
	//get objects
	m_GameUnits = UnitObject::getInstance();
	m_Gametextures = TextureObject::getInstance();

	//apply
	m_UnitStats = m_GameUnits->m_vUnits[nation][id];
	m_sfTexture = m_Gametextures->m_vUnitTextures[nation][id];

	//set units attributes
	m_fCurrentHealth = m_UnitStats.m_iMaxHealth;
	m_bUnitHasATarget = false;
	m_bAlive = true;
	m_fTimeSinceLastAttack = 0.0f;
	
	//posistion
	m_sfPosition = pos;
	m_fRotation = rot;

	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_UnitStats.m_sfSize);
	m_sfRect.setOrigin(m_UnitStats.m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfUnitSprite.setPosition(m_sfRect.getPosition());
	m_sfUnitSprite.setTexture(m_sfTexture);
	m_sfUnitSprite.setOrigin(m_UnitStats.m_sfSize / 2.0f);
	m_sfUnitSprite.setRotation(m_fRotation);


	cout << "Spawned " << m_UnitStats.m_sName << endl;


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
	m_sfRect.setSize(m_UnitStats.m_sfSize);
	m_sfRect.setOrigin(m_UnitStats.m_sfSize / 2.0f);
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
		if (dist <= m_UnitStats.m_fSightRange && otherPlayersUnits[i].m_bAlive)
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
	m_sfPosition.x += dt * m_UnitStats.m_fMovementSpeed * sinf(currentAngleOfRotation);
	m_sfPosition.y -= dt * m_UnitStats.m_fMovementSpeed * cosf(currentAngleOfRotation);

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
		if (unitAngle + 5 < angle)m_fRotation = m_fRotation + (dt * -(m_UnitStats.m_fMovementSpeed / 2));
		else if (angle + 5 < unitAngle)m_fRotation = m_fRotation + (dt *  (m_UnitStats.m_fMovementSpeed / 2));
		else m_fRotation = angle;
	}
	else
	{
		//decide how to drive
		if (unitAngle + 5 < angle)m_fRotation = m_fRotation + (dt * (m_UnitStats.m_fMovementSpeed / 2));
		else if (angle + 5 < unitAngle)m_fRotation = m_fRotation + (dt - (m_UnitStats.m_fMovementSpeed / 2));
		else m_fRotation = angle;
	}

}

void Unit::attack(Unit &otherPlayersUnit, int id)
{
	

	if (m_fTimeSinceLastAttack >= (1 / m_UnitStats.m_fRateOfAtt[0]))
	{
		cout << "Player : " << id << " " << m_UnitStats.m_sName << " Attacking !" << endl;
		otherPlayersUnit.takeDamage(m_UnitStats.m_iAttDmg[0], m_UnitStats.m_sAttackType[0]);
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

	amount = amount - m_UnitStats.m_iaDeffFromType[iType];
	if (amount < 0) amount = 0;
	
	m_fCurrentHealth -= amount;

	if (m_fCurrentHealth <= 0)m_bAlive = false;

	cout << m_UnitStats.m_sName << " health : " << m_fCurrentHealth << endl;
}
 