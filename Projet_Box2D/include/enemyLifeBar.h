#pragma once

#include "SFML/Graphics.hpp"

class EnemyLifeBar : public sf::Drawable
{
public:
	EnemyLifeBar(float enemylifeMax);

	void update();

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// Setters
	void setEnemyLife(float enemylife_);

private:
	sf::RectangleShape m_enemyLifeBarFill;
	sf::RectangleShape m_enemyLifeBarContour;
	float m_enemyLifeMax;
	float m_enemyLife;
};
