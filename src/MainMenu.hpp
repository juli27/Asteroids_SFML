#pragma once

#include <vector>

#include <SFML\Graphics.hpp>

#include "Animation.hpp"
#include "GameState.hpp"
#include "MenuEntry.hpp"

enum MenuEntryID {
  ME_START,
  ME_OPTIONS,
  ME_QUIT
};

class MainMenu : public GameState {
private:
  sf::RenderWindow &m_Window;
  Animation m_Cursor;
  sf::Text m_Copyright;
  std::vector<MenuEntry*> entries;
  MenuEntryID activeEntry;
  bool keyLock;

public:
  MainMenu(sf::RenderWindow& window, const sf::Font* font);
  ~MainMenu();

  void update(sf::Time& time);
  void render(sf::Time& time);
};
