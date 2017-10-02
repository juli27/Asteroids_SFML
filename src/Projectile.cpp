#include "Projectile.hpp"

sf::Texture* Projectile::texture = nullptr;

Projectile::Projectile(sf::Vector2f& pos) : m_alive(true) {
  if (!texture) {
    texture = new sf::Texture();
    texture->loadFromFile("data/Laser.png");
  }

  setTexture(*texture);
  setPosition(pos);
}

Projectile::~Projectile() {
  //TODO m_Tex memory leak
}

void Projectile::update(sf::Time& time) {
  setPosition(getPosition().x, getPosition().y - 400.0f * time.asSeconds());

  if (getPosition().y < -20.0f) {
    m_alive = false;
  }
}

bool Projectile::isAlive() const {
  return m_alive;
}

void Projectile::setAlive(bool alive) {
  m_alive = alive;
}

sf::IntRect Projectile::getCollisionRect() const {
  return sf::IntRect(getGlobalBounds());
}
