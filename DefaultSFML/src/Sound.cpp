#include "Sound.h"

bool SoundObject::bInstanceFlag = false;
SoundObject* SoundObject::soundObject = nullptr;


SoundObject * SoundObject::getInstance()
{
	if (!bInstanceFlag) // return the singleton window class
	{
		soundObject = new SoundObject();
		bInstanceFlag = true;
		return soundObject;
	}
	else
	{
		return soundObject;
	}
}

void SoundObject::loadSounds()
{
	cout << "Loading interface sounds ...";
	SoundBuffer temp;
	Sound stemp;

	//Interface Sounds -----------------------
	if (!temp.loadFromFile("./Assets/sounds/Ui/button.wav"))
	{
		cout << "Error : button.wav failed to load" << endl;
	}
	m_vBufferInterfaceSounds.push_back(temp);
	m_vInterfaceSounds.push_back(stemp);

	if (!temp.loadFromFile("./Assets/sounds/Ui/failedClick.wav"))
	{
		cout << "Error : failedClick.wav failed to load" << endl;
	}
	m_vBufferInterfaceSounds.push_back(temp);
	m_vInterfaceSounds.push_back(stemp);

	cout << "Finished" << endl;

	//FX Sounds -----------------------
	cout << "Loading FX ...";


	

	cout << "Finished" << endl;

	
}
