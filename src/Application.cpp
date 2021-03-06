#include "Application.hpp"

#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>

#include "Game.hpp"
#include "MainMenu.hpp"
#include "Options.hpp"

void Application::run() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids", sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  sf::Texture backgroundTexture;
  backgroundTexture.loadFromFile("data/Background.png");
  sf::Sprite background(backgroundTexture);

  sf::Font agencyFont;
  agencyFont.loadFromFile("data/AGENCYR.TTF");
  sf::Text fpsText("", agencyFont, 20u);

  sf::Time elapsedTimed;
  sf::Clock clock;
  const float fpsUpdateInterval = 0.5f;
  float fpsUpdateTimer = fpsUpdateInterval;
  std::string fpsString;
  sf::String test;
  fpsString.reserve(10);

  // initial GameState is the main menu
  GameState* currentGameState = new MainMenu(window, agencyFont);

  // Mainloop
  while (window.isOpen()) {
    elapsedTimed = clock.restart();

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

    fpsUpdateTimer += elapsedTimed.asSeconds();
    if (fpsUpdateTimer >= fpsUpdateInterval) {
      int fps = static_cast<int> (1.0f / elapsedTimed.asSeconds());
      fpsString.clear();
      fpsString.append(std::to_string(fps)).append(" FPS");
      fpsText.setString(fpsString);

      fpsUpdateTimer = 0.0f;
    }

    // polling every frame is bad :(
    if (currentGameState->hasNextState()) {
      // with a loading screen: switch to loading screen state and pass the new state ID to a
      // function of the loading screen state and let it construct the new state in another thread
      // and return the new state somehow (...) when finished

      GameState* nextGameState = nullptr;

      switch (currentGameState->getNextGameStateID()) {
      case GSID_MAINMENU:
        nextGameState = new MainMenu(window, agencyFont);
        break;
      case GSID_OPTIONS:
        nextGameState = new Options(window, agencyFont);
        break;
      case GSID_GAME:
        nextGameState = new Game(window, agencyFont);
        break;
      default:
        nextGameState = new MainMenu(window, agencyFont);
        break;
      }

      if (nextGameState) {
        delete currentGameState;
        currentGameState = nextGameState;
      }
    }

    currentGameState->update(elapsedTimed);

    window.clear(sf::Color::Magenta);
    window.draw(background);
    currentGameState->render();
    window.draw(fpsText);
    window.display();
  }

  delete currentGameState;
}
