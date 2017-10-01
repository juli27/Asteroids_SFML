#pragma once

#include "Animation.hpp"

class Asteroid : public Animation {
private:
	bool m_Alive;

public:
	Asteroid(sf::Vector2f& position);
	virtual ~Asteroid();

	void update(sf::Time& time);

	void setAlive(bool Alive);
	bool isAlive() const;
	sf::IntRect getCollisionRect() const;
};
