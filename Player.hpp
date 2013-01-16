#pragma once

#include "Animation.hpp"
#include "Shot.hpp"
#include <list>

class Player
{
private:
	sf::RenderWindow *m_Window;
	Animation *m_Player;
	sf::Texture m_ShotTex;
	sf::Sprite *m_Shot;
	sf::Vector2f m_Position;
	float m_PlayerAnimPhase;
	bool m_ShotLock;

	std::list<Shot> m_ShotList;

	void ProcessMoving(sf::Time Time);
	void ProcessShooting(sf::Time Time);
	void CheckPosition();

public:
	Player(sf::RenderWindow *Window);
	~Player();
	void Update(sf::Time Time);
	void Render(sf::Time Time);
	std::list<Shot> *getShotList();
	sf::IntRect getCollisionRect() const;
};