#include "Game.h"

Game::Game()
{
	m_Gametextures = TextureObject::getInstance();

}

Game::Game(string dir)
{
	m_Gametextures = TextureObject::getInstance();
	m_currPlayer = Profile::getInstance();

	m_vPlayers.push_back(TeamPlayer(0, "England", m_vPlayers.size()));
	m_vPlayers.push_back(TeamPlayer(1, "Italy", m_vPlayers.size()));


	if (dir == "Arena")
	{
		m_vPlayers[0].spawnUnit("testing",0,Vector2f(-1000.0f,0.0f), 90.0f);
		m_vPlayers[1].spawnUnit("testing",0, Vector2f(1000.0f, 0.0f), 270.0f);

		m_vPlayers[0].spawnBuilding("testing", 0, Vector2f(-2000.0f, 0.0f), 90.0f);
		m_vPlayers[1].spawnBuilding("testing", 0, Vector2f(2000.0f, 0.0f), 270.0f);

		for (int x = -4096; x < 4096; x += 1024)
		{
			for (int y = -4096; y < 4096; y += 1024)
			{
				m_vTerrian.push_back(Terrian(0.0f, m_Gametextures->m_vBackgroundTextures[1], Vector2f(1024.0f, 1024.0f), Vector2f(x, y), true));

			}
		}

	
	}

	
	//set up drawbales
	m_sfHudTopBarRect.setPosition(Vector2f(0.0f,0.0f));
	m_sfHudTopBarRect.setSize(Vector2f(m_currPlayer->m_sfResolution.x, m_currPlayer->m_sfResolution.y));
	m_sfHudTopBarRect.setFillColor(Color::Red);

	m_sfHudTopBarSprite.setPosition(m_sfHudTopBarRect.getPosition());
	m_sfHudTopBarSprite.setTexture(m_Gametextures->m_topBarTexture[0]);



}

void Game::updateScene(float dt)
{
	for (int i = 0; i < m_vTerrian.size(); i++)
	{
		m_vTerrian[i].update();
	}
	
	for (int i = 0; i < m_vPlayers.size(); i++)
	{
		
		for (int x = 0; x < m_vPlayers.size(); x++)
		{
			if (x != i) // not same palyet
			{
				if (m_vPlayers[i].m_iTeam != m_vPlayers[x].m_iTeam)
				{
					//compare pass player x to player i for ai checks
					m_vPlayers[i].findTarget(m_vPlayers[x].m_vUnits,x);
					m_vPlayers[i].DecisionOnTarget(m_vPlayers[x].m_vUnits, x,dt);
				}
			}
		}
		
		m_vPlayers[i].update(dt);
		
	}


	//set up drawbales
	m_sfHudTopBarRect.setPosition(Vector2f(0.0f, 0.0f));
	m_sfHudTopBarRect.setSize(Vector2f(1920.0f, 1080.0f));
	m_sfHudTopBarRect.setFillColor(Color::Red);

	m_sfHudTopBarSprite.setPosition(m_sfHudTopBarRect.getPosition());
	m_sfHudTopBarSprite.setScale(Vector2f(m_currPlayer->m_sfResolution.x / 3840.0f , m_currPlayer->m_sfResolution.y / 2160.0f ));
	m_sfHudTopBarSprite.setTexture(m_Gametextures->m_topBarTexture[0]);

}

void Game::drawScene(RenderWindow & window)
{
	for (int i = 0; i < m_vTerrian.size(); i++)
	{
		window.draw(m_vTerrian[i]);
	}
	for (int i = 0; i < m_vPlayers.size(); i++)
	{
		for (int x = 0; x < m_vPlayers[i].m_vUnits.size(); x++)
		{
			if(m_vPlayers[i].m_vUnits[x].m_bAlive)window.draw(m_vPlayers[i].m_vUnits[x]);
		}
		for (int x = 0; x < m_vPlayers[i].m_vBuildings.size(); x++)
		{
			window.draw(m_vPlayers[i].m_vBuildings[x]);
		}
	}
}

void Game::closeGame()
{
}

void Game::loopClickables(Vector2f pos)
{
	for (int i = 0; i < m_vPlayers.size(); i++)
	{
		for (int x = 0; x < m_vPlayers[i].m_vBuildings.size(); x++)
		{
			if (m_vPlayers[i].m_vBuildings[x].m_bClicked(pos))
			{
				m_vPlayers[i].spawnUnit("testing", 0, Vector2f(-1000.0f, 0.0f), 90.0f);
				cout << "spawnUnit " << endl;
			}

		}

	}
}

