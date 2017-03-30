#include "Player.hpp"

Player::Player(sf::RenderWindow& window)
	: m_Window(window),
		m_Animation("data/Player.png", 11, 64, 64),
		m_ShotLock(false),
		m_Alive(true) {
	m_ShotTex.loadFromFile("data/Laser.png");
	m_Shot = new sf::Sprite(m_ShotTex);

	m_Position.x = 376.0f;
	m_Position.y = 520.0f;
	
	m_Animation.setPosition(m_Position);
	m_Animation.setFrame(5);
	m_Animation.setLooped(false);
}

Player::~Player() {
	delete m_Shot;
}

void Player::update(sf::Time& time) {
	processMoving(time);
	processShooting(time);
}

void Player::render(sf::Time& Time) {
	m_Animation.setPosition(m_Position);
	m_Window.draw(m_Animation);

	std::list<Shot>::iterator It = m_ShotList.begin();
	while (It != m_ShotList.end()) {
		It->Update(Time);

		if (It->isAlive()) {
			It->Render();
			It++;
		}
		else {
			It = m_ShotList.erase(It);
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
		Shot shot(m_Shot, m_Position, m_Window);

		m_ShotList.push_back(shot);

		m_ShotLock = true;
	}

	if (m_ShotLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_ShotLock = false;
	}
}

std::list<Shot> *Player::getShotList() {
	return &m_ShotList;
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
