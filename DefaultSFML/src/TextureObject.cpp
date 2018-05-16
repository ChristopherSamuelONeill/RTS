#include "TextureObject.h"

bool TextureObject::bInstanceFlag = false;
TextureObject* TextureObject::textureObject = nullptr;


TextureObject::TextureObject()
{
}

TextureObject * TextureObject::getInstance()
{

	if (!bInstanceFlag) // return the singleton window class
	{
		textureObject = new TextureObject();
		bInstanceFlag = true;
		return textureObject;
	}
	else
	{
		return textureObject;
	}
}

void TextureObject::loadTextures()
{
	if (!m_bLoaded)
	{
		cout << "Loading Textures... ";

		Texture sfTempTexture;

		//base colours------------------------------------------

		

		//Background Textures---------------------------------------------------------------------

		//Grass
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/GreenGrass.png"))
		{
			cout << "Error: GreenGrass.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Grass
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/YellowGrass.png"))
		{
			cout << "Error: YellowGrass.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Sand
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/GreySand.png"))
		{
			cout << "Error: GreySand.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Sand
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/YellowSand.png"))
		{
			cout << "Error: YellowSand.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Concrete
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/Concrete.png"))
		{
			cout << "Error: Concrete.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);


		//Dirt
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/DirtPath.png"))
		{
			cout << "Error: DirtPath.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);

		//Ice
		if (!sfTempTexture.loadFromFile("./Assets/textures/Backgrounds/Ice.png"))
		{
			cout << "Error: Ice.png was unable to load." << endl;
		};
		m_vBackgroundTextures.push_back(sfTempTexture);


		//Time Textures---------------------------------------------------------------------

		//Normal.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Normal.png"))
		{
			cout << "Error: Normal.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Day.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Day.png"))
		{
			cout << "Error: Day.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Summer.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Summer.png"))
		{
			cout << "Error: Summer.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Evening.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Evening.png"))
		{
			cout << "Error: Evening.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Night.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Night.png"))
		{
			cout << "Error: Night.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);

		//Winter.png
		if (!sfTempTexture.loadFromFile("./Assets/textures/Time of Day/Winter.png"))
		{
			cout << "Error: Winter.png was unable to load." << endl;
		};
		m_vTimeTextures.push_back(sfTempTexture);


		m_vUnitTextures.push_back(vector<Texture>());
		//units
		if (!sfTempTexture.loadFromFile("./Assets/textures/Units/England/placeHolder01.png"))
		{
			
		};
		m_vUnitTextures[0].push_back(sfTempTexture);

		m_vUnitTextures.push_back(vector<Texture>());
		if (!sfTempTexture.loadFromFile("./Assets/textures/Units/Italy/placeHolder01.png"))
		{
		
		};
		m_vUnitTextures[1].push_back(sfTempTexture);


		// ui
		if (!sfTempTexture.loadFromFile("./Assets/textures/Hud/TopBar/oldFashioned.png"))
		{
			cout << "Error: Winter.png was unable to load." << endl;
		};
		m_topBarTexture.push_back(sfTempTexture);


		//buildings
		if (!sfTempTexture.loadFromFile("./Assets/textures/Buildings/England/Testing.png"))
		{
			cout << "Error: Winter.png was unable to load." << endl;
		};
		m_vBuildPaceHolders.push_back(sfTempTexture);

		if (!sfTempTexture.loadFromFile("./Assets/textures/Buildings/Italy/Testing.png"))
		{
			cout << "Error: Winter.png was unable to load." << endl;
		};
		m_vBuildPaceHolders.push_back(sfTempTexture);

		cout << "Finished" << endl;
	}
}
