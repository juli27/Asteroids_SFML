#include "Shot.hpp"

Shot::Shot(sf::Sprite *Shot, sf::Vector2f Pos, sf::RenderWindow &Window)
	: m_Shot(Shot),
	  m_Position(Pos),
	  m_Window(Window)
{
	m_CollisionRect.left = static_cast<int> (m_Position.x);
	m_CollisionRect.top = static_cast<int> (m_Position.y);
	m_CollisionRect.width = static_cast<int>(m_Shot->getLocalBounds().width);
	m_CollisionRect.height = static_cast<int> (m_Shot->getLocalBounds().height);

	m_Alive = true;
}

Shot::~Shot()
{
}

void Shot::Update(sf::Time Time)
{
	m_Position.y -= 400.0f * Time.asSeconds();

	m_CollisionRect.top = static_cast<int> (m_Position.y);

	if (m_Position.y < -20.0f)
		m_Alive = false;
}

void Shot::Render()
{
	if (m_Alive)
	{
		m_Shot->setPosition(m_Position);
		m_Window.draw(*m_Shot);
	}
}

bool Shot::isAlive() const
{
	return m_Alive;
}

void Shot::setAlive(bool Alive)
{
	m_Alive = Alive;
}

sf::IntRect Shot::getCollisionRect() const
{
	return m_CollisionRect;
}