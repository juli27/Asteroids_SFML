#include "MenuEntry.hpp"

MenuEntry::MenuEntry(sf::String text, float x, float y) : m_Text(text) {
  m_Font.loadFromFile("data/AGENCYR.TTF");

  m_Entry.setString(m_Text);
  m_Entry.setPosition(x, y);
  m_Entry.setFont(m_Font);
  m_Entry.setCharacterSize(100);
}

MenuEntry::~MenuEntry() {

}

sf::Vector2f MenuEntry::getPosition() const {
	return m_Entry.getPosition();
}

void MenuEntry::Render(sf::RenderWindow &Window) {
	Window.draw(m_Entry);
}
