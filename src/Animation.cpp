#include "Animation.hpp"

Animation::Animation(const std::string filename, int numFrames, int frameWidth, int frameHeight, float speed)
	: m_NumFrames(numFrames),
		m_Speed(speed),
    currentFrame(0),
		nextFrameIndex(0.0f),
		m_Looped(true) {
	sf::Texture* tex = new sf::Texture();
	tex->loadFromFile(filename);
	setTexture(*tex);

	m_Frames = new sf::IntRect[numFrames];

	int framesX = tex->getSize().x / frameWidth;

	for (int i = 0; i < numFrames; ++i) {
		int colomn = i % framesX;
		int row = i / framesX;
		m_Frames[i].left = colomn * frameWidth;
		m_Frames[i].top = row * frameHeight;
		
		m_Frames[i].width = frameWidth;
		m_Frames[i].height = frameHeight;
	}

  setTextureRect(m_Frames[currentFrame]);
}

Animation::~Animation() {
	delete getTexture();
	delete[] m_Frames;
}

void Animation::update(sf::Time& time) {
	nextFrameIndex += m_Speed * time.asSeconds();

	if (nextFrameIndex >= m_NumFrames) {
		if (m_Looped) {
			nextFrameIndex = 0.0f;
		}
		else {
			nextFrameIndex = m_NumFrames - 1.0f;
		}
	}
	else if (nextFrameIndex < 0) {
		if (m_Looped) {
			nextFrameIndex = m_NumFrames - 1.0f;
		}
		else {
			nextFrameIndex = 0.0f;
		}
	}

  //TODO hmm. does this work reliably with float?
  if (currentFrame != std::floor(nextFrameIndex)) {
    currentFrame = static_cast<int> (nextFrameIndex);
    setTextureRect(m_Frames[currentFrame]);
  }
}

void Animation::setSpeed(float speedFactor) {
	m_Speed = speedFactor;
}

void Animation::setFrame(int frame) {
	nextFrameIndex = static_cast<float> (frame);
	setTextureRect(m_Frames[static_cast<int> (nextFrameIndex)]);
}

void Animation::setLooped(bool looped) {
	m_Looped = looped;
}

float Animation::getSpeed() const {
	return m_Speed;
}

int Animation::getFrame() const {
	return static_cast<int> (nextFrameIndex);
}

bool Animation::isLooped() const {
	return m_Looped;
}

sf::IntRect Animation::getCollisionRect() const {
	return sf::IntRect(getGlobalBounds());
}
