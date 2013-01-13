#include "Animation.hpp"

Animation::Animation(const std::string Filename, int Frames, int FrameWidth, int FrameY, sf::RenderWindow *Window)
	: m_Window(Window),
	  m_FrameX(FrameWidth),
	  m_FrameY(FrameY)
{
	m_AnimImg.loadFromFile(Filename);
	m_AnimImg.createMaskFromColor(sf::Color(255, 0, 255));
	m_FrameRect.width = FrameWidth;
	m_FrameRect.height = FrameY;
	m_FramesX = m_AnimImg.getSize().x / m_FrameX;
}

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::setPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void Animation::setPosition(sf::Vector2f Position)
{
	m_Position = Position;
}

void Animation::Render(float FrameNumber)
{
	int Colomn = static_cast<int> (FrameNumber) % m_FramesX;
	int Row = static_cast<int> (FrameNumber) / m_FramesX;

	m_FrameRect.left = Colomn * m_FrameX;
	m_FrameRect.top = Row * m_FrameY;

	m_AnimPhaseTex.loadFromImage(m_AnimImg, m_FrameRect);
	m_AnimPhase.setTexture(m_AnimPhaseTex);
	m_AnimPhase.setPosition(m_Position);

	m_Window->draw(m_AnimPhase);
}