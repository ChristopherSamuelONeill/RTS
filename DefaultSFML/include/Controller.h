#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <vector>
#include <queue>

#include "Pathfinding.h"

using namespace std;
using namespace sf;

class Controller
{
private:
	

	vector<int> m_viNodesToCheck;//  \brief vector of ints for getting surrounding nodes
	bool m_bPathFound;
	bool nodeInList(pair< Node*, Vector2f> node1, vector<pair< Node*, Vector2f>> list);  // \brief Retunrs true if the node is i nthe list
	void calculateManhattan(int iStartTile, int iEndTile);
	void calculateMoveCost(int iCurrentTile, int iEndTile);
	void checkNode(int iTile, int iCurrentTile, int iMoveCost);
	void makeCurrent(int iTile, int iCurrentTile, int iMoveCost);
	bool validVacinity(int iEndTile);
	void setInvalid(sf::Vector2f Node);
	pair< Node*, Vector2f> getNode(Vector2f pos); // \brief Retunrs the node at a given pos



protected:
	vector<Vector2f> m_path; //  \brief Vector of positions forming a route
	Vector2f m_sfGoal;// \brief XY of the destination
	Vector2f m_sfStart;// \brief XY of the start
	Vector2f m_sfPosition; // \brief X Y position of unit
	Pathfinding m_Pathfinding; // \brief Pointer to Path data

	vector<RectangleShape> m_sfRectRoute;

public:

	void receiveNodeData(Pathfinding nodeData);
	Controller();
	void findPath();// \brief Function that runs the A* algorithm

	

};


#endif // !CONTROLLER_H