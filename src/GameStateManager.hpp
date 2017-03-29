#pragma once

#include <SFML\Graphics.hpp>

#include "GameState.hpp"

class GameStateManager {
private:
	static GameState* m_activeGameState;
	static GameStateID m_nextGameState;

public:
	static GameState* updateActiveGameState(sf::RenderWindow& window, sf::Sprite& background);
	static void setNextActiveGameState(GameStateID id);
	static GameState* getActiveGameState();
};
