#pragma once

#include <list>

#include <SFML\Graphics.hpp>

#include "Animation.hpp"
#include "Projectile.hpp"

class Player : public sf::Drawable {
private:
  sf::RenderWindow& m_Window;
  Animation m_animation;
  sf::Vector2f m_position;
  bool m_alive;
  bool m_shotLock;
  //TODO: replace with object pool
  std::list<Projectile> m_projectiles;

  void processMoving(sf::Time& time);
  void processShooting();
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
  Player(sf::RenderWindow& window);

  void update(sf::Time& time);

  std::list<Projectile>* getProjectiles();
  sf::FloatRect getCollisionRect() const;
  bool isAlive() const;
  void setAlive(bool Alive);
};
