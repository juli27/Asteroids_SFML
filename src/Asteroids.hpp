#pragma once

#include <SFML\Graphics.hpp>

class Asteroids {
private:
	sf::RenderWindow m_Window;
	sf::Event m_Event;
	sf::Time m_ElapsedTime;
	sf::Texture m_BackgroundTex;
	sf::Sprite m_Background;
	sf::Font m_Font;
	sf::Text m_FPS;
	float m_FPSTimer;

public:
	Asteroids();
	~Asteroids();
	bool run();
};
