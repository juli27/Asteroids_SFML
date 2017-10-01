#include "MainMenu.hpp"

MainMenu::MainMenu(sf::RenderWindow& window, const sf::Font* font) : GameState(GSID_MAINMENU),
    m_Window(window),
    m_Cursor("data/Asteroid.png", 20, 64, 64, 10.0f),
    activeEntry(ME_START),
    m_Copyright("Julian Bühler 2013/2017", *font, 20),
    keyLock(true) {
  // init menu entries
  entries.push_back(new MenuEntry("Start", 300.0f, 200.0f));
  entries.push_back(new MenuEntry("Options", 300.0f, 300.0f));
  entries.push_back(new MenuEntry("Quit", 300.0f, 400.0f));

  // init cursor
  MenuEntry* entry = entries[activeEntry];
  m_Cursor.setPosition(entry->getPosition().x - 70, entry->getPosition().y + 30);

  m_Copyright.setPosition(650, 580);
}

MainMenu::~MainMenu() {
  for (std::vector<MenuEntry*>::iterator it = entries.begin(); it != entries.end(); ++it) {
    delete (*it);
  }
}

void MainMenu::update(sf::Time& time) {
  if (!keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    switch (activeEntry) {
    case ME_START:
      activeEntry = ME_OPTIONS;
      break;
    case ME_OPTIONS:
      activeEntry = ME_QUIT;
      break;
    case ME_QUIT:
      activeEntry = ME_START;
      break;
    default:
      break;
    }

    sf::Vector2f entryPos = entries[activeEntry]->getPosition();
    m_Cursor.setPosition(entryPos.x - 70, entryPos.y + 30);

    keyLock = true;
  }

  if (!keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    switch (activeEntry) {
    case ME_START:
      activeEntry = ME_QUIT;
      break;
    case ME_OPTIONS:
      activeEntry = ME_START;
      break;
    case ME_QUIT:
      activeEntry = ME_OPTIONS;
      break;
    default:
      break;
    }

    sf::Vector2f entryPos = entries[activeEntry]->getPosition();
    m_Cursor.setPosition(entryPos.x - 70, entryPos.y + 30);

    keyLock = true;
  }

  if (!keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    switch (activeEntry) {
    case ME_START:
      setNextGameStateID(GSID_GAME);
      break;
    case ME_OPTIONS:
      setNextGameStateID(GSID_OPTIONS);
      break;
    case ME_QUIT:
      m_Window.close();
      break;
    default:
      break;
    }

    keyLock = true;
  }

  if (keyLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    keyLock = false;
  }

  m_Cursor.update(time);
}

void MainMenu::render(sf::Time& time) {
  for (std::vector<MenuEntry*>::iterator it = entries.begin(); it != entries.end(); ++it) {
    (*it)->Render(m_Window);
  }

  m_Window.draw(m_Cursor);
  m_Window.draw(m_Copyright);
}
