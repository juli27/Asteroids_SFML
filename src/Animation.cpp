#include "Animation.hpp"

Animation::Animation(const std::string filename, int numFrames, int frameWidth, int frameHeight, float speed)
	: m_NumFrames(numFrames),
		m_Speed(speed),
		m_CurrentFrame(0),
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
}

Animation::~Animation() {
	delete getTexture();
}

void Animation::update(sf::Time& time) {
	m_CurrentFrame += m_Speed * time.asSeconds();

	if (m_CurrentFrame >= m_NumFrames) {
		if (m_Looped) {
			m_CurrentFrame = 0.0f;
		}
		else {
			m_CurrentFrame = m_NumFrames - 1;
		}
	}
	else if (m_CurrentFrame < 0) {
		if (m_Looped) {
			m_CurrentFrame = m_NumFrames - 1;
		}
		else {
			m_CurrentFrame = 0.0f;
		}
	}

	setTextureRect(m_Frames[static_cast<int> (m_CurrentFrame)]);
}

void Animation::setSpeed(float speedFactor) {
	m_Speed = speedFactor;
}

void Animation::setFrame(int frame) {
	m_CurrentFrame = static_cast<float> (frame);
	setTextureRect(m_Frames[static_cast<int> (m_CurrentFrame)]);
}

void Animation::setLooped(bool looped) {
	m_Looped = looped;
}

float Animation::getSpeed() const {
	return m_Speed;
}

int Animation::getFrame() const {
	return static_cast<int> (m_CurrentFrame);
}

bool Animation::isLooped() const {
	return m_Looped;
}

sf::IntRect Animation::getCollisionRect() const {
	return sf::IntRect(getGlobalBounds());
}
