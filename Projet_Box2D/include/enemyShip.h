#pragma once

#include "userData.h"
#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

class Game;

class EnemyShip : public sf::Drawable, public sf::Transformable {

public:

	void shoot();

	void UpdateTimer(sf::Time time);

	explicit EnemyShip(Game& game_);
	~EnemyShip() {}

	void init(sf::Vector2u winsize);
	void update();

	void move(sf::Vector2f _pixelsPosition, sf::Vector2f _velocity);

	void speedUp(float force);
	void speedDown(float force);
	void ApplyLocalForceWithCheck(float force);

	void speedLeft(float force);
	void speedRight(float force);
	void ApplyTorqueWithCheck(float force);

	// DRAWABLE OVERRIDES
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// getters
	float getEnemyLife();
	void setDamages(float damages_);
	constexpr float enemyLifeMax() { return 100.0f; };

private:
	bool m_isGoingRight;

	Game& m_game;

	sf::Sprite m_sprite;

	b2Body* m_body = nullptr;
	UserData* m_userData = new UserData(UserDataType::ENEMYSHIP);

	float m_enemyLife = 100.0f;

	float time_between_shots = 5.0f;
	float timer = 5.0f;

};
