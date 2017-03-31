#pragma once

#include <SFML\Graphics.hpp>

class Projectile : public sf::Sprite {
private:
	bool m_Alive;

	static sf::Texture* m_Tex;

public:
	Projectile(sf::Vector2f& pos);
	virtual ~Projectile();

	void update(sf::Time& time);

	void setAlive(bool alive);
	bool isAlive() const;
	sf::IntRect getCollisionRect() const;
};
