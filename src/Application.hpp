#pragma once

#include <SFML\Graphics.hpp>
#include "GameState.hpp"

class Application {
private:
  sf::Sprite m_Background;
  sf::Text m_FPSText;
  GameState* currentGameState;

public:
  Application();
  ~Application();
  void run();
};
