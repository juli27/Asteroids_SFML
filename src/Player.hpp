#pragma once

#include <list>

#include "Animation.hpp"
#include "Projectile.hpp"

class Player {
private:
	sf::RenderWindow& m_Window;
	Animation m_Animation;
	sf::Texture m_ShotTex;
	sf::Sprite *m_Shot;
	sf::Vector2f m_Position;
	bool m_ShotLock;
	bool m_Alive;

	std::list<Shot> m_ShotList;

	void processMoving(sf::Time& time);
	void processShooting(sf::Time& time);

public:
	Player(sf::RenderWindow& window);
	~Player();

	void update(sf::Time& time);
	void render(sf::Time& time);

	std::list<Shot> *getShotList();
	sf::IntRect getCollisionRect() const;
	bool isAlive() const;
	void setAlive(bool Alive);
};
