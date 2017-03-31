#include "Player.hpp"

Player::Player(sf::RenderWindow& window)
	: m_Window(window),
		m_Animation("data/Player.png", 11, 64, 64),
		m_ShotLock(false),
		m_Alive(true) {
	m_Position.x = 376.0f;
	m_Position.y = 520.0f;
	
	m_Animation.setPosition(m_Position);
	m_Animation.setFrame(5);
	m_Animation.setLooped(false);
}

Player::~Player() { }

void Player::update(sf::Time& time) {
	processMoving(time);
	processShooting(time);
}

void Player::render(sf::Time& time) {
	m_Animation.setPosition(m_Position);
	m_Window.draw(m_Animation);

	std::list<Projectile>::iterator it = m_Projectiles.begin();
	while (it != m_Projectiles.end()) {
		it->update(time);

		if (it->isAlive()) {
			m_Window.draw(*it);
			it++;
		}
		else {
			it = m_Projectiles.erase(it);
		}
	}
}

void Player::processMoving(sf::Time& time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_Alive) {
		m_Position.x -= 300.0f * time.asSeconds();
		if (m_Position.x < 0.0f)
			m_Position.x = 0.0f;
		
		m_Animation.setSpeed(-30.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_Alive) {
		m_Position.x += 300.0f * time.asSeconds();
		if (m_Position.x > 736.0f)
			m_Position.x = 736.0f;
		
		m_Animation.setSpeed(30.0f);
	}
	else {
		if (m_Animation.getFrame() > 5) {
			m_Animation.setSpeed(-30.0f);
		}
		else if (m_Animation.getFrame() < 5) {
			m_Animation.setSpeed(30.0f);
		}
		else {
			m_Animation.setSpeed(0.0f);
		}
	}

	m_Animation.update(time);
}

void Player::processShooting(sf::Time& time) {
	if (!m_ShotLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_Alive) {
		Projectile projectile(m_Position);

		m_Projectiles.push_back(projectile);

		m_ShotLock = true;
	}

	if (m_ShotLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_ShotLock = false;
	}
}

std::list<Projectile>* Player::getProjectiles() {
	return &m_Projectiles;
}

sf::IntRect Player::getCollisionRect() const {
	return m_Animation.getCollisionRect();
}

bool Player::isAlive() const {
	return m_Alive;
}

void Player::setAlive(bool Alive) {
	m_Alive = Alive;
}
