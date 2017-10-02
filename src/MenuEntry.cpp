#include "MenuEntry.hpp"

MenuEntry::MenuEntry(const sf::String& text, const sf::Font& font, const float x, const float y)
  : m_text(text, font, 100u) {
  m_text.setPosition(x, y);
}

void MenuEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(m_text);
}

const sf::Vector2f& MenuEntry::getPosition() const {
  return m_text.getPosition();
}
