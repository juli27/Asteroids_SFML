#pragma once

#include "GameStateID.hpp"

class GameStateManager
{
private:
	GameStateID m_ActiveStateID;
public:
	GameStateManager();
	~GameStateManager();
	void setState(GameStateID ID);
	GameStateID getActiveStateID() const;
};