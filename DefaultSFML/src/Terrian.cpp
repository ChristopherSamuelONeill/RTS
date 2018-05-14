#include "Terrian.h"

Terrian::Terrian()
{
}

Terrian::Terrian(float rotation, Texture texture,  Vector2f Size, Vector2f Pos, bool passable)
{
	m_sfTexture = texture;
	m_sfPosition = Pos;
	m_sfSize = Size;
	m_fRotation = rotation;

	//set up drawbales
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	//m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfTexture.setRepeated(true);
	m_sfTerrianSprite.setPosition(m_sfRect.getPosition());
	m_sfTerrianSprite.setTexture(m_sfTexture);
	//m_sfTerrianSprite.setOrigin(m_sfSize / 2.0f);
	m_sfTerrianSprite.setRotation(m_fRotation);
}


void Terrian::update()
{
	//ensure all emements are up to date
	m_sfRect.setPosition(m_sfPosition);
	m_sfRect.setSize(m_sfSize);
	//m_sfRect.setOrigin(m_sfSize / 2.0f);
	m_sfRect.setRotation(m_fRotation);
	m_sfRect.setFillColor(Color::Red);

	m_sfTexture.setRepeated(true);
	m_sfTerrianSprite.setTextureRect({ 0,0,(int)m_sfSize.x,(int)m_sfSize.y });

	m_sfTerrianSprite.setPosition(m_sfRect.getPosition());
	m_sfTerrianSprite.setTexture(m_sfTexture);
	m_sfTerrianSprite.setRotation(m_fRotation);



}

void Terrian::draw(RenderTarget & target, RenderStates states) const
{
	//draw the sprite
	
	target.draw(m_sfTerrianSprite);
}

void Terrian::setTexture(Texture newTexture)
{
	m_sfTexture = newTexture;
}

void Terrian::setPosistion(Vector2f newPos)
{
	m_sfPosition = newPos;
}

void Terrian::setSize(Vector2f newSize)
{
	m_sfSize = newSize;
}

void Terrian::incrementRotation(float increment)
{
	m_fRotation += increment;
}
