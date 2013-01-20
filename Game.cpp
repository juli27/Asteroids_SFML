#include "Game.hpp"
#include <iostream>

Game::Game(sf::RenderWindow &Window, sf::Sprite &Background)
	: m_Window(Window),
	  m_Background(Background),
	  m_Points(0),
	  m_Player(m_Window)
{
	// m_Player = new Player(m_Window);
	m_Asteroid = new Animation("data/Asteroid.png", 20, 64, 64, m_Window);

	m_AsteroidTimer = 0.0f;
}

Game::~Game()
{
	delete m_Asteroid;
	std::cout << "Gesamtpunktzahl: " << m_Points << std::endl;
}

void Game::CheckCollisions()
{
	std::list<Shot> *ShotList = m_Player.getShotList();

	std::list<Asteroid>::iterator AsteroidIt = m_Asteroids.begin();
	std::list<Shot>::iterator ShotIt;

	sf::IntRect AsteroidRect;
	sf::IntRect ShotRect;
	sf::IntRect PlayerRect = m_Player.getCollisionRect();

	while (AsteroidIt != m_Asteroids.end())
	{
		AsteroidRect = AsteroidIt->getCollisionRect();

		for (ShotIt = ShotList->begin(); ShotIt != ShotList->end(); ++ShotIt)
		{
			ShotRect = ShotIt->getCollisionRect();

			if (ShotRect.intersects(AsteroidRect))
			{
				AsteroidIt->setAlive(false);
				ShotIt->setAlive(false);
				m_Points++;
			}
		}

		if (PlayerRect.intersects(AsteroidRect))
		{
			m_ActiveGameState = GSID_MAINMENU;
		}

		if (AsteroidIt->isAlive())
			AsteroidIt++;
		else
			AsteroidIt = m_Asteroids.erase(AsteroidIt);
	}
}

void Game::UpdateAsteroids(sf::Time Time)
{
	m_AsteroidTimer += Time.asSeconds();

	if (m_AsteroidTimer >= 0.5f)
	{
		Asteroid asteroid(m_Asteroid, sf::Vector2f(static_cast<float> (rand()%736), -60.0f));

		m_Asteroids.push_back(asteroid);

		m_AsteroidTimer = 0.0f;
	}
	
	std::list<Asteroid>::iterator It;
	for (It = m_Asteroids.begin(); It != m_Asteroids.end(); ++It)
	{
		It->Update(Time);
	}

}

void Game::RenderAsteroids(sf::Time Time)
{
	std::list<Asteroid>::iterator It;

	for (It = m_Asteroids.begin(); It != m_Asteroids.end(); ++It)
	{
		It->Render();
	}
}

void Game::Update(sf::Time Time)
{
	m_Player.Update(Time);
	UpdateAsteroids(Time);
	CheckCollisions();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_ActiveGameState = GSID_MAINMENU;
}

void Game::Render(sf::Time Time)
{
	m_Window.clear(sf::Color::Magenta);
	m_Window.draw(m_Background);
	m_Player.Render(Time);
	RenderAsteroids(Time);
}