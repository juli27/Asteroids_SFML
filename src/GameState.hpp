#pragma once

#include "SFML\Graphics.hpp"
#include "GameStateID.hpp"

class GameState
{
protected:
	static GameStateID m_ActiveGameState;

public:
	GameState() {}
	virtual ~GameState() {}
	virtual void Update(sf::Time Time) = 0;
	virtual void Render(sf::Time Time) = 0;
	static GameStateID getActiveState()
	{
		return m_ActiveGameState;
	}
	static void setActiveState(GameStateID ID)
	{
		m_ActiveGameState = ID;
	}
};