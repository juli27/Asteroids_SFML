#pragma once

#include "SFML\Graphics.hpp"
#include <list>

class Animation
{
private:
	sf::RenderWindow *m_Window;
	sf::Image m_AnimImg;
	sf::Texture *m_AnimPhaseTex;
	sf::Sprite m_AnimPhase;
	sf::Vector2f m_Position;
	sf::IntRect m_FrameRect;
	std::list<sf::Texture*> m_AnimationTextures;
	std::vector<sf::Sprite> m_Animation;
	int m_FrameX;
	int m_FrameY;
	int m_Frames;
	int m_FramesX;

public:
	Animation(const std::string Filename, int Frames, int FrameWidth, int FrameY, sf::RenderWindow *Window);
	Animation();
	~Animation();
	sf::FloatRect getCollisionRect() const;
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f Position);
	void Render(float FrameNumber);
};