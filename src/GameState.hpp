#pragma once

enum GameStateID {
  GSID_NONE,
  GSID_MAINMENU,
  GSID_OPTIONS,
  GSID_GAME
};

class GameState {
private:
  const GameStateID gameStateID;
  bool hasNext;
  GameStateID nextGameStateID;

protected:
  void setNextGameStateID(GameStateID id) {
    hasNext = true;
    nextGameStateID = id;
  }

public:
  GameState(GameStateID id) : gameStateID(id), hasNext(false), nextGameStateID(GSID_NONE) { }
  virtual ~GameState() { }

  virtual void update(sf::Time& time) = 0;
  virtual void render(sf::Time& time) = 0;

  GameStateID getGameStateID() const {
    return gameStateID;
  }

  bool hasNextState() const {
    return hasNext;
  }

  GameStateID getNextGameStateID() const {
    return nextGameStateID;
  }
};
