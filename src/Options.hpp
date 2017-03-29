#pragma once

#include "GameState.hpp"

class Options : public GameState
{
private:
	sf::RenderWindow &m_Window;
	sf::Sprite &m_Background;
	bool m_KeyLock;
	sf::Font m_Font;
	sf::Text m_VSync;
	sf::Text m_Instructions;
	static bool m_VSyncEnabled;

public:

	Options(sf::RenderWindow &Window, sf::Sprite &Background);
	~Options();
	void Update(sf::Time Time);
	void Render(sf::Time Time);

};