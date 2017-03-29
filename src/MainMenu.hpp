#pragma once

#include <map>

#include <SFML\Graphics.hpp>

#include "GameStateManager.hpp"
#include "MenuEntry.hpp"
#include "Animation.hpp"

enum MenuEntryID
{
	ME_NONE,
	ME_START,
	ME_OPTIONS,
	ME_QUIT
};

class MainMenu : public GameState
{
private:
	sf::RenderWindow &m_Window;
	sf::Sprite &m_Background;
	Animation *m_Cursor;
	float m_CursorAnimPhase;
	bool m_KeyLock;
	sf::Font m_Font;
	sf::Text m_Copyright;

	std::map<MenuEntryID, MenuEntry*> m_Entries;
	std::map<MenuEntryID, MenuEntry*>::iterator m_It;
	std::pair<MenuEntryID, MenuEntry*> m_Entry;

	MenuEntryID m_ActiveEntry;
	

public:
	MainMenu(sf::RenderWindow &window, sf::Sprite &background);
	~MainMenu();
	void update(sf::Time Time);
	void render(sf::Time Time);
};
