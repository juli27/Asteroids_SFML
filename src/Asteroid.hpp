#pragma once

#include "Animation.hpp"

class Asteroid : public Animation {
private:
  bool m_alive;

public:
  Asteroid(const sf::Vector2f& position);

  void update(sf::Time& time);

  void setAlive(bool alive);
  bool isAlive() const;
  sf::IntRect getCollisionRect() const;
};
