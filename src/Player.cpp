#include "Player.hpp"

Player::Player(sf::RenderWindow &Window) :
	m_Window(Window),
	m_Alive(true)
{
	m_Player = new Animation("data/Player.png", 11, 64, 64, m_Window);
	
	m_ShotTex.loadFromFile("data/Laser.png");
	m_Shot = new sf::Sprite(m_ShotTex);

	m_Position.x = 376.0f;
	m_Position.y = 520.0f;

	m_PlayerAnimPhase = 5.0f;

	m_ShotLock = false;
}

Player::~Player()
{
	delete m_Shot;
	delete m_Player;
}

void Player::Update(sf::Time Time)
{
	ProcessMoving(Time);
	ProcessShooting(Time);
	CheckPosition();
}

void Player::Render(sf::Time Time)
{
	m_Player->setPosition(m_Position);
	m_Player->Render(m_PlayerAnimPhase);

	std::list<Shot>::iterator It = m_ShotList.begin();
	while (It != m_ShotList.end())
	{
		It->Update(Time);

		if (It->isAlive())
		{
			It->Render();
			It++;
		}
		else
		{
			It = m_ShotList.erase(It);
		}
	}
}

void Player::ProcessMoving(sf::Time Time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_Alive)
	{
		m_Position.x -= 300.0f * Time.asSeconds();
		m_PlayerAnimPhase -= 30.0f * Time.asSeconds();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_Alive)
	{
		m_Position.x += 300.0f * Time.asSeconds();
		m_PlayerAnimPhase += 30.0f * Time.asSeconds();
	}
	else
	{
		if (m_PlayerAnimPhase > 5.0f)
			m_PlayerAnimPhase -= 30.0f * Time.asSeconds();
		if (m_PlayerAnimPhase < 5.0f)
			m_PlayerAnimPhase += 30.0f * Time.asSeconds();
	}
}

void Player::ProcessShooting(sf::Time Time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_ShotLock && m_Alive)
	{
		Shot shot(m_Shot, m_Position, m_Window);

		m_ShotList.push_back(shot);

		m_ShotLock = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_ShotLock = false;
	}
}

void Player::CheckPosition()
{
	if (m_Position.x < 0.0f)
		m_Position.x = 0.0f;
	else if (m_Position.x > 736.0f)
		m_Position.x = 736.0f;

	if (m_PlayerAnimPhase < 0.0f)
		m_PlayerAnimPhase = 0.0f;
	else if (m_PlayerAnimPhase > 10.0f)
		m_PlayerAnimPhase = 10.0f;
}

std::list<Shot> *Player::getShotList()
{
	return &m_ShotList;
}

sf::IntRect Player::getCollisionRect() const
{
	return m_Player->getCollisionRect();
}

bool Player::isAlive() const
{
	return m_Alive;
}

void Player::setAlive(bool Alive)
{
	m_Alive = Alive;
}