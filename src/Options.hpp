#pragma once

#include <SFML\Graphics.hpp>

#include "GameStateManager.hpp"

class Options : public GameState {
private:
	sf::RenderWindow &m_Window;
	bool m_KeyLock;
	sf::Text m_VSync;
	sf::Text m_Instructions;
	static bool m_VSyncEnabled;

public:
	Options(sf::RenderWindow &window, const sf::Font* font);
	~Options();

	void update(sf::Time& time);
	void render(sf::Time& time);
};
