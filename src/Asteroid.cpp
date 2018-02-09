#include "Asteroid.hpp"

//TODO: a new Animation (and therefore a newtexture) for every Asteroid is bad :(
Asteroid::Asteroid(const sf::Vector2f& position)
    : Animation("data/Asteroid.png", 20, 64, 64, 10.0f),
      m_alive(true) {
  setPosition(position);
}

void Asteroid::update(sf::Time& time) {
  Animation::update(time);

  setPosition(getPosition().x, getPosition().y + 200.0f * time.asSeconds());

  if (getPosition().y > 600.0f) {
    m_alive = false;
  }
}

void Asteroid::setAlive(bool alive) {
  m_alive = alive;
}

bool Asteroid::isAlive() const {
	return m_alive;
}

sf::IntRect Asteroid::getCollisionRect() const {
	return sf::IntRect(getGlobalBounds());
}
