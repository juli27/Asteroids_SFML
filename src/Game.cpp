#include "Game.hpp"
#include <iostream>

Game::Game(sf::RenderWindow& window, const sf::Font* font) :
	GameState(GSID_GAME),
	m_Window(window),
	m_Points(0),
	m_Player(m_Window) {
	m_Explosion = new Animation("data/Explosion1.png", 16, 64, 64, 20.0f);

	m_AsteroidTimer = 0.0f;
}

Game::~Game() {
	delete m_Explosion;
	std::cout << "Gesamtpunktzahl: " << m_Points << std::endl;
}

void Game::CheckCollisions() {
	std::list<Projectile> *projectiles = m_Player.getProjectiles();

	std::list<Asteroid>::iterator asteroidIt = m_Asteroids.begin();
	std::list<Projectile>::iterator projectileIt;

	sf::IntRect asteroidRect;
	sf::IntRect projectileRect;
	sf::IntRect PlayerRect = m_Player.getCollisionRect();

	while (asteroidIt != m_Asteroids.end()) {
		asteroidRect = asteroidIt->getCollisionRect();

		for (projectileIt = projectiles->begin(); projectileIt != projectiles->end(); ++projectileIt) {
			projectileRect = projectileIt->getCollisionRect();

			if (projectileRect.intersects(asteroidRect)) {
				asteroidIt->setAlive(false);
				projectileIt->setAlive(false);
				m_Points++;

				Explosion Expl(asteroidIt->getPosition());
				m_Explosions.push_back(Expl);
			}
		}

		if (PlayerRect.intersects(asteroidRect)) {
			m_Player.setAlive(false);
			asteroidIt->setAlive(false);

			Explosion Expl(asteroidIt->getPosition());
			Explosion PlayerExpl(sf::Vector2f(static_cast<float> (PlayerRect.left), static_cast<float> (PlayerRect.top)));
			m_Explosions.push_back(Expl);
			m_Explosions.push_back(PlayerExpl);
		}

		if (asteroidIt->isAlive())
			asteroidIt++;
		else
			asteroidIt = m_Asteroids.erase(asteroidIt);
	}
}

void Game::updateAsteroids(sf::Time& time) {
	if (m_Player.isAlive()) {
		m_AsteroidTimer += time.asSeconds();

		if (m_AsteroidTimer >= 0.5f) {
			Asteroid asteroid(sf::Vector2f(static_cast<float> (rand() % 736), -60.0f));

			m_Asteroids.push_back(asteroid);

			m_AsteroidTimer = 0.0f;
		}
	}

	for (std::list<Asteroid>::iterator it = m_Asteroids.begin(); it != m_Asteroids.end(); ++it) {
		it->update(time);
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

void Game::renderAsteroids() {
	for (std::list<Asteroid>::iterator it = m_Asteroids.begin(); it != m_Asteroids.end(); ++it) {
		m_Window.draw(*it);
	}
}

void Game::update(sf::Time& time) {
	m_Player.update(time);
	//updateAsteroids(time);
	UpdateEffects(time);
	CheckCollisions();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    setNextGameStateID(GSID_MAINMENU);
	}

	if (!m_Player.isAlive()) {
		if (m_Asteroids.empty()) {
      setNextGameStateID(GSID_MAINMENU);
		}
	}
}

void Game::render(sf::Time& time) {
	m_Player.render(time);
	renderAsteroids();
	RenderEffects();
}
