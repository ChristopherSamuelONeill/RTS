#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include <iostream>
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

class TextureObject
{
public:
	TextureObject(); // \brief Default constructor of Texture Obejct

	static bool bInstanceFlag;
	static TextureObject *textureObject;
	static TextureObject* getInstance();

	bool m_bLoaded = false;


	void loadTextures(); // \brief Loads all of the textures needed for game just once


	//Scene texture
	vector<Texture> m_vBackgroundTextures; // \brief Texture for background
	vector<Texture> m_vTimeTextures; // \brief Texture for background
	
									 
	//0 England
	//1 Italy
	vector<vector<Texture>> m_vUnitTextures;

	vector<Texture> m_vBuildPaceHolders; 



	
	vector<Texture> m_topBarTexture;
	
};
#endif