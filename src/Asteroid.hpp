#pragma once

#include "Animation.hpp"

class Asteroid {
private:
	Animation *m_Asteroid;
	sf::Vector2f m_Position;
	sf::IntRect m_CollisionRect;
	float m_AsteroidAnimPhase;
	bool m_Alive;

public:
	Asteroid(Animation *Asteroid, sf::Vector2f Position);
	~Asteroid();
	void Update(sf::Time Time);
	void Render();
	bool isAlive() const;
	void setAlive(bool Alive);
	sf::IntRect getCollisionRect() const;
	sf::Vector2f getPosition() const;
};
