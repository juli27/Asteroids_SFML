#include "Game.hpp"

Game::Game(sf::RenderWindow *Window, GameStateManager *GSM, sf::Sprite &Background)
	: m_Window(Window),
	  m_Background(Background),
	  m_GSM(GSM)
{
	m_Player = new Player(m_Window);
	m_Asteroid = new Animation("data/Asteroid.bmp", 20, 64, 64, m_Window);

	m_AsteroidTimer = 0.0f;
}

Game::~Game()
{
	delete m_Player;
	delete m_Asteroid;
}

void Game::SpawnAsteroids(sf::Time Time)
{
	m_AsteroidTimer += Time.asSeconds();

	if (m_AsteroidTimer >= 0.5f)
	{
		Asteroid asteroid(m_Asteroid, sf::Vector2f(static_cast<float> (rand()%736), -60.0f));

		m_Asteroids.push_back(asteroid);

		m_AsteroidTimer = 0.0f;
	}
}

void Game::CheckCollisions()
{
	std::list<Shot> *ShotList = m_Player->getShotList();

	std::list<Asteroid>::iterator AsteroidIt = m_Asteroids.begin();
	std::list<Shot>::iterator ShotIt;

	sf::IntRect AsteroidRect;
	sf::IntRect ShotRect;

	while (AsteroidIt != m_Asteroids.end())
	{
		AsteroidRect = AsteroidIt->getCollisionRect();

		for (ShotIt = ShotList->begin(); ShotIt != ShotList->end(); ++ShotIt)
		{
			ShotRect = ShotIt->getRect();

			if (ShotRect.top < AsteroidRect.top + AsteroidRect.height &&
				ShotRect.top + ShotRect.height > AsteroidRect.top &&
				ShotRect.left < AsteroidRect.left + AsteroidRect.width &&
				ShotRect.left + ShotRect.width > AsteroidRect.left)
			{
				AsteroidIt->setAlive(false);
				ShotIt->setAlive(false);
			}
		}

		if (AsteroidIt->isAlive())
			AsteroidIt++;
		else
			AsteroidIt = m_Asteroids.erase(AsteroidIt);
	}
}
void Game::RenderAsteroids(sf::Time Time)
{
	std::list<Asteroid>::iterator It;

	for (It = m_Asteroids.begin(); It != m_Asteroids.end(); ++It)
	{
		It->Render();
		It->Update(Time);
	}
}

void Game::Update(sf::Time Time)
{
	m_Player->Update(Time);
	SpawnAsteroids(Time);
	CheckCollisions();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		m_GSM->setState(GSID_MAINMENU);
}

void Game::Render(sf::Time Time)
{
	m_Window->clear(sf::Color::Magenta);
	m_Window->draw(m_Background);
	m_Player->Render(Time);
	RenderAsteroids(Time);
}