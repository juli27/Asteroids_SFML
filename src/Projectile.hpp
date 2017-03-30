#pragma once

#include "SFML\Graphics.hpp"

class Shot {
private:
	sf::RenderWindow &m_Window;
	sf::Sprite *m_Shot;
	sf::Vector2f m_Position;
	sf::IntRect m_CollisionRect;
	bool m_Alive;

public:
	Shot(sf::Sprite *Shot, sf::Vector2f Pos, sf::RenderWindow &Window);
	~Shot();
	void Update(sf::Time Time);
	void Render();
	bool isAlive() const;
	void setAlive(bool Alive);
	sf::IntRect getCollisionRect() const;
};
