#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>

#include "Node.h"

using namespace std;
using namespace sf;

class Pathfinding
{

public:

	// \brief Default Constructor for Pathfinding class
	Pathfinding();


	// \brief Overloaded Function to add a new node to the pathfinding class
	// \param hValue , float Huesristic value of the node
	// \param gValue , float movement cost of the node
	// \param index , int the node number in the list
	// \param accessable, bool avaible node or not
	void addunitNode( float hValue, float gValue, int index, Vector2f pos, bool accessable);

	// \brief Overloaded Function to add a new node to the pathfinding class
	// \param hValue , float Huesristic value of the node
	// \param gValue , float movement cost of the node
	// \param index , int the node number in the list
	// \param accessable, bool avaible node or not
	void addPedNode(float hValue, float gValue, int index, Vector2f pos, bool accessable);

	// \brief Function to clear all nodes
	void clearNodes();

	vector<pair< Node*, Vector2f>> m_unitNodes; // \brief list of ALL nodes
	vector<pair< Node*, Vector2f>> m_unitOpenNodes; // \brief list of nodes available for checking
	vector<pair< Node*, Vector2f>> m_unitClosedNodes;// \brief list of nodes NOT to be checked


	vector<pair< Node*, Vector2f>> m_pedNodes; // \brief list of ALL nodes
	vector<pair< Node*, Vector2f>> m_pedOpenNodes; // \brief list of nodes available for checking
	vector<pair< Node*, Vector2f>> m_pedClosedNodes;// \brief list of nodes NOT to be checked
	
	unsigned int m_uiNodeX = 0; //!< Dimensions of level
	unsigned int m_uiNodeY = 0; //!< Dimensions of level

};


#endif // !PATHFINDING_H