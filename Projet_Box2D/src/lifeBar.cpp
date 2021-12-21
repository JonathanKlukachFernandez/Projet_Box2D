#include "lifebar.h"

LifeBar::LifeBar(float lifeMax)
{

	// Life bar of the ship
	m_lifeBarFill.setSize(sf::Vector2f(400.0f, 5.0f));
	m_lifeBarFill.setPosition(sf::Vector2f(10, 25));
	m_lifeBarFill.setOrigin(0, m_lifeBarFill.getSize().y * 0.5f);
	m_lifeBarFill.setFillColor(sf::Color::Green);

	// Life bar of the ship
	m_lifeBarContour.setSize(sf::Vector2f(400.0f, 5.0f));
	m_lifeBarContour.setPosition(sf::Vector2f(10, 25));
	m_lifeBarContour.setOrigin(0, m_lifeBarContour.getSize().y * 0.5f);
	m_lifeBarContour.setFillColor(sf::Color::Black);
	m_lifeBarContour.setOutlineColor(sf::Color::Green);
	m_lifeBarContour.setOutlineThickness(2);

	m_lifeMax = lifeMax;

}

void LifeBar::update()
{
	// Life bar update
	m_lifeBarFill.setScale(m_life / m_lifeMax, 1.0f);

}

void LifeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_lifeBarContour, states);
	target.draw(m_lifeBarFill, states);
}

void LifeBar::setLife(float life_) {
	m_life = life_;
}
