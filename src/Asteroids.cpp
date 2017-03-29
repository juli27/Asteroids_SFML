#include "Asteroids.hpp"

#include <iostream>
#include <sstream>

#include "GameStateManager.hpp"

Asteroids::Asteroids() :
	m_Window(sf::VideoMode(800, 600), "Asteroids"),
	m_FPSTimer(0.0f)
{
	m_BackgroundTex.loadFromFile("data/Background.png");
	m_Background.setTexture(m_BackgroundTex);

	m_Font.loadFromFile("data/AGENCYR.TTF");
	m_FPS.setString("");
	m_FPS.setFont(m_Font);
}

Asteroids::~Asteroids() {
	delete GameStateManager::getActiveGameState();
}

bool Asteroids::run() {
	sf::Clock GameClock;

	// Mainloop
	while (m_Window.isOpen()) {
		m_ElapsedTime = GameClock.restart();

		if (!GameStateManager::getActiveGameState()) {
			GameStateManager::setNextActiveGameState(GSID_MAINMENU);
		}

		// Eventloop
		while (m_Window.pollEvent(m_Event)) {
			switch (m_Event.type) {
			case sf::Event::Closed:
				m_Window.close();
				break;
			default:
				break;
			}
		}

		int FPS = static_cast<int> (1.0f / m_ElapsedTime.asSeconds());
		
		m_FPSTimer += m_ElapsedTime.asSeconds();
		if (m_FPSTimer >= 0.2f) {
			std::ostringstream Converter;
			Converter << FPS << " FPS";
			m_FPS.setString(Converter.str());

			m_FPSTimer = 0.0f;
		}

		GameStateManager::updateActiveGameState(m_Window, m_Background);
		GameStateManager::getActiveGameState()->render(m_ElapsedTime);
		GameStateManager::getActiveGameState()->update(m_ElapsedTime);

		m_Window.draw(m_FPS);
		m_Window.display();
	}

	return true;
}
