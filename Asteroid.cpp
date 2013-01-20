#include "Asteroid.hpp"

Asteroid::Asteroid(Animation *Asteroid, sf::Vector2f Position)
{
	m_Asteroid = Asteroid;
	m_Position.x = Position.x;
	m_Position.y = Position.y;

	m_AsteroidAnimPhase = 0.0f;

	m_CollisionRect.left = static_cast<int> (m_Position.x);
	m_CollisionRect.top = static_cast<int> (m_Position.y);
	m_CollisionRect.width = static_cast<int> (m_Asteroid->getCollisionRect().width);
	m_CollisionRect.height = static_cast<int> (m_Asteroid->getCollisionRect().height);

	m_Alive = true;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(sf::Time Time)
{
	m_Position.y += 200.0f * Time.asSeconds();
	m_CollisionRect.top = static_cast<int> (m_Position.y);

	m_AsteroidAnimPhase += 10.0f * Time.asSeconds();

	if (m_AsteroidAnimPhase >= 20.0f)
		m_AsteroidAnimPhase -= 20.0f;

	if (m_Position.y > 600.0f)
		m_Alive = false;

}

void Asteroid::Render()
{
	m_Asteroid->setPosition(m_Position);
	m_Asteroid->Render(m_AsteroidAnimPhase);
}

bool Asteroid::isAlive() const
{
	return m_Alive;
}

void Asteroid::setAlive(bool Alive)
{
	m_Alive = Alive;
}

sf::IntRect Asteroid::getCollisionRect() const
{
	return m_CollisionRect;
}