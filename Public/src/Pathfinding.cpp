#include "Pathfinding.h"

Pathfinding::Pathfinding()
{
}

void Pathfinding::addunitNode( float hValue, float gValue, int index, Vector2f pos, bool accessable)
{
	pair< Node*, Vector2f> tempNode;
	tempNode.first = new Node(hValue, gValue, index, accessable);
	tempNode.second = pos;
	m_unitNodes.push_back(tempNode);
}

void Pathfinding::addPedNode(float hValue, float gValue, int index, Vector2f pos, bool accessable)
{
	pair< Node*, Vector2f> tempNode;
	tempNode.first = new Node(hValue, gValue, index, accessable);
	tempNode.second = pos;
	m_pedNodes.push_back(tempNode);
}


void Pathfinding::clearNodes()
{
	m_unitOpenNodes.clear();
	m_unitClosedNodes.clear();
	for (int i = 0; i < m_unitNodes.size(); i++)
	{
		m_unitNodes[i].first->ParticalReset();
	}
	
}
