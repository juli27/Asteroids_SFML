#include <sstream>

#include "Options.hpp"

bool Options::m_VSyncEnabled = false;

Options::Options(sf::RenderWindow &window, sf::Sprite &background) :
	GameState(GSID_OPTIONS),
	m_Window(window),
	m_Background(background),
	m_KeyLock(true)
{
	m_Font.loadFromFile("data/AGENCYR.TTF");
	m_VSync.setFont(m_Font);
	m_VSync.setPosition(300.0f, 200.0f);

	m_Instructions.setFont(m_Font);
	m_Instructions.setString("\n\nPress Enter to change the setting - Press Esc to return to the menu");
	m_Instructions.setPosition(70.0f, 490.0f);
}

Options::~Options()
{
}

void Options::update(sf::Time Time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		GameStateManager::setNextActiveGameState(GSID_MAINMENU);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !m_KeyLock)
	{
		if (m_VSyncEnabled)
		{
			m_VSyncEnabled = false;
		}
		else
		{
			m_VSyncEnabled = true;
		}

		m_Window.setVerticalSyncEnabled(m_VSyncEnabled);
		m_KeyLock = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		m_KeyLock = false;
	}

	std::ostringstream Converter;
	Converter << "VSync: ";
	if (m_VSyncEnabled)
		Converter << "on";
	else
		Converter << "off";
	
	m_VSync.setString(Converter.str());

}

void Options::render(sf::Time Time)
{
	m_Window.clear(sf::Color::Magenta);
	m_Window.draw(m_Background);
	m_Window.draw(m_VSync);
	m_Window.draw(m_Instructions);
}
