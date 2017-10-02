#include "Animation.hpp"

Animation::Animation(const std::string filename, const int numFrames, const int frameWidth,
  const int frameHeight, const float speed, const bool looped)
    : m_numFrames(numFrames),
      m_speed(speed),
      m_currentFrameIndex(0),
      m_nextFrameIndex(0.0f),
      m_looped(looped) {
  sf::Texture* tex = new sf::Texture();
  tex->loadFromFile(filename);
  setTexture(*tex);

  m_frames = new sf::IntRect[numFrames];

  int framesX = tex->getSize().x / frameWidth;

  for (int i = 0; i < numFrames; ++i) {
    int colomn = i % framesX;
    int row = i / framesX;
    m_frames[i].left = colomn * frameWidth;
    m_frames[i].top = row * frameHeight;

    m_frames[i].width = frameWidth;
    m_frames[i].height = frameHeight;
  }

  setTextureRect(m_frames[m_currentFrameIndex]);
}

Animation::~Animation() {
  delete[] m_frames;
  delete getTexture();
}

void Animation::update(sf::Time& time) {
  if (m_speed == 0.0f) {
    return;
  }

  m_nextFrameIndex += m_speed * time.asSeconds();

  if (m_nextFrameIndex >= m_numFrames) {
    if (m_looped) {
      m_nextFrameIndex = 0.0f;
    }
    else {
      m_nextFrameIndex = m_numFrames - 1.0f;
      m_speed = 0.0f;
    }
  }
  else if (m_nextFrameIndex < 0) {
    if (m_looped) {
      m_nextFrameIndex = m_numFrames - 1.0f;
    }
    else {
      m_nextFrameIndex = 0.0f;
      m_speed = 0.0f;
    }
  }

  if (m_currentFrameIndex != std::floor(m_nextFrameIndex)) {
    m_currentFrameIndex = static_cast<int> (m_nextFrameIndex);
    setTextureRect(m_frames[m_currentFrameIndex]);
  }
}

void Animation::setSpeed(const float speedFactor) {
  m_speed = speedFactor;
}

void Animation::setFrame(const int frame) {
  m_currentFrameIndex = frame;
  m_nextFrameIndex = static_cast<float> (frame);
  setTextureRect(m_frames[frame]);
}

int Animation::getFrame() const {
  return m_currentFrameIndex;
}
