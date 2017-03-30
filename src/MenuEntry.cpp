#include "MenuEntry.hpp"

MenuEntry::MenuEntry(sf::String Text, float x, float y)
	: m_Active(false),
	m_Text(Text) {
	m_Font.loadFromFile("data/AGENCYR.TTF");

	m_Entry.setString(m_Text);
	m_Entry.setPosition(x, y);
	m_Entry.setFont(m_Font);
	m_Entry.setCharacterSize(100);
}

MenuEntry::~MenuEntry() { }

bool MenuEntry::isActive() const {
	return m_Active;
}

void MenuEntry::setActive() {
	this->m_Active = true;
}

sf::Vector2f MenuEntry::getPosition() const {
	return m_Entry.getPosition();
}

void MenuEntry::Render(sf::Time Time, sf::RenderWindow &Window) {
	Window.draw(m_Entry);
}
