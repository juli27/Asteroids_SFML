#include "Asteroids.hpp"
#include <iostream>

Asteroids::Asteroids()
	: m_ActiveState(NULL),
	  m_ActiveStateID(GSID_FIX)
{
	m_Window = new sf::RenderWindow(sf::VideoMode(800, 600), "Asteroids");

	m_BackgroundTex.loadFromFile("data/Background.bmp");
	m_Background.setTexture(m_BackgroundTex);
	
	m_FPS = 0;

	m_GSManager = new GameStateManager();
}

Asteroids::~Asteroids()
{
	delete m_ActiveState;
}

bool Asteroids::Run()
{
	sf::Clock GameClock;

	// Mainloop
	while (m_Window->isOpen())
	{
		m_ElapsedTime = GameClock.restart();

		if (m_ActiveStateID != m_GSManager->getActiveStateID())
		{
			m_ActiveStateID = m_GSManager->getActiveStateID();

			if (m_ActiveState)
				delete m_ActiveState;

			switch (m_ActiveStateID)
			{
			case GSID_NONE:
				m_GSManager->setState(GSID_MAINMENU);
				m_ActiveState = new MainMenu(m_Window, m_GSManager, m_Background);
				break;

			case GSID_MAINMENU:
				m_ActiveState = new MainMenu(m_Window, m_GSManager, m_Background);
				break;

			case GSID_GAME:
				m_ActiveState = new Game(m_Window, m_GSManager, m_Background);
				break;

			default:
				break;
			}
		}

		// Eventloop
		while (m_Window->pollEvent(m_Event))
		{
			switch (m_Event.type)
			{
			case sf::Event::Closed:
				m_Window->close();
				break;

			default:
				break;
			}
		}
		//

		m_FPS = static_cast<int> (1.f / m_ElapsedTime.asSeconds());

		// std::cout << m_FPS << std::endl;

		m_ActiveState->Render(m_ElapsedTime);
		m_ActiveState->Update(m_ElapsedTime);

		m_Window->display();
	}
	//

	return true;
}