#pragma once

#include <SFML\System\Time.hpp>

enum GameStateID
{
	GSID_NONE,
	GSID_MAINMENU,
	GSID_OPTIONS,
	GSID_GAME
};

class GameState
{
private:
	const GameStateID m_gameStateID;

public:
	GameState(GameStateID id) : m_gameStateID(id) { }
	virtual ~GameState() { }

	virtual void update(sf::Time Time) = 0;
	virtual void render(sf::Time Time) = 0;

	GameStateID getGameStateID() const {
		return m_gameStateID;
	}
};
