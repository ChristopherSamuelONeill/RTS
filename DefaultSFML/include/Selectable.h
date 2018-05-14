#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


using namespace std;
using namespace sf;



class Selectable
{
public:
	////////////////////////////////////////////////////////////
	/// \brief Overloaded Bool Function
	///
	/// Testes if the object has been clicked on
	///
	/// \param sfVmouseClick sf::Vector2f of where the mouse was clicked
	////////////////////////////////////////////////////////////
	bool m_bClicked(Vector2f sfVmouseClick);

protected:

	FloatRect m_sfCollisionRect;


private:

};


