#pragma once

#include "SFML\Graphics.hpp"

class MenuEntry
{
private:
	bool m_Active;
	sf::String m_Text;
	sf::Font m_Font;
	sf::Text m_Entry;

public:
	MenuEntry(sf::String Text, float x, float y);
	~MenuEntry();
	bool isActive() const;
	void setActive();
	sf::Vector2f getPosition() const;
	void Render(sf::Time Time, sf::RenderWindow &Window);
};