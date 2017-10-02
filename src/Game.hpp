#pragma once

#include <SFML\Graphics.hpp>

#include "Asteroid.hpp"
#include "GameState.hpp"
#include "Player.hpp"

class Game : public GameState {
private:
  Player m_player;
  Animation m_explosion;
  std::list<Asteroid> m_asteroids;
  std::list<Animation> m_effects;
  float m_asteroidTimer;
  int m_score;

  void updateAsteroids(sf::Time& time);
  void updateEffects(sf::Time& time);
  void checkCollisions();
  void renderAsteroids();
  void renderEffects();

public:
  Game(sf::RenderWindow& window, const sf::Font& font);
  ~Game();
  void update(sf::Time& time);
  void render();
};
