#pragma once

#include <SFML\Graphics.hpp>

#include "Asteroid.hpp"
#include "Explosion.hpp"
#include "GameState.hpp"
#include "Player.hpp"

class Game : public GameState {
private:
	sf::RenderWindow &m_Window;
	Player m_Player;
	Animation *m_Explosion;
	std::list<Asteroid> m_Asteroids;
	std::list<Explosion> m_Explosions;
	float m_AsteroidTimer;
	int m_Points;

	void updateAsteroids(sf::Time& time);
	void UpdateEffects(sf::Time Time);
	void renderAsteroids();
	void RenderEffects();
	void CheckCollisions();

public:
	Game(sf::RenderWindow &window, const sf::Font* font);
	~Game();
	void update(sf::Time& time);
	void render(sf::Time& time);
};
