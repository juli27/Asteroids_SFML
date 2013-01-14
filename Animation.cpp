#include "Animation.hpp"

Animation::Animation(const std::string Filename, int Frames, int FrameWidth, int FrameHeight, sf::RenderWindow *Window)
	: m_Window(Window)
{
	sf::Image AnimImg;
	AnimImg.loadFromFile(Filename);
	AnimImg.createMaskFromColor(sf::Color(255, 0, 255));
	m_FrameRect.width = FrameWidth;
	m_FrameRect.height = FrameHeight;

	int FramesX = AnimImg.getSize().x / FrameWidth;

	for (int i = 0; i < Frames; ++i)
	{
		int Colomn = i % FramesX;
		int Row = i / FramesX;

		m_FrameRect.left = Colomn * FrameWidth;
		m_FrameRect.top = Row * FrameHeight;
		m_AnimPhaseTex = new sf::Texture;

		m_AnimPhaseTex->loadFromImage(AnimImg, m_FrameRect);
		m_AnimationTextures.push_back(m_AnimPhaseTex);

		sf::Sprite sprite(*m_AnimPhaseTex);
		m_Animation.push_back(sprite);
	}
}

Animation::Animation()
{
}

Animation::~Animation()
{
	std::list<sf::Texture*>::iterator It;

	for (It = m_AnimationTextures.begin(); It != m_AnimationTextures.end(); ++It)
	{
		delete *It;
	}
}

sf::FloatRect Animation::getCollisionRect() const
{
	return m_AnimPhase.getGlobalBounds();
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
	m_AnimPhase = m_Animation.at(static_cast<int> (FrameNumber));

	m_AnimPhase.setPosition(m_Position);

	m_Window->draw(m_AnimPhase);
}