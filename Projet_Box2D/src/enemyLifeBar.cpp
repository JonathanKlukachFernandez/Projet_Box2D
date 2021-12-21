#include "enemyLifeBar.h"

EnemyLifeBar::EnemyLifeBar(float enemylifeMax)
{

	// Life bar of the enemy ship
	m_enemyLifeBarFill.setSize(sf::Vector2f(400.0f, 5.0f));
	m_enemyLifeBarFill.setPosition(sf::Vector2f(10, 40));
	m_enemyLifeBarFill.setOrigin(0, m_enemyLifeBarFill.getSize().y * 0.5f);
	m_enemyLifeBarFill.setFillColor(sf::Color::Red);

	// Life bar of the enemy ship
	m_enemyLifeBarContour.setSize(sf::Vector2f(400.0f, 5.0f));
	m_enemyLifeBarContour.setPosition(sf::Vector2f(10, 40));
	m_enemyLifeBarContour.setOrigin(0, m_enemyLifeBarContour.getSize().y * 0.5f);
	m_enemyLifeBarContour.setFillColor(sf::Color::Black);
	m_enemyLifeBarContour.setOutlineColor(sf::Color::Red);
	m_enemyLifeBarContour.setOutlineThickness(2);

	m_enemyLifeMax = enemylifeMax;

}

void EnemyLifeBar::update()
{
	// Enemy life bar update
	m_enemyLifeBarFill.setScale(m_enemyLife / m_enemyLifeMax, 1.0f);

}

void EnemyLifeBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_enemyLifeBarContour, states);
	target.draw(m_enemyLifeBarFill, states);
}

void EnemyLifeBar::setEnemyLife(float enemylife_) {
	m_enemyLife = enemylife_;
}
