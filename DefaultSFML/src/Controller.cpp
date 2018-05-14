#include "Controller.h"

Controller::Controller()
{
	
	
}

pair<Node*, Vector2f> Controller::getNode(Vector2f pos)
{
	// Find the Desired mode
	RectangleShape goalRect(Vector2f(100, 100));
	RectangleShape nodeRect(Vector2f(100, 100));

	for (int i = 0; i < m_Pathfinding.m_unitNodes.size(); i++)
	{
		//position rect at goal
		goalRect.setPosition(pos);
		//check rect of node
		nodeRect.setPosition(m_Pathfinding.m_unitNodes[i].second);

		FloatRect Goal = goalRect.getGlobalBounds();
		FloatRect node = nodeRect.getGlobalBounds();

		//if it instersects set the goal node
		if (Goal.intersects(node))
		{
			return m_Pathfinding.m_unitNodes[i];
		}

	}

	cout << "NO node was found !!" << endl;
	return pair<Node*, Vector2f>();
}

void Controller::findPath()
{


	//Calculates the Position of the Start Tile in the Grid
	int iStartTile = getNode(m_sfStart).first->m_iIndex;

	//Calculates the Position of the End Tile in the Grid
	int iEndTile = getNode(m_sfGoal).first->m_iIndex;


	int iCurrentTile = iStartTile; //Holds the tile being checked

	if (iStartTile != iEndTile )//&& iStartTile < m_Pathfinding.m_unitNodes.size() && iEndTile <m_Pathfinding.m_unitNodes.size())// && validVacinity(iEndTile))
	{
	
		//Calculates the Manhattan distance for each accessable node
		for (int i = 0; i < m_Pathfinding.m_unitNodes.size(); i++)
		{
			if (m_Pathfinding.m_unitNodes[i].first->m_bAccessable == true)
			{
				calculateManhattan(i, iEndTile);
				
			}
			
		}

		int iNextIndex = NULL;
		while (!m_bPathFound)
		{
			//If the tile being checked isn't the end tile
			if (iCurrentTile != iEndTile)
			{
				//Pushes the node to the closed list
				m_Pathfinding.m_unitClosedNodes.push_back(m_Pathfinding.m_unitNodes[iCurrentTile]);
			}

			//Find the move cost for the adjacent nodes
			calculateMoveCost(iCurrentTile, iEndTile);

			if (!m_bPathFound)
			{
				int iLowestF = 9999999999.0f;
				//Checks for the lowest F value in the open list
				for (int i = 0; i < m_Pathfinding.m_unitOpenNodes.size(); i++)
				{
					if (m_Pathfinding.m_unitOpenNodes[i].first->m_fFValue < iLowestF)
					{
						iCurrentTile = m_Pathfinding.m_unitOpenNodes[i].first->m_iIndex;
						iLowestF = m_Pathfinding.m_unitOpenNodes[i].first->m_fFValue;
						iNextIndex = i;
					}
				}
				m_Pathfinding.m_unitOpenNodes.erase(m_Pathfinding.m_unitOpenNodes.begin() + iNextIndex);
			}
		}

		pair< Node*, Vector2f> CurrentNode;
		//If the end is not on the closed list
		if (!nodeInList(m_Pathfinding.m_unitNodes[iEndTile],m_Pathfinding.m_unitClosedNodes))
		{
			CurrentNode = m_Pathfinding.m_unitNodes[iEndTile];
			m_path.push_back(CurrentNode.second);
		}
		//set its parent to be the end node
		else
		{
			CurrentNode = *m_Pathfinding.m_unitNodes[iEndTile].first->parentNode;
			m_path.push_back(CurrentNode.second);
		}

		//If the current node isn't the start node
		if (CurrentNode.first->m_iIndex != iStartTile)
		{
			//Loop back through the parents to find the path
			do {
				CurrentNode = *CurrentNode.first->parentNode ;
				m_path.push_back(CurrentNode.second);
			} while (CurrentNode.first->parentNode != NULL);
		}
	}
	m_bPathFound = false;

}

void Controller::calculateManhattan(int iStartTile, int iEndTile)
{
	/// Number of Nodes in x
	float fXDist = ((m_Pathfinding.m_unitNodes[iEndTile].second.x )- (m_Pathfinding.m_unitNodes[iStartTile].second.x));

	// Number of Nodes in y
	float fYDist = ((m_Pathfinding.m_unitNodes[iEndTile].second.y) - (m_Pathfinding.m_unitNodes[iStartTile].second.y));
	// Added x and y dist
	float fDistance = abs(fXDist) + abs(fYDist);

	// Returns the combined distances
	m_Pathfinding.m_unitNodes[iStartTile].first->m_fHValue = fDistance;
}

