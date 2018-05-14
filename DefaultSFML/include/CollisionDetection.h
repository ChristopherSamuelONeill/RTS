#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>

using namespace std;
using namespace sf;

class CollisionDetection
{
public:
	bool operator()(RectangleShape A, RectangleShape B);



	
};
#endif