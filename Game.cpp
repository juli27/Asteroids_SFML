#include "Game.hpp"

Game::Game(sf::RenderWindow *Window, GameStateManager *GSM, sf::Sprite &Background)
	: m_Window(Window),
	  m_Background(Background),
	  m_GSM(GSM)
{
	m_Player = new Player(m_Window);
}

Game::~Game()
{
	delete m_Player;
}

void Game::Update(sf::Time Time)
{
	m_Player->Update(Time);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_GSM->setState(GSID_MAINMENU);
}

void Game::Render(sf::Time Time)
{
	m_Window->clear(sf::Color::Magenta);
	m_Window->draw(m_Background);
	m_Player->Render(Time);
}