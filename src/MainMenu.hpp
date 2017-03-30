#pragma once

#include <map>

#include <SFML\Graphics.hpp>

#include "Animation.hpp"
#include "GameStateManager.hpp"
#include "MenuEntry.hpp"

enum MenuEntryID {
	ME_NONE,
	ME_START,
	ME_OPTIONS,
	ME_QUIT
};

class MainMenu : public GameState {
private:
	sf::RenderWindow &m_Window;
	Animation m_Cursor;
	bool m_KeyLock;
	sf::Text m_Copyright;

	std::map<MenuEntryID, MenuEntry*> m_Entries;
	std::map<MenuEntryID, MenuEntry*>::iterator m_It;
	std::pair<MenuEntryID, MenuEntry*> m_Entry;
	MenuEntryID m_ActiveEntry;

public:
	MainMenu(sf::RenderWindow &window, const sf::Font* font);
	~MainMenu();

	void update(sf::Time& time);
	void render(sf::Time& time);
};
