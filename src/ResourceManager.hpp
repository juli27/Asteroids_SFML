#pragma once

#include <string>

#include <SFML\Graphics\Font.hpp>

#include "GameState.hpp"

enum ResourceType {
  RES_FONT,
  RES_TEXTURE
};

class ResourceManager {
private:

public:
  unsigned int loadResource(GameStateID gameStateID, ResourceType type, std::string& location);
  sf::Font& getFont(unsigned int handle);
  sf::Texture& getTexture(unsigned int handle);
};
