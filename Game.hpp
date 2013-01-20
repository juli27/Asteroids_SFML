#pragma once

#include  "GameState.hpp"
#include "Player.hpp"
#include "Asteroid.hpp"

class Game : public GameState
{
private:
	sf::RenderWindow &m_Window;
	sf::Sprite &m_Background;
	Player m_Player;
	Animation *m_Asteroid;
	std::list<Asteroid> m_Asteroids;
	float m_AsteroidTimer;
	int m_Points;

	void UpdateAsteroids(sf::Time Time);
	void RenderAsteroids(sf::Time Time);
	void CheckCollisions();

public:
	Game(sf::RenderWindow &Window, sf::Sprite &Background);
	~Game();
	void Update(sf::Time Time);
	void Render(sf::Time Time);
};