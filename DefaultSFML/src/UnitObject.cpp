#include "UnitObject.h"

bool UnitObject::bInstanceFlag = false;
UnitObject* UnitObject::unitObject = nullptr;

UnitObject::UnitObject()
{
}

UnitObject * UnitObject::getInstance()
{

	if (!bInstanceFlag) // return the singleton window class
	{
		unitObject = new UnitObject();
		bInstanceFlag = true;
		return unitObject;
	}
	else
	{
		return unitObject;
	}
}

void UnitObject::loadUnits()
{
	if (!m_bLoaded)
	{
	

		fstream file;
		string lineData;
		string temp;

		//England
		cout << "Loading England Units... ";
		file.open("Assets/res/units/England.txt");

		m_vUnits.push_back(vector<StatManagerUnit>()); // empty team

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
					StatManagerUnit temp;
					temp.m_bMilitary = false;
					float x = 0;
					float y = 0;
					UnitData >> temp.m_iId >> temp.m_sName >> temp.m_sType >> temp.m_iAgeFrom >> temp.m_iAgeTo >> temp.m_iMaxHealth >> temp.m_iMultiAttack >> temp.m_iAttDmg[0] >> temp.m_sAttackType[0] >> temp.m_fAttackRng[0] >> temp.m_fRateOfAtt[0] >> temp.m_iAttDmg[1] >> temp.m_sAttackType[1] >> temp.m_fAttackRng[1] >> temp.m_fRateOfAtt[1] >> temp.m_iAttDmg[2] >> temp.m_sAttackType[2] >> temp.m_fAttackRng[2] >> temp.m_fRateOfAtt[2] >> temp.m_sArmour >> temp.m_iaDeffFromType[0] >> temp.m_iaDeffFromType[1] >> temp.m_iaDeffFromType[2] >> temp.m_iaDeffFromType[3] >> temp.m_iaDeffFromType[4] >> temp.m_iaDeffFromType[5] >> temp.m_iaDeffFromType[6] >> temp.m_iaDeffFromType[7];
					UnitData >> temp.m_iAbilityID >> temp.m_fMovementSpeed >> temp.m_iCarryCap >> temp.m_fSightRange;
					UnitData >> temp.m_aiPrice[0] >> temp.m_aiPrice[1] >> temp.m_aiPrice[2] >> temp.m_aiPrice[3] >> temp.m_aiPrice[4] >> temp.m_aiPrice[5] >> temp.m_aiPrice[6] >> temp.m_aiPrice[7] >> temp.m_aiPrice[8] >> temp.m_aiPrice[9];
					UnitData >> temp.m_afCost[0] >> temp.m_afCost[1] >> temp.m_afCost[2] >> temp.m_afCost[3] >> temp.m_afCost[4] >> temp.m_afCost[5] >> temp.m_afCost[6] >> temp.m_afCost[7] >> temp.m_afCost[8];
					UnitData >> temp.m_afAttackCost[0] >> temp.m_afAttackCost[1] >> temp.m_afAttackCost[2] >> temp.m_afAttackCost[3] >> temp.m_afAttackCost[4] >> temp.m_afAttackCost[5] >> temp.m_afAttackCost[6] >> temp.m_afAttackCost[7] >> temp.m_afAttackCost[8];
					UnitData >> x >> y;
					temp.m_sfSize = Vector2f(x, y);

					for (int i = 0; i < 3; i++)
					{
						temp.m_fAttackRng[i] = temp.m_fAttackRng[i] * 100; // 100 pixels is a meter
					}

					temp.m_fMovementSpeed = temp.m_fMovementSpeed * 100;
					temp.m_fSightRange = temp.m_fSightRange * 100; // 100 pixels is a meter

					m_vUnits[0].push_back(temp);
					
				

				}
				else if (temp == "m")
				{
					StatManagerUnit temp;
					temp.m_bMilitary = true;
					float x = 0;
					float y = 0;
					UnitData >> temp.m_iId >> temp.m_sName >> temp.m_sType >> temp.m_iAgeFrom >> temp.m_iAgeTo >> temp.m_iMaxHealth >> temp.m_iMultiAttack >> temp.m_iAttDmg[0] >> temp.m_sAttackType[0] >> temp.m_fAttackRng[0] >> temp.m_fRateOfAtt[0] >> temp.m_iAttDmg[1] >> temp.m_sAttackType[1] >> temp.m_fAttackRng[1] >> temp.m_fRateOfAtt[1] >> temp.m_iAttDmg[2] >> temp.m_sAttackType[2] >> temp.m_fAttackRng[2] >> temp.m_fRateOfAtt[2] >> temp.m_sArmour >> temp.m_iaDeffFromType[0] >> temp.m_iaDeffFromType[1] >> temp.m_iaDeffFromType[2] >> temp.m_iaDeffFromType[3] >> temp.m_iaDeffFromType[4] >> temp.m_iaDeffFromType[5] >> temp.m_iaDeffFromType[6] >> temp.m_iaDeffFromType[7];
					UnitData >> temp.m_iAbilityID >> temp.m_fMovementSpeed >> temp.m_iCarryCap >> temp.m_fSightRange;
					UnitData >> temp.m_aiPrice[0] >> temp.m_aiPrice[1] >> temp.m_aiPrice[2] >> temp.m_aiPrice[3] >> temp.m_aiPrice[4] >> temp.m_aiPrice[5] >> temp.m_aiPrice[6] >> temp.m_aiPrice[7] >> temp.m_aiPrice[8] >> temp.m_aiPrice[9];
					UnitData >> temp.m_afCost[0] >> temp.m_afCost[1] >> temp.m_afCost[2] >> temp.m_afCost[3] >> temp.m_afCost[4] >> temp.m_afCost[5] >> temp.m_afCost[6] >> temp.m_afCost[7] >> temp.m_afCost[8];
					UnitData >> temp.m_afAttackCost[0] >> temp.m_afAttackCost[1] >> temp.m_afAttackCost[2] >> temp.m_afAttackCost[3] >> temp.m_afAttackCost[4] >> temp.m_afAttackCost[5] >> temp.m_afAttackCost[6] >> temp.m_afAttackCost[7] >> temp.m_afAttackCost[8];
					UnitData >> x >> y;
					temp.m_sfSize = Vector2f(x, y);
					
					for (int i = 0; i < 3; i++)
					{
						temp.m_fAttackRng[i] = temp.m_fAttackRng[i] * 100; // 100 pixels is a meter
					}

					temp.m_fMovementSpeed = temp.m_fMovementSpeed * 100;
					temp.m_fSightRange = temp.m_fSightRange * 100; // 100 pixels is a meter
					
					m_vUnits[0].push_back(temp);

				}


			}
		}
		file.close();
		cout << "Finished" << endl;

		//Italy
		cout << "Loading Italy Units... ";
		file.open("Assets/res/units/Italy.txt");

		m_vUnits.push_back(vector<StatManagerUnit>()); // empty team

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
					StatManagerUnit temp;
					temp.m_bMilitary = false;
					float x = 0;
					float y = 0;
					UnitData >> temp.m_iId >> temp.m_sName >> temp.m_sType >> temp.m_iAgeFrom >> temp.m_iAgeTo >> temp.m_iMaxHealth >> temp.m_iMultiAttack >> temp.m_iAttDmg[0] >> temp.m_sAttackType[0] >> temp.m_fAttackRng[0] >> temp.m_fRateOfAtt[0] >> temp.m_iAttDmg[1] >> temp.m_sAttackType[1] >> temp.m_fAttackRng[1] >> temp.m_fRateOfAtt[1] >> temp.m_iAttDmg[2] >> temp.m_sAttackType[2] >> temp.m_fAttackRng[2] >> temp.m_fRateOfAtt[2] >> temp.m_sArmour >> temp.m_iaDeffFromType[0] >> temp.m_iaDeffFromType[1] >> temp.m_iaDeffFromType[2] >> temp.m_iaDeffFromType[3] >> temp.m_iaDeffFromType[4] >> temp.m_iaDeffFromType[5] >> temp.m_iaDeffFromType[6] >> temp.m_iaDeffFromType[7];
					UnitData >> temp.m_iAbilityID >> temp.m_fMovementSpeed >> temp.m_iCarryCap >> temp.m_fSightRange;
					UnitData >> temp.m_aiPrice[0] >> temp.m_aiPrice[1] >> temp.m_aiPrice[2] >> temp.m_aiPrice[3] >> temp.m_aiPrice[4] >> temp.m_aiPrice[5] >> temp.m_aiPrice[6] >> temp.m_aiPrice[7] >> temp.m_aiPrice[8] >> temp.m_aiPrice[9];
					UnitData >> temp.m_afCost[0] >> temp.m_afCost[1] >> temp.m_afCost[2] >> temp.m_afCost[3] >> temp.m_afCost[4] >> temp.m_afCost[5] >> temp.m_afCost[6] >> temp.m_afCost[7] >> temp.m_afCost[8];
					UnitData >> temp.m_afAttackCost[0] >> temp.m_afAttackCost[1] >> temp.m_afAttackCost[2] >> temp.m_afAttackCost[3] >> temp.m_afAttackCost[4] >> temp.m_afAttackCost[5] >> temp.m_afAttackCost[6] >> temp.m_afAttackCost[7] >> temp.m_afAttackCost[8];
					UnitData >> x >> y;
					temp.m_sfSize = Vector2f(x, y);

					for (int i = 0; i < 3; i++)
					{
						temp.m_fAttackRng[i] = temp.m_fAttackRng[i] * 100; // 100 pixels is a meter
					}

					temp.m_fMovementSpeed = temp.m_fMovementSpeed * 100;
					temp.m_fSightRange = temp.m_fSightRange * 100; // 100 pixels is a meter

					m_vUnits[1].push_back(temp);



				}
				else if (temp == "m")
				{
					StatManagerUnit temp;
					temp.m_bMilitary = true;
					float x = 0;
					float y = 0;
					UnitData >> temp.m_iId >> temp.m_sName >> temp.m_sType >> temp.m_iAgeFrom >> temp.m_iAgeTo >> temp.m_iMaxHealth >> temp.m_iMultiAttack >> temp.m_iAttDmg[0] >> temp.m_sAttackType[0] >> temp.m_fAttackRng[0] >> temp.m_fRateOfAtt[0] >> temp.m_iAttDmg[1] >> temp.m_sAttackType[1] >> temp.m_fAttackRng[1] >> temp.m_fRateOfAtt[1] >> temp.m_iAttDmg[2] >> temp.m_sAttackType[2] >> temp.m_fAttackRng[2] >> temp.m_fRateOfAtt[2] >> temp.m_sArmour >> temp.m_iaDeffFromType[0] >> temp.m_iaDeffFromType[1] >> temp.m_iaDeffFromType[2] >> temp.m_iaDeffFromType[3] >> temp.m_iaDeffFromType[4] >> temp.m_iaDeffFromType[5] >> temp.m_iaDeffFromType[6] >> temp.m_iaDeffFromType[7];
					UnitData >> temp.m_iAbilityID >> temp.m_fMovementSpeed >> temp.m_iCarryCap >> temp.m_fSightRange;
					UnitData >> temp.m_aiPrice[0] >> temp.m_aiPrice[1] >> temp.m_aiPrice[2] >> temp.m_aiPrice[3] >> temp.m_aiPrice[4] >> temp.m_aiPrice[5] >> temp.m_aiPrice[6] >> temp.m_aiPrice[7] >> temp.m_aiPrice[8] >> temp.m_aiPrice[9];
					UnitData >> temp.m_afCost[0] >> temp.m_afCost[1] >> temp.m_afCost[2] >> temp.m_afCost[3] >> temp.m_afCost[4] >> temp.m_afCost[5] >> temp.m_afCost[6] >> temp.m_afCost[7] >> temp.m_afCost[8];
					UnitData >> temp.m_afAttackCost[0] >> temp.m_afAttackCost[1] >> temp.m_afAttackCost[2] >> temp.m_afAttackCost[3] >> temp.m_afAttackCost[4] >> temp.m_afAttackCost[5] >> temp.m_afAttackCost[6] >> temp.m_afAttackCost[7] >> temp.m_afAttackCost[8];
					UnitData >> x >> y;
					temp.m_sfSize = Vector2f(x, y);

					for (int i = 0; i < 3; i++)
					{
						temp.m_fAttackRng[i] = temp.m_fAttackRng[i] * 100; // 100 pixels is a meter
					}

					temp.m_fMovementSpeed = temp.m_fMovementSpeed * 100;
					temp.m_fSightRange = temp.m_fSightRange * 100; // 100 pixels is a meter

					m_vUnits[1].push_back(temp);

				}


			}
		}
		file.close();
		cout << "Finished" << endl;



		
	}
}
