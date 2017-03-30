#pragma once

#include <SFML\Graphics.hpp>

class Animation : public sf::Sprite {
private:
	sf::IntRect* m_Frames;
	int m_NumFrames;
	float m_Speed;
	float m_CurrentFrame;
	bool m_Looped;

public:
	Animation(const std::string filename, int numFrames, int frameWidth, int frameHeight, float speed = 0.0f);
	virtual ~Animation();

	void update(sf::Time& time);

	void setSpeed(float speedFactor);
	void setFrame(int frame);
	void setLooped(bool looped);

	float getSpeed() const;
	int getFrame() const;
	bool isLooped() const;
	sf::IntRect getCollisionRect() const;
};
