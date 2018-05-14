#ifndef TERRIAN_H
#define TERRIAN_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>


#include "TextureObject.h"
#include "Pathfinding.h"
#include "Profile.h"



using namespace sf;
using namespace std;

class Terrian : public Drawable
{

private:
	
	RectangleShape m_sfRect;
	Texture m_sfTexture;
	Sprite m_sfTerrianSprite; // \brief Sprite for the unit
	
	Vector2f m_sfPosition;
	Vector2f m_sfSize;
	float m_fRotation;

public:


	Terrian(); // \brief Default constructor of game object

	// \brief Overloaded constructor of game object
	// \param Path to the texture
	// \param bool Is this terrian passable
	Terrian(float rotation , Texture texture ,Vector2f Size, Vector2f Pos,bool passable);

	void draw(RenderTarget& target, RenderStates states) const;
	void update();
	void setTexture(Texture newTexture);
	void setPosistion(Vector2f newPos);
	void setSize(Vector2f newSize);
	void incrementRotation(float increment);
};
#endif // !GAME_H