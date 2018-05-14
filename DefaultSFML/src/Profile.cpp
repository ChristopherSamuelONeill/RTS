#include "Profile.h"

bool Profile::bInstanceFlag = false;
Profile* Profile::profile = nullptr;


Profile * Profile::getInstance()
{
	if (!bInstanceFlag) // return the singleton window class
	{
		profile = new Profile();
		bInstanceFlag = true;
		return profile;
	}
	else
	{
		
		return profile;
	}
}


Profile::Profile(string location)
{
	fstream file;
	string lineData;
	string temp;

	file.open("Assets/profiles/" +location);
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			if (temp == "c")
			{
				//ingore
			}
			else if (temp == "s")
			{
				settings >> m_sfResolution.x >> m_sfResolution.y >> m_bFullscreen >> m_bTextures >> m_iGameAudioVolume >> m_iInterfaceAudioVolume >> m_iMusicAudioVolume;
			}
			else if (temp == "d")
			{
				settings >> m_sProfileName >> m_uilevel >> m_fXP >> m_uiPedestriansTotal >> m_uiunitsTotal >> m_uiCrashesTotal >> m_uiFatalitiesTotal >> m_fFlowRate;
			}
		}
		m_sProfile = m_sProfileName;
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/"<< location << endl;
	}

	file.close();
}


Profile::~Profile()
{
}

void Profile::saveProfile()
{
	ofstream ofile;
	ofile.open("Assets/profiles/" +m_sProfileName +".txt");
	if (ofile.is_open())
	{

		ofile << "c " << "x res " << "y res " << "full " << "texures " << "gme vl " << "ivl " << "mvl " << endl;
		ofile << "s " << m_sfResolution.x << " " << m_sfResolution.y << " " << m_bFullscreen << " " << m_bTextures << " " << m_iGameAudioVolume << " " << m_iMusicAudioVolume << " " << m_iInterfaceAudioVolume << endl;
		ofile << "c " << "name " << "level " << "xp " << "tPed " << "tunit " << "cTot " << "fTot " << "fRat " << endl;
		ofile << "d " << m_sProfileName << " " << m_uilevel << " " << m_fXP << " " << m_uiPedestriansTotal << " " << m_uiunitsTotal<< " " << m_uiCrashesTotal << " " << m_uiFatalitiesTotal << " " << m_fFlowRate<< " " << endl;
	}
	ofile.close();
}

bool Profile::loadProfile(string name)
{
	fstream file;
	string lineData;
	string temp;

	file.open("Assets/profiles/" + name +".txt");
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			if (temp == "c")
			{
				//ingore
			}
			else if (temp == "s")
			{
				settings >> m_sfResolution.x >> m_sfResolution.y >> m_bFullscreen >> m_bTextures >> m_iGameAudioVolume >> m_iInterfaceAudioVolume >> m_iMusicAudioVolume;
			}
			else if (temp == "d")
			{
				settings >> m_sProfileName >> m_uilevel >> m_fXP >> m_uiPedestriansTotal >> m_uiunitsTotal >> m_uiCrashesTotal >> m_uiFatalitiesTotal >> m_fFlowRate;
			}
		}
	}
	else
	{
		cout << "Couldnt Open file ... Assets/profiles/" << name + ".txt" << endl;
		return false;
	}

	return true;

	file.close();
}

void Profile::newProfile(string name)
{
	fstream file;
	string lineData;
	string temp;
	// load a deafualt profile
	file.open("Assets/profiles/default.txt");
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			if (temp == "c")
			{
				//ingore
			}
			else if (temp == "s")
			{
				settings >> m_sfResolution.x >> m_sfResolution.y >> m_bFullscreen >> m_bTextures >> m_iGameAudioVolume >> m_iInterfaceAudioVolume >> m_iMusicAudioVolume;
			}
			else if (temp == "d")
			{
				settings >> m_sProfileName >> m_uilevel >> m_fXP >> m_uiPedestriansTotal >> m_uiunitsTotal >> m_uiCrashesTotal >> m_uiFatalitiesTotal >> m_fFlowRate;
			}
		}
	}

	// set the name
	m_sProfileName = name;
	//and save
	saveProfile();

	//add to profile list
	vector<string> names;


	//read in existing names
	file.open("Assets/profiles/profileList.txt");
	if (file.is_open())
	{
		while (getline(file, lineData))
		{
			istringstream settings(lineData);
			settings.str(lineData);
			settings >> temp;
			names.push_back(temp);
		}
	}

	//add names back the the file
	ofstream ofile;
	
	ofile.open("Assets/profiles/profileList.txt");
	if (ofile.is_open())
	{
		for (int i = 0; i < names.size(); i++)
		{
			ofile << names[i] << endl;
		}

		//add the newest name
		ofile << m_sProfileName << endl;
	}

}
