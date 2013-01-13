#pragma once

#include "SFML\Graphics.hpp"

class Animation
{
private:
	sf::RenderWindow *m_Window;
	sf::Image m_AnimImg;
	sf::Texture m_AnimPhaseTex;
	sf::Sprite m_AnimPhase;
	sf::Vector2f m_Position;
	sf::IntRect m_FrameRect;
	int m_FrameX;
	int m_FrameY;
	int m_FramesX;

public:
	Animation(const std::string Filename, int Frames, int FrameWidth, int FrameY, sf::RenderWindow *Window);
	Animation();
	~Animation();
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f Position);
	void Render(float FrameNumber);
};