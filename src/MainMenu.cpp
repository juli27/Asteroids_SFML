#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow &window, const sf::Font* font)
	: GameState(GSID_MAINMENU),
		m_Window(window),
		m_Cursor("data/Asteroid.png", 20, 64, 64, 10.0f),
		m_ActiveEntry(ME_START),
		m_KeyLock(true),
		m_Copyright("Julian Bühler 2013/2017", *font, 20) {
	MenuEntry *Entry;
	Entry = new MenuEntry("Start", 300.0f, 200.0f);
	m_Entry = std::make_pair(ME_START, Entry);
	m_Entries.insert(m_Entry);

	Entry = new MenuEntry("Options", 300.0f, 300.0f);
	m_Entry = std::make_pair(ME_OPTIONS, Entry);
	m_Entries.insert(m_Entry);
	Entry = new MenuEntry("Quit", 300.0f, 400.0f);
	m_Entry = std::make_pair(ME_QUIT, Entry);
	m_Entries.insert(m_Entry);

	m_Copyright.setPosition(690, 580);
}

MainMenu::~MainMenu() {
	for (m_It = m_Entries.begin(); m_It != m_Entries.end(); m_It++) {
		delete m_It->second;
	}
}

void MainMenu::update(sf::Time& time) {
	m_It = m_Entries.find(m_ActiveEntry);

	if (!m_It->second->isActive()) {
		m_It->second->setActive();
	}

	// Cursor
	m_Cursor.setPosition(m_It->second->getPosition().x - 70, m_It->second->getPosition().y + 30);
	m_Cursor.update(time);

	// Controls
	if (!m_KeyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		switch (m_ActiveEntry) {
		case ME_START:
			m_ActiveEntry = ME_OPTIONS;
			break;
		case ME_OPTIONS:
			m_ActiveEntry = ME_QUIT;
			break;
		case ME_QUIT:
			m_ActiveEntry = ME_START;
			break;
		default:
			break;
		}

		m_KeyLock = true;
	}

	if (!m_KeyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		switch (m_ActiveEntry) {
		case ME_START:
			m_ActiveEntry = ME_QUIT;
			break;
		case ME_OPTIONS:
			m_ActiveEntry = ME_START;
			break;
		case ME_QUIT:
			m_ActiveEntry = ME_OPTIONS;
			break;
		default:
			break;
		}

		m_KeyLock = true;
	}

	if (!m_KeyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		switch (m_ActiveEntry) {
		case ME_NONE:
			break;
		case ME_START:
			GameStateManager::setNextActiveGameState(GSID_GAME);
			break;
		case ME_OPTIONS:
			GameStateManager::setNextActiveGameState(GSID_OPTIONS);
			break;
		case ME_QUIT:
			m_Window.close();
			break;
		default:
			break;
		}

		m_KeyLock = true;
	}

	if (m_KeyLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		m_KeyLock = false;
	}
}

void MainMenu::render(sf::Time& time) {
	for (m_It = m_Entries.begin(); m_It != m_Entries.end(); m_It++) {
		m_It->second->Render(time, m_Window);
	}

	m_Window.draw(m_Cursor);
	m_Window.draw(m_Copyright);
}
