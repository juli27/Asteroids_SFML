#pragma once

#include "SFML\Graphics.hpp"
#include "GameStateID.hpp"

class GameState
{
private:
	GameStateID m_ActiveGameState;

public:
	GameState() {}
	virtual ~GameState() {}
	virtual void Update(sf::Time Time) = 0;
	virtual void Render(sf::Time Time) = 0;
};