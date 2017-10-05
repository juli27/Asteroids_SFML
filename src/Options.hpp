#pragma once

#include <SFML\Graphics.hpp>

#include "GameState.hpp"

class Options : public GameState {
private:
  sf::Text m_vSync;
  sf::Text m_instructions;
  bool m_keyLock;

  static bool vSyncEnabled;

public:
  Options(sf::RenderWindow &window, const sf::Font& font);
  ~Options();

  void update(sf::Time& time);
  void render();
};
