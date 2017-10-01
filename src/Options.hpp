#pragma once

#include <SFML\Graphics.hpp>

#include "GameState.hpp"

class Options : public GameState {
private:
  sf::RenderWindow &m_Window;
  sf::Text m_VSync;
  sf::Text m_Instructions;
  bool m_VSyncEnabled;
  bool m_KeyLock;

public:
  Options(sf::RenderWindow &window, const sf::Font* font);
  ~Options();

  void update(sf::Time& time);
  void render(sf::Time& time);
};
