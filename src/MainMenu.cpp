#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow& window, const sf::Font& font)
    : GameState(GSID_MAINMENU, window),
      m_cursor("data/Asteroid.png", 20, 64, 64, 10.0f),
      m_copyright("Julian Bühler 2013/2017", font, 20u),
      m_activeEntry(ME_START),
      m_keyLock(true) {
  m_entries.emplace_back("Start", font, 300.f, 200.f);
  m_entries.emplace_back("Options", font, 300.0f, 300.0f);
  m_entries.emplace_back("Quit", font, 300.0f, 400.0f);

  sf::Vector2f entryPos = m_entries[m_activeEntry].getPosition();
  m_cursor.setPosition(entryPos.x - 70, entryPos.y + 30);

  m_copyright.setPosition(650, 580);
}

void MainMenu::update(sf::Time& time) {
  if (!m_keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    switch (m_activeEntry) {
    case ME_START:
      m_activeEntry = ME_OPTIONS;
      break;
    case ME_OPTIONS:
      m_activeEntry = ME_QUIT;
      break;
    case ME_QUIT:
      m_activeEntry = ME_START;
      break;
    default:
      break;
    }

    sf::Vector2f entryPos = m_entries[m_activeEntry].getPosition();
    m_cursor.setPosition(entryPos.x - 70, entryPos.y + 30);

    m_keyLock = true;
  }

  if (!m_keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    switch (m_activeEntry) {
    case ME_START:
      m_activeEntry = ME_QUIT;
      break;
    case ME_OPTIONS:
      m_activeEntry = ME_START;
      break;
    case ME_QUIT:
      m_activeEntry = ME_OPTIONS;
      break;
    default:
      break;
    }

    sf::Vector2f entryPos = m_entries[m_activeEntry].getPosition();
    m_cursor.setPosition(entryPos.x - 70, entryPos.y + 30);

    m_keyLock = true;
  }

  if (!m_keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    switch (m_activeEntry) {
    case ME_START:
      setNextGameStateID(GSID_GAME);
      break;
    case ME_OPTIONS:
      setNextGameStateID(GSID_OPTIONS);
      break;
    case ME_QUIT:
      m_window.close();
      break;
    default:
      break;
    }

    m_keyLock = true;
  }

  if (m_keyLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
    && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    m_keyLock = false;
  }

  m_cursor.update(time);
}

void MainMenu::render() {
  for (std::vector<MenuEntry>::iterator it = m_entries.begin(); it != m_entries.end(); ++it) {
    m_window.draw(*it);
  }

  m_window.draw(m_cursor);
  m_window.draw(m_copyright);
}
