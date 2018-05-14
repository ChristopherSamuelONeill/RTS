#include"Selectable.h"

bool Selectable::m_bClicked(Vector2f sfVmouseClick)
{
	//create a float rect out of the mouse click
	FloatRect mousePos(sfVmouseClick, Vector2f(10.0f, 10.0f));
	if (mousePos.intersects(m_sfCollisionRect))
	{
		return true;
	}
	
	return false;
}