void Controller::calculateMoveCost(int iCurrentTile, int iEndTile)
{
	if (!m_bPathFound)
	{
		
		if (m_Pathfinding.m_unitNodes[iCurrentTile].first->m_bAccessable == false)
		{

		}
		else
		{
			//If not on the right edge of the screen
			if (iCurrentTile % (int)m_Pathfinding.m_uiNodeX < (int)m_Pathfinding.m_uiNodeX - 1)
			{
				checkNode(iCurrentTile + 1, iCurrentTile, 10); //Assign right node a cost

															   //If also not on the top edge of the screen
				if (iCurrentTile - m_Pathfinding.m_uiNodeX > 0)
				{
					//Assign top right node a cost
					//If the tile to the right, the top or the top right of the tile is on the closed list
					if (find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[iCurrentTile - (int)m_Pathfinding.m_uiNodeX + 1]) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[iCurrentTile - (int)m_Pathfinding.m_uiNodeX]) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[iCurrentTile + 1]) != m_Pathfinding.m_unitClosedNodes.end() ||
						m_Pathfinding.m_unitNodes[iCurrentTile].first->m_bAccessable == false
						) {
						checkNode(iCurrentTile - m_Pathfinding.m_uiNodeX + 1, iCurrentTile, 1000);  //Make the cost really high
					}
					else
					{
						checkNode(iCurrentTile - m_Pathfinding.m_uiNodeX + 1, iCurrentTile, 14); //Otherwise allow diagonal movement
					}
				}

				//If also not on the bottom edge of the screen
				if (iCurrentTile + m_Pathfinding.m_uiNodeX < m_Pathfinding.m_unitNodes.size())
				{
					//Assign bottom right node a cost
					//If the tile to the right, the bottom or the bottom right of the tile is on the closed list
					if (find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[iCurrentTile + (int)m_Pathfinding.m_uiNodeX + 1]) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[iCurrentTile + (int)m_Pathfinding.m_uiNodeX]) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[iCurrentTile + 1]) != m_Pathfinding.m_unitClosedNodes.end() ||
						m_Pathfinding.m_unitNodes[iCurrentTile].first->m_bAccessable == false
						) {
						checkNode(iCurrentTile + m_Pathfinding.m_uiNodeX + 1, iCurrentTile, 1000); //Make the cost so high its more probable to walk around it
					}
					else
					{
						checkNode(iCurrentTile + m_Pathfinding.m_uiNodeX + 1, iCurrentTile, 14);//Otherwise allow diagonal movement
					}
				}
			}
			//If not on the left edge of the screen
			if (iCurrentTile % (int)m_Pathfinding.m_uiNodeX > 0)
			{
				checkNode(iCurrentTile - 1, iCurrentTile, 10); //Assign left node a cost

															   //If also not on the top edge of the screen
				if (iCurrentTile - m_Pathfinding.m_uiNodeX > 0)
				{
					//Assign top left node a cost
					//If the tile to the left, the top or the top left of the tile is on the closed list
					if (find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iCurrentTile - (int)m_Pathfinding.m_uiNodeX - 1)) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iCurrentTile - (int)m_Pathfinding.m_uiNodeX)) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iCurrentTile - 1)) != m_Pathfinding.m_unitClosedNodes.end() ||
						m_Pathfinding.m_unitNodes[iCurrentTile].first->m_bAccessable == false
						) {
						checkNode(iCurrentTile - m_Pathfinding.m_uiNodeX - 1, iCurrentTile, 1000);  //Make the cost so high its more probable to walk around it
					}
					else
					{
						checkNode(iCurrentTile - m_Pathfinding.m_uiNodeX - 1, iCurrentTile, 14);//Otherwise allow diagonal movement
					}
				}

				//If also not on the bottom edge of the screen
				if (iCurrentTile + m_Pathfinding.m_uiNodeX < m_Pathfinding.m_unitNodes.size())
				{
					//Assign bottom left node a cost
					//If the tile to the left, the bottom or the bottom left of the tile is on the closed list
					if (find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iCurrentTile + (int)m_Pathfinding.m_uiNodeX - 1)) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iCurrentTile + (int)m_Pathfinding.m_uiNodeX)) != m_Pathfinding.m_unitClosedNodes.end() ||
						find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iCurrentTile - 1)) != m_Pathfinding.m_unitClosedNodes.end() ||
						m_Pathfinding.m_unitNodes[iCurrentTile].first->m_bAccessable == false
						) {
						checkNode(iCurrentTile + m_Pathfinding.m_uiNodeX - 1, iCurrentTile, 100); //Make the cost so high its more probable to walk around it
					}
					else
					{
						checkNode(iCurrentTile + m_Pathfinding.m_uiNodeX - 1, iCurrentTile, 14);//Otherwise allow diagonal movement
					}
				}
			}

			//If not on the top edge of the screen
			if (iCurrentTile - m_Pathfinding.m_uiNodeX > 0)
			{
				checkNode(iCurrentTile - m_Pathfinding.m_uiNodeX, iCurrentTile, 10); //Assign top node a cost
			}

			//If not on the bottom edge of the screen.
			if (iCurrentTile + m_Pathfinding.m_uiNodeX < m_Pathfinding.m_unitNodes.size())
			{
				checkNode(iCurrentTile + m_Pathfinding.m_uiNodeX, iCurrentTile, 10); //Assign bottom node a cost
			}


			//If the end wall isn't on the closed list
			if (!nodeInList(m_Pathfinding.m_unitNodes[iEndTile], m_Pathfinding.m_unitClosedNodes))
			{
				//Checks all the surrounding tiles for the end tile
				for (int i = 0; i < m_viNodesToCheck.size(); i++)
				{
					//If any of the surrounding tiles are the end tile parent it and set the path
					if (iCurrentTile + m_viNodesToCheck.at(i) == iEndTile)
					{
						m_bPathFound = true;
						m_Pathfinding.m_unitNodes[iEndTile].first->parentNode = &m_Pathfinding.m_unitNodes.at(iCurrentTile);
					}
				}
			}
			//If current tile is the end tile set the path
			else if (iCurrentTile == iEndTile)
			{
				m_bPathFound = true;
			}

		}

		
	}
}

