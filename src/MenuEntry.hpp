#pragma once

#include <SFML\Graphics.hpp>

class MenuEntry : public sf::Drawable {
private:
  sf::Text m_text;

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
  MenuEntry(const sf::String& text, const sf::Font& font, const float x, const float y);
  const sf::Vector2f& getPosition() const;
};
