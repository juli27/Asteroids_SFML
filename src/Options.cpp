#include "Options.hpp"

bool Options::vSyncEnabled = true;

Options::Options(sf::RenderWindow& window, const sf::Font& font)
    : GameState(GSID_OPTIONS, window),
      m_vSync("VSync: on", font),
      m_instructions("Press Enter to change the setting or Esc to return to the menu", font),
      m_keyLock(true) {
  if (!vSyncEnabled) {
    m_vSync.setString("VSync: off");
  }

  m_vSync.setPosition(300.0f, 200.0f);

  m_instructions.setPosition(85.0f, 560.0f);
}

Options::~Options() {

}

void Options::update(sf::Time& time) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    setNextGameStateID(GSID_MAINMENU);
  }

  if (!m_keyLock && sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    vSyncEnabled = !vSyncEnabled;

    if (vSyncEnabled) {
      m_vSync.setString("VSync: on");
    }
    else {
      m_vSync.setString("VSync: off");
    }

    m_window.setVerticalSyncEnabled(vSyncEnabled);
    m_keyLock = true;
  }

  if (m_keyLock && !sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
    m_keyLock = false;
  }
}

void Options::render() {
  m_window.draw(m_vSync);
  m_window.draw(m_instructions);
}
