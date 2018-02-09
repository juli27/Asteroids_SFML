#pragma once

//TODO replace with forward declaration ?
#include <SFML\System\Time.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class ResourceManager;

enum GameStateID {
  GSID_NONE,
  GSID_MAINMENU,
  GSID_OPTIONS,
  GSID_GAME
};

class GameState {
private:
  const GameStateID m_gameStateID;
  bool m_hasNext;
  GameStateID m_nextGameStateID;

  // ResourceManager/loader as static member, call switch state on GameState ctor
  static ResourceManager resManager;

protected:
  sf::RenderWindow& m_window;

  void setNextGameStateID(GameStateID id) {
    m_hasNext = true;
    m_nextGameStateID = id;
  }

public:
  GameState(GameStateID id, sf::RenderWindow& window) : m_gameStateID(id), m_window(window),
    m_hasNext(false), m_nextGameStateID(GSID_NONE) { }
  virtual ~GameState() { }

  virtual void update(sf::Time& time) = 0;
  virtual void render() = 0;

  GameStateID getGameStateID() const {
    return m_gameStateID;
  }

  bool hasNextState() const {
    return m_hasNext;
  }

  GameStateID getNextGameStateID() const {
    return m_nextGameStateID;
  }
};
