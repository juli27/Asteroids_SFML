#include "Game.hpp"
#include <iostream>

Game::Game(sf::RenderWindow &window, const sf::Font* font) :
	GameState(GSID_GAME),
	m_Window(window),
	m_Points(0),
	m_Player(m_Window) {
	m_Asteroid = new Animation("data/Asteroid.png", 20, 64, 64, 10.0f);
	m_Explosion = new Animation("data/Explosion1.png", 16, 64, 64, 20.0f);

	m_AsteroidTimer = 0.0f;
}

Game::~Game() {
	delete m_Asteroid;
	std::cout << "Gesamtpunktzahl: " << m_Points << std::endl;
}

void Game::CheckCollisions() {
	std::list<Projectile> *projectiles = m_Player.getProjectiles();

	std::list<Asteroid>::iterator AsteroidIt = m_Asteroids.begin();
	std::list<Projectile>::iterator projectileIt;

	sf::IntRect AsteroidRect;
	sf::IntRect projectileRect;
	sf::IntRect PlayerRect = m_Player.getCollisionRect();

	while (AsteroidIt != m_Asteroids.end()) {
		AsteroidRect = AsteroidIt->getCollisionRect();

		for (projectileIt = projectiles->begin(); projectileIt != projectiles->end(); ++projectileIt) {
			projectileRect = projectileIt->getCollisionRect();

			if (projectileRect.intersects(AsteroidRect)) {
				AsteroidIt->setAlive(false);
				projectileIt->setAlive(false);
				m_Points++;

				Explosion Expl(AsteroidIt->getPosition());
				m_Explosions.push_back(Expl);
			}
		}

		if (PlayerRect.intersects(AsteroidRect)) {
			m_Player.setAlive(false);
			AsteroidIt->setAlive(false);

			Explosion Expl(AsteroidIt->getPosition());
			Explosion PlayerExpl(sf::Vector2f(static_cast<float> (PlayerRect.left), static_cast<float> (PlayerRect.top)));
			m_Explosions.push_back(Expl);
			m_Explosions.push_back(PlayerExpl);
		}

		if (AsteroidIt->isAlive())
			AsteroidIt++;
		else
			AsteroidIt = m_Asteroids.erase(AsteroidIt);
	}
}

void Game::UpdateAsteroids(sf::Time Time) {
	std::list<Asteroid>::iterator It;

	if (m_Player.isAlive()) {
		m_AsteroidTimer += Time.asSeconds();

		if (m_AsteroidTimer >= 0.5f) {
			Asteroid asteroid(m_Asteroid, sf::Vector2f(static_cast<float> (rand() % 736), -60.0f));

			m_Asteroids.push_back(asteroid);

			m_AsteroidTimer = 0.0f;
		}
	}

	for (It = m_Asteroids.begin(); It != m_Asteroids.end(); ++It) {
		It->Update(Time);
	}
}

void Game::UpdateEffects(sf::Time Time) {
	std::list<Explosion>::iterator It = m_Explosions.begin();

	while (It != m_Explosions.end()) {
		float Phase = It->getAnimationPhase();
		Phase += 20.0f * Time.asSeconds();
		if (Phase >= 16.0f) {
			It = m_Explosions.erase(It);
		}
		else {
			It->setAnimationPhase(Phase);
			++It;
		}
	}
}

void Game::RenderEffects() {
	std::list<Explosion>::iterator It;

	for (It = m_Explosions.begin(); It != m_Explosions.end(); ++It) {
		m_Explosion->setPosition(It->getPosition());
		m_Explosion->setFrame(static_cast<int> (It->getAnimationPhase()));
		m_Window.draw(*m_Explosion);
	}
}

void Game::RenderAsteroids() {
	std::list<Asteroid>::iterator It;

	for (It = m_Asteroids.begin(); It != m_Asteroids.end(); ++It) {
		It->Render();
	}
}

void Game::update(sf::Time& time) {
	m_Player.update(time);
	//UpdateAsteroids(time);
	UpdateEffects(time);
	CheckCollisions();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		GameStateManager::setNextActiveGameState(GSID_MAINMENU);
	}

	if (!m_Player.isAlive()) {
		if (m_Asteroids.empty()) {
			GameStateManager::setNextActiveGameState(GSID_MAINMENU);
		}
	}
}

void Game::render(sf::Time& time) {
	m_Player.render(time);
	RenderAsteroids();
	RenderEffects();
}
