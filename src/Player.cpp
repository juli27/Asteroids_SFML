#include "Player.hpp"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

Player::Player(sf::RenderWindow& window)
    : m_Window(window),
      m_animation("data/Player.png", 11, 64, 64, 0.0f, false),
      m_position(376.f, 520.f),
      m_alive(true),
      m_shotLock(false) {
  m_animation.setPosition(m_position);
  m_animation.setFrame(5);
}

void Player::processMoving(sf::Time& time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_alive) {
    m_position.x -= 300.f * time.asSeconds();

    if (m_position.x < 0.f) {
      m_position.x = 0.f;
    }

    m_animation.setPosition(m_position);
    m_animation.setSpeed(-30.f);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_alive) {
    m_position.x += 300.f * time.asSeconds();

    if (m_position.x > 736.f) {
      m_position.x = 736.f;
    }

    m_animation.setPosition(m_position);
    m_animation.setSpeed(30.0f);
  } else {
    if (m_animation.getFrame() > 5) {
      m_animation.setSpeed(-30.0f);
    } else if (m_animation.getFrame() < 5) {
      m_animation.setSpeed(30.0f);
    } else {
      m_animation.setSpeed(0.0f);
    }
  }

  m_animation.update(time);
}

void Player::processShooting() {
  if (!m_shotLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_alive) {
    m_shotLock = true;

    m_projectiles.emplace_back(m_position);
  }

  if (m_shotLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    m_shotLock = false;
  }
}

void Player::update(sf::Time& time) {
  processMoving(time);
  processShooting();

  std::list<Projectile>::iterator it = m_projectiles.begin();
  while (it != m_projectiles.end()) {
    it->update(time);

    if (!it->isAlive()) {
      it = m_projectiles.erase(it);
    } else {
      ++it;
    }
  }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (m_alive) {
    target.draw(m_animation, states);
  }

  for (std::list<Projectile>::const_iterator it = m_projectiles.cbegin(); it != m_projectiles.end(); ++it) {
    target.draw(*it, states);
  }
}

std::list<Projectile>* Player::getProjectiles() {
  return &m_projectiles;
}

sf::FloatRect Player::getCollisionRect() const {
  return m_animation.getGlobalBounds();
}

bool Player::isAlive() const {
  return m_alive;
}

void Player::setAlive(bool Alive) {
  m_alive = Alive;
}
