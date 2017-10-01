#include "Projectile.hpp"

sf::Texture* Projectile::m_Tex;

Projectile::Projectile(sf::Vector2f& pos)
	: m_Alive(true) {
	if (!m_Tex) {
		m_Tex = new sf::Texture();
		m_Tex->loadFromFile("data/Laser.png");
	}

	setTexture(*m_Tex);
	setPosition(pos);
}

Projectile::~Projectile() {
  //TODO m_Tex memory leak
}

void Projectile::update(sf::Time& time) {
	setPosition(getPosition().x, getPosition().y - 400.0f * time.asSeconds());

	if (getPosition().y < -20.0f)
		m_Alive = false;
}

bool Projectile::isAlive() const {
	return m_Alive;
}

void Projectile::setAlive(bool alive) {
	m_Alive = alive;
}

sf::IntRect Projectile::getCollisionRect() const {
	return sf::IntRect(getGlobalBounds());
}
