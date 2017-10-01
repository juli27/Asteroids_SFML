#pragma once

#include <list>

#include "Animation.hpp"
#include "Projectile.hpp"

class Player {
private:
	sf::RenderWindow& m_Window;
	Animation m_Animation;
	sf::Vector2f m_Position;
	bool m_ShotLock;
	bool m_Alive;
	std::list<Projectile> m_Projectiles;

	void processMoving(sf::Time& time);
	void processShooting();

public:
	Player(sf::RenderWindow& window);
	~Player();

	void update(sf::Time& time);
	void render(sf::Time& time);

	std::list<Projectile>* getProjectiles();
	sf::IntRect getCollisionRect() const;
	bool isAlive() const;
	void setAlive(bool Alive);
};
