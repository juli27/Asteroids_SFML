#pragma once

#include "SFML\Graphics.hpp"

class MenuEntry {
private:
  sf::String m_Text;
  sf::Font m_Font;
  sf::Text m_Entry;

public:
  MenuEntry(sf::String text, float x, float y);
  ~MenuEntry();
  sf::Vector2f getPosition() const;
  void Render(sf::RenderWindow &Window);
};
