#include "Game.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

Game::Game(sf::RenderWindow& window, const sf::Font& font)
    : GameState(GSID_GAME, window),
      m_player(window),
      m_explosion("data/Explosion1.png", 16, 64, 64, 20.0f, false),
      m_score(0),
      m_asteroidTimer(0.f) {}

Game::~Game() {
#ifdef _DEBUG
  std::cout << "Score: " << m_score << std::endl;
#endif // _DEBUG
}

void Game::updateAsteroids(sf::Time& time) {
  if (m_player.isAlive()) {
    m_asteroidTimer += time.asSeconds();

    if (m_asteroidTimer >= 0.5f) {
      //TODO: rand() is bad
      const sf::Vector2f asteroisPos(static_cast<float> (rand() % 736), -60.0f);
      m_asteroids.emplace_back(asteroisPos);

      m_asteroidTimer = 0.0f;
    }
  }

  for (std::list<Asteroid>::iterator it = m_asteroids.begin(); it != m_asteroids.end(); ++it) {
    it->update(time);
  }
}

void Game::updateEffects(sf::Time& time) {
  std::list<Animation>::iterator it = m_effects.begin();

  while (it != m_effects.end()) {
    if (it->getFrame() >= 15) {
      it = m_effects.erase(it);
    } else {
      it->update(time);
      ++it;
    }
  }
}

void Game::checkCollisions() {
  sf::FloatRect playerRect = m_player.getCollisionRect();

  std::list<Projectile>* projectiles = m_player.getProjectiles();

  std::list<Asteroid>::iterator asteroidIt = m_asteroids.begin();

  while (asteroidIt != m_asteroids.end()) {
    sf::FloatRect asteroidRect = asteroidIt->getGlobalBounds();

    for (std::list<Projectile>::iterator projectileIt = projectiles->begin(); projectileIt != projectiles->end(); ++projectileIt) {
      sf::FloatRect projectileRect = projectileIt->getGlobalBounds();

      if (projectileRect.intersects(asteroidRect)) {
        asteroidIt->setAlive(false);
        projectileIt->setAlive(false);
        ++m_score;

        m_effects.emplace_back("data/Explosion1.png", 16, 64, 64, 20.0f, false);
        m_effects.back().setPosition(asteroidIt->getPosition());
      }
    }

    if (playerRect.intersects(asteroidRect)) {
      m_player.setAlive(false);
      asteroidIt->setAlive(false);

      m_effects.emplace_back("data/Explosion1.png", 16, 64, 64, 20.0f, false);
      m_effects.back().setPosition(asteroidIt->getPosition());

      m_effects.emplace_back("data/Explosion1.png", 16, 64, 64, 20.0f, false);
      m_effects.back().setPosition(playerRect.left, playerRect.top);
    }

    if (asteroidIt->isAlive()) {
      ++asteroidIt;
    } else {
      asteroidIt = m_asteroids.erase(asteroidIt);
    }
  }
}

void Game::update(sf::Time& time) {
  m_player.update(time);
  updateAsteroids(time);
  updateEffects(time);
  checkCollisions();

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    setNextGameStateID(GSID_MAINMENU);
  }

  if (!m_player.isAlive()) {
    if (m_asteroids.empty()) {
      setNextGameStateID(GSID_MAINMENU);
    }
  }
}

void Game::render() {
  m_window.draw(m_player);

  for (std::list<Asteroid>::const_iterator it = m_asteroids.cbegin(); it != m_asteroids.cend(); ++it) {
    m_window.draw(*it);
  }

  for (std::list<Animation>::const_iterator it = m_effects.cbegin(); it != m_effects.cend(); ++it) {
    m_window.draw(*it);
  }
}
