#include "Application.hpp"

#include <iostream>
#include <sstream>

#include "MainMenu.hpp"
#include "Options.hpp"
#include "Game.hpp"

Application::Application() {
  sf::Texture* backgroundTex = new sf::Texture();
  backgroundTex->loadFromFile("data/Background.png");
  m_Background.setTexture(*backgroundTex);

  sf::Font* agencyFont = new sf::Font();
  agencyFont->loadFromFile("data/AGENCYR.TTF");
  m_FPSText.setFont(*agencyFont);
}

Application::~Application() {
  delete m_Background.getTexture();
  delete m_FPSText.getFont();
}

void Application::run() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids");

  sf::Clock clock;
  float fpsDisplayTimer = 0.0f;

  // initial GameState is the main menu
  currentGameState = new MainMenu(window, m_FPSText.getFont());

  // Mainloop
  while (window.isOpen()) {
    sf::Time elapsedTimed = clock.restart();

    // Event polling
    sf::Event event;
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      default:
        break;
      }
    }

    int FPS = static_cast<int> (1.0f / elapsedTimed.asSeconds());

    fpsDisplayTimer += elapsedTimed.asSeconds();
    if (fpsDisplayTimer >= 0.2f) {
      std::ostringstream Converter;
      Converter << FPS << " FPS";
      m_FPSText.setString(Converter.str());

      fpsDisplayTimer = 0.0f;
    }

    if (currentGameState->hasNextState()) {
      GameStateID nextGameStateID = currentGameState->getNextGameStateID();

      delete currentGameState;

      switch (nextGameStateID) {
      case GSID_MAINMENU:
        currentGameState = new MainMenu(window, m_FPSText.getFont());
        break;
      case GSID_OPTIONS:
        currentGameState = new Options(window, m_FPSText.getFont());
        break;
      case GSID_GAME:
        currentGameState = new Game(window, m_FPSText.getFont());
        break;
      default:
        currentGameState = new MainMenu(window, m_FPSText.getFont());
        break;
      }
    }

    currentGameState->update(elapsedTimed);

    window.clear(sf::Color::Magenta);
    window.draw(m_Background);
    currentGameState->render(elapsedTimed);
    window.draw(m_FPSText);
    window.display();
  }

  delete currentGameState;
  currentGameState = nullptr;
}
