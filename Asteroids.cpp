#include "Asteroids.hpp"
#include <iostream>
#include <sstream>

GameStateID GameState::m_ActiveGameState = GSID_NONE;

Asteroids::Asteroids()
	: m_Window(sf::VideoMode(800, 600), "Asteroids"),
	  m_ActiveState(NULL),
	  m_ActiveStateID(GSID_FIX),
	  m_FPSTimer(0.0f)
{
	m_BackgroundTex.loadFromFile("data/Background.png");
	m_Background.setTexture(m_BackgroundTex);

	m_Font.loadFromFile("data/AGENCYR.TTF");
	m_FPS.setString("");
	m_FPS.setFont(m_Font);
}

Asteroids::~Asteroids()
{
	delete m_ActiveState;
}

bool Asteroids::Run()
{
	sf::Clock GameClock;

	// Mainloop
	while (m_Window.isOpen())
	{
		m_ElapsedTime = GameClock.restart();

		if (m_ActiveStateID != GameState::getActiveState())
		{
			m_ActiveStateID = GameState::getActiveState();

			if (m_ActiveState)
				delete m_ActiveState;

			switch (m_ActiveStateID)
			{
			case GSID_NONE:
				GameState::setActiveState(GSID_MAINMENU);
				m_ActiveState = new MainMenu(m_Window, m_Background);
				break;
			case GSID_MAINMENU:
				m_ActiveState = new MainMenu(m_Window, m_Background);
				break;
			case GSID_OPTIONS:
				m_ActiveState = new Options(m_Window, m_Background);
				break;
			case GSID_GAME:
				m_ActiveState = new Game(m_Window, m_Background);
				break;
			default:
				break;
			}
		}

		// Eventloop
		while (m_Window.pollEvent(m_Event))
		{
			switch (m_Event.type)
			{
			case sf::Event::Closed:
				m_Window.close();
				break;

			default:
				break;
			}
		}
		//

		int FPS = static_cast<int> (1.0f / m_ElapsedTime.asSeconds());
		
		m_FPSTimer += m_ElapsedTime.asSeconds();
		if (m_FPSTimer >= 0.2f)
		{
			std::ostringstream Converter;
			Converter << FPS << " FPS";
			m_FPS.setString(Converter.str());

			m_FPSTimer = 0.0f;
		}

		m_ActiveState->Render(m_ElapsedTime);
		m_ActiveState->Update(m_ElapsedTime);

		m_Window.draw(m_FPS);
		m_Window.display();
	}
	//

	return true;
}