void Controller::checkNode(int iTile, int iCurrentTile, int iMoveCost)
{
	//If the node isn't on the open list
	if (!nodeInList(m_Pathfinding.m_unitNodes[iTile] , m_Pathfinding.m_unitOpenNodes))
	{
		//If the node isn't on the closed list
		if (find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes.at(iTile)) == m_Pathfinding.m_unitClosedNodes.end()) {
			m_Pathfinding.m_unitOpenNodes.push_back(m_Pathfinding.m_unitNodes[iTile]); //Add the node to the open list
			makeCurrent(iTile, iCurrentTile, iMoveCost);
		}
	}
	//If it's faster to move to an already checked node from this node than the previous node
	else if (m_Pathfinding.m_unitNodes[iCurrentTile].first->m_fGValue + iMoveCost < m_Pathfinding.m_unitNodes[iTile].first->m_fGValue) {
		makeCurrent(iTile, iCurrentTile, iMoveCost);
	}
}

bool Controller::nodeInList(pair<Node*, Vector2f> node1, vector<pair<Node*, Vector2f>> list)
{

	if ((find(list.begin(), list.end(), node1)) != list.end())return true;
	else return false;
}
void  Controller::receiveNodeData(Pathfinding nodeData)
{
	m_Pathfinding = nodeData;

	m_viNodesToCheck = {
		1,									 //Right
		-1,									 //Left
		-(int)m_Pathfinding.m_uiNodeX,		//Top
		-(int)m_Pathfinding.m_uiNodeX + 1, //Top right
		-(int)m_Pathfinding.m_uiNodeX - 1, //Top left
		(int)m_Pathfinding.m_uiNodeX,      //Bottom
		(int)m_Pathfinding.m_uiNodeX + 1,  //Bottom right
		(int)m_Pathfinding.m_uiNodeX - 1   //Bottom left
	};
}

void Controller::makeCurrent(int iTile, int iCurrentTile, int iMoveCost)
{
	m_Pathfinding.m_unitNodes[iTile].first->parentNode = &m_Pathfinding.m_unitNodes[iCurrentTile]; //Make the parent the current node
	m_Pathfinding.m_unitNodes[iTile].first->m_fGValue = m_Pathfinding.m_unitNodes[iTile].first->parentNode->first->m_fGValue + iMoveCost; //The node gets its parents movecost plus the travel cost
	m_Pathfinding.m_unitNodes[iTile].first->m_fFValue = m_Pathfinding.m_unitNodes[iTile].first->m_fGValue + m_Pathfinding.m_unitNodes[iTile].first->m_fHValue; //Calculate the node's F value
}

//Used to check if the end node is surrounded by impassable nodes
bool Controller::validVacinity(int iEndTile)
{
	for (int i = 0; i < m_viNodesToCheck.size(); i++) // For every surrounding node
	{
		if (iEndTile + m_viNodesToCheck[i] > 0 && iEndTile + m_viNodesToCheck[i] < m_Pathfinding.m_unitNodes.size())// If within the grid space
		{
			if (find(m_Pathfinding.m_unitClosedNodes.begin(), m_Pathfinding.m_unitClosedNodes.end(), m_Pathfinding.m_unitNodes[(iEndTile + m_viNodesToCheck[i])]) == m_Pathfinding.m_unitClosedNodes.end()) { //And not on the closed list
				return true;
			}
		}
	}

	return false; //If all of the tests are false return false
}

void Controller::setInvalid(sf::Vector2f Node)
{
	m_Pathfinding.m_unitClosedNodes.push_back(m_Pathfinding.m_unitNodes[(Node.y *m_Pathfinding.m_uiNodeX) + Node.x]);
}
