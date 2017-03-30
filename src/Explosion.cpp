#include "Explosion.hpp"

Explosion::Explosion(sf::Vector2f Position) :
	m_AnimationPhase(0.0f),
	m_Position(Position) { }

Explosion::~Explosion() { }

float Explosion::getAnimationPhase() const {
	return m_AnimationPhase;
}

const sf::Vector2f Explosion::getPosition() const {
	return m_Position;
}

void Explosion::setAnimationPhase(float Phase) {
	m_AnimationPhase = Phase;
}
