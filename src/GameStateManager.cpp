#include "GameStateManager.hpp"
#include "MainMenu.hpp"
#include "Options.hpp"
#include "Game.hpp"

GameState* GameStateManager::m_activeGameState = nullptr;
GameStateID GameStateManager::m_nextGameState = GSID_NONE;

GameState* GameStateManager::getActiveGameState() {
	return m_activeGameState;
}

void GameStateManager::setNextActiveGameState(GameStateID id) {
	m_nextGameState = id;
}

GameState* GameStateManager::updateActiveGameState(sf::RenderWindow& window, sf::Sprite& background) {
	if (!m_activeGameState || m_nextGameState != m_activeGameState->getGameStateID()) {
		if (m_activeGameState) {
			delete m_activeGameState;
		}

		switch (m_nextGameState)
		{
		case GSID_MAINMENU:
			m_activeGameState = new MainMenu(window, background);
			break;
		case GSID_OPTIONS:
			m_activeGameState = new Options(window, background);
			break;
		case GSID_GAME:
			m_activeGameState = new Game(window, background);
			break;
		default:
			m_activeGameState = new MainMenu(window, background);
			break;
		}
	}

	return m_activeGameState;
}
