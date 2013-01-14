#pragma once

#include "GameState.hpp"
#include "GameStateManager.hpp"
#include "MenuEntry.hpp"
#include "Animation.hpp"
#include <map>

enum MenuEntryID
{
	ME_NONE,
	ME_START,
	ME_QUIT
};

class MainMenu : public GameState
{
private:
	GameStateManager *m_GSM;
	sf::RenderWindow *m_Window;
	sf::Sprite m_Background;
	Animation *m_Cursor;
	float m_CursorAnimPhase;

	std::map<MenuEntryID, MenuEntry*> m_Entries;
	std::map<MenuEntryID, MenuEntry*>::iterator m_It;
	std::pair<MenuEntryID, MenuEntry*> m_Entry;

	MenuEntryID m_ActiveEntry;
	

public:
	MainMenu(sf::RenderWindow *Window, GameStateManager *GSM, sf::Sprite &Background);
	~MainMenu();
	void Update(sf::Time Time);
	void Render(sf::Time Time);
};