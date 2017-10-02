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
  Animation m_cursor;
  std::vector<MenuEntry> m_entries;
  sf::Text m_copyright;
  MenuEntryID m_activeEntry;
  bool m_keyLock;

public:
  MainMenu(sf::RenderWindow& window, const sf::Font& font);

  void update(sf::Time& time);
  void render();
};
