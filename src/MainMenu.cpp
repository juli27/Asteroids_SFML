#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow &window, sf::Sprite &background) :
	GameState(GSID_MAINMENU),
	m_Window(window),
	m_ActiveEntry(ME_START),
	m_CursorAnimPhase(0.0f),
	m_Background(background),
	m_KeyLock(true)
{
	m_Cursor = new Animation("data/Asteroid.png", 20, 64, 64, m_Window);

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

	m_Font.loadFromFile("data/AGENCYR.TTF");
	m_Copyright.setFont(m_Font);
	m_Copyright.setCharacterSize(20);
	m_Copyright.setString("Julian B�hler 2013");
	m_Copyright.setPosition(690, 580);
}

MainMenu::~MainMenu()
{
	for(m_It = m_Entries.begin(); m_It != m_Entries.end(); m_It++)
	{
		delete m_It->second;
	}
}

void MainMenu::update(sf::Time Time) {
	m_It = m_Entries.find(m_ActiveEntry);

	if (!m_It->second->isActive())
	{
		m_It->second->setActive();
	}
	
	// Cursor
	m_Cursor->setPosition(m_It->second->getPosition().x - 70, m_It->second->getPosition().y + 30);
	m_CursorAnimPhase += 10.0f * Time.asSeconds();
	if (m_CursorAnimPhase >= 20.0f)
		m_CursorAnimPhase -= 20.0f;
	//

	// Controls
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !m_KeyLock)
	{
		switch (m_ActiveEntry)
		{
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_KeyLock)
	{
		switch (m_ActiveEntry)
		{
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)  && !m_KeyLock)
	{
		switch (m_ActiveEntry)
		{
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

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		m_KeyLock = false;
	}
	//
}

void MainMenu::render(sf::Time Time) {
	m_Window.clear(sf::Color::Magenta);
	m_Window.draw(m_Background);

	for (m_It = m_Entries.begin(); m_It != m_Entries.end(); m_It++)
	{
		m_It->second->Render(Time, m_Window);
	}

	m_Cursor->Render(m_CursorAnimPhase);
	m_Window.draw(m_Copyright);
}
