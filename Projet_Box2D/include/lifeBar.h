#pragma once

#include "SFML/Graphics.hpp"

class LifeBar : public sf::Drawable
{
public:
	LifeBar(float lifeMax);

	void update();

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Setters
	void setLife(float life_);

private:
	sf::RectangleShape m_lifeBarFill;
	sf::RectangleShape m_lifeBarContour;
	float m_lifeMax;
	float m_life;
};
