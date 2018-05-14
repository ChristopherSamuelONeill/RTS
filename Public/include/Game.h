#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <sstream>


#include "Controller.h"
#include "Node.h"
#include "Pathfinding.h"

#include "CollisionDetection.h"
#include "Game.h"
#include "Sound.h"
#include "TextureObject.h"

#include "StatManagerUnit.h"
#include "Terrian.h"

#include "TeamPlayer.h"

#include "Profile.h"
#include "Achievement.h"

#include "Button.h"
#include "Clickable.h"
#include "Hoverable.h"
#include "Overlay.h"
#include "TextBox.h"


using namespace sf;
using namespace std;

class Game
{

private:





public:


	Game(); // \brief Default constructor of game object

			// \brief Overloaded constructor of game object
			// \param Path to the level
	Game(string dir);

	// \brief function to update scene
	// \param time change
	void updateScene(float dt);

	// \brief function to update scene
	// \param time change
	void drawScene(RenderWindow& window);

	// \brief function to clear scene
	void closeGame();

	void loopClickables(Vector2f pos);

	vector<Terrian> m_vTerrian; // \brief Tiles of terrian
	vector<TeamPlayer> m_vPlayers;
	TextureObject *m_Gametextures;// \brief handle to all game textures

	RectangleShape m_sfHudTopBarRect;
	Sprite m_sfHudTopBarSprite;
	Profile *m_currPlayer;


};
#endif // !GAME_H