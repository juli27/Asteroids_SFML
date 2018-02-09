#pragma once

#include <string>

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

class Animation : public sf::Sprite {
private:
  sf::IntRect* m_frames;
  const int m_numFrames;
  float m_speed;
  int m_currentFrameIndex;
  float m_nextFrameIndex;
  bool m_looped;

public:
  /// <summary><c>Contructor</c> This is a test</summary>
  Animation(const std::string filename, const int numFrames, const int frameWidth,
    const int frameHeight, const float speed = 0.0f, const bool looped = true);
  virtual ~Animation();

  void update(sf::Time& time);

  void setSpeed(const float speedFactor);
  void setFrame(int frame);

  int getFrame() const;
};
