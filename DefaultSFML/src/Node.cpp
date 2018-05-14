#include "Node.h"
#include "..\include\Node.h"

Node::Node()
{
	parentNode = NULL;
}

Node::Node(float hValue, float gValue, int index, bool Accessable)
{
	m_iIndex = index;
	m_fHValue = hValue;
	m_fGValue = gValue;
	m_fFValue = m_fHValue + m_fGValue;
	parentNode = NULL;
	m_bAccessable = Accessable;
}

void Node::ParticalReset()
{
	parentNode = NULL;
	m_fGValue = 0.f;
	m_fHValue = 0.f;
	m_fFValue = 0.f;
}



void Node::ResetNode()
{
	
	parentNode = NULL;

	m_fGValue = 0.f;
	m_fHValue = 0.f;
	m_fFValue = 0.f;
}
