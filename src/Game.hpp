#pragma once

#include <SFML\Graphics.hpp>

#include "Asteroid.hpp"
#include "Explosion.hpp"
#include "GameStateManager.hpp"
#include "Player.hpp"

class Game : public GameState {
private:
	sf::RenderWindow &m_Window;
	Player m_Player;
	Animation *m_Asteroid;
	Animation *m_Explosion;
	std::list<Asteroid> m_Asteroids;
	std::list<Explosion> m_Explosions;
	float m_AsteroidTimer;
	int m_Points;

	void UpdateAsteroids(sf::Time Time);
	void UpdateEffects(sf::Time Time);
	void RenderAsteroids();
	void RenderEffects();
	void CheckCollisions();

public:
	Game(sf::RenderWindow &window, const sf::Font* font);
	~Game();
	void update(sf::Time& time);
	void render(sf::Time& time);
};
