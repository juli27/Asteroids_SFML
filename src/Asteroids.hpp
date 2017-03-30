#pragma once

#include <SFML\Graphics.hpp>

class Asteroids {
private:
	sf::RenderWindow m_Window;
	sf::Sprite m_Background;
	sf::Text m_FPSText;

public:
	Asteroids();
	~Asteroids();
	void run();
};
