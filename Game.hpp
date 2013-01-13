#pragma once

#include  "GameState.hpp"
#include "GameStateManager.hpp"
#include "Player.hpp"

class Game : public GameState
{
private:
	GameStateManager *m_GSM;
	sf::RenderWindow *m_Window;
	sf::Sprite m_Background;
	Player *m_Player;

public:
	Game(sf::RenderWindow *Window, GameStateManager *GSM, sf::Sprite &Background);
	~Game();
	void Update(sf::Time Time);
	void Render(sf::Time Time);
};