#pragma once

#include "SFML\Graphics.hpp"

class Animation
{
private:
	sf::RenderWindow &m_Window;
	sf::Texture m_AnimationTex;
	sf::Sprite m_AnimPhase;
	sf::Vector2f m_Position;
	sf::IntRect m_FrameRect;
	std::vector<sf::Sprite> m_Animation;

public:
	Animation(const std::string Filename, int Frames, int FrameWidth, int FrameY, sf::RenderWindow &Window);
	~Animation();
	sf::IntRect getCollisionRect() const;
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f Position);
	void Update();
	void Render(float FrameNumber);
};