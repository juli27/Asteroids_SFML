#include "Asteroid.hpp"

Asteroid::Asteroid(sf::Vector2f& position)
	: Animation("data/Asteroid.png", 20, 64, 64, 10.0f),
		m_Alive(true) {
	setPosition(position);
}

Asteroid::~Asteroid() { }

void Asteroid::update(sf::Time& time) {
	this->Animation::update(time);

	setPosition(getPosition().x, getPosition().y + 200.0f * time.asSeconds());

	if (getPosition().y > 600.0f) {
		m_Alive = false;
	}
}

void Asteroid::setAlive(bool Alive) {
	m_Alive = Alive;
}

bool Asteroid::isAlive() const {
	return m_Alive;
}

sf::IntRect Asteroid::getCollisionRect() const {
	return sf::IntRect(getGlobalBounds());
}
