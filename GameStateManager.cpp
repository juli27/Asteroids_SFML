#include "GameStateManager.hpp"

GameStateManager::GameStateManager()
	: m_ActiveStateID(GSID_NONE)
{
}

GameStateManager::~GameStateManager()
{
}

void GameStateManager::setState(GameStateID ID)
{
	m_ActiveStateID = ID;
}

GameStateID GameStateManager::getActiveStateID()
{
	return m_ActiveStateID;
}