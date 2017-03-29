#pragma once

#include "SFML\Graphics.hpp"

class Explosion
{
private:
	float m_AnimationPhase;
	sf::Vector2f m_Position;

public:
	Explosion(sf::Vector2f Position);
	~Explosion();
	float getAnimationPhase() const;
	const sf::Vector2f getPosition() const;
	void setAnimationPhase(float Phase);
};