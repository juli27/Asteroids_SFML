#include "Options.hpp"

bool Options::m_VSyncEnabled = false;

Options::Options(sf::RenderWindow &window, const sf::Font* font)
	: GameState(GSID_OPTIONS),
		m_Window(window),
		m_KeyLock(true),
		m_VSync("VSync: off", *font),
		m_Instructions("\n\nPress Enter to change the setting - Press Esc to return to the menu", *font) {
	m_VSync.setPosition(300.0f, 200.0f);

	m_Instructions.setPosition(70.0f, 490.0f);
}

Options::~Options() { }

void Options::update(sf::Time& time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		GameStateManager::setNextActiveGameState(GSID_MAINMENU);
	}

	if (!m_KeyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		if (m_VSyncEnabled) {
			m_VSyncEnabled = false;
			m_VSync.setString("VSync: off");
		}
		else {
			m_VSyncEnabled = true;
			m_VSync.setString("VSync: on");
		}

		m_Window.setVerticalSyncEnabled(m_VSyncEnabled);
		m_KeyLock = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		m_KeyLock = false;
	}
}

void Options::render(sf::Time& time) {
	m_Window.draw(m_VSync);
	m_Window.draw(m_Instructions);
}
