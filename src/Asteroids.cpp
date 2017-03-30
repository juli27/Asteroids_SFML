#include "Asteroids.hpp"

#include <iostream>
#include <sstream>

#include "GameStateManager.hpp"

Asteroids::Asteroids() :
	m_Window(sf::VideoMode(800, 600), "Asteroids") {
	sf::Texture* backgroundTex = new sf::Texture();
	backgroundTex->loadFromFile("data/Background.png");
	m_Background.setTexture(*backgroundTex);

	sf::Font* agencyFont = new sf::Font();
	agencyFont->loadFromFile("data/AGENCYR.TTF");
	m_FPSText.setFont(*agencyFont);
}

Asteroids::~Asteroids() {
	delete GameStateManager::getActiveGameState();
	delete m_Background.getTexture();
	delete m_FPSText.getFont();
}

void Asteroids::run() {
	sf::Clock clock;
	float fpsDisplayTimer = 0.0f;

	// Mainloop
	while (m_Window.isOpen()) {
		sf::Time elapsedTimed = clock.restart();

		if (!GameStateManager::getActiveGameState()) {
			GameStateManager::setNextActiveGameState(GSID_MAINMENU);
		}

		// Eventloop
		sf::Event event;
		while (m_Window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				m_Window.close();
				break;
			default:
				break;
			}
		}

		int FPS = static_cast<int> (1.0f / elapsedTimed.asSeconds());

		fpsDisplayTimer += elapsedTimed.asSeconds();
		if (fpsDisplayTimer >= 0.2f) {
			std::ostringstream Converter;
			Converter << FPS << " FPS";
			m_FPSText.setString(Converter.str());

			fpsDisplayTimer = 0.0f;
		}

		GameStateManager::updateActiveGameState(m_Window, m_FPSText.getFont());

		m_Window.clear(sf::Color::Magenta);
		m_Window.draw(m_Background);
		GameStateManager::getActiveGameState()->render(elapsedTimed);
		GameStateManager::getActiveGameState()->update(elapsedTimed);

		m_Window.draw(m_FPSText);
		m_Window.display();
	}
}